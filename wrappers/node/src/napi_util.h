
#include <time.h>
#include <errno.h>

#include <napi.h>

void complete(napi_env env, napi_status async_work_status, void* data);
void execute(napi_env env, void* data);

size_t napi_string_length(napi_env env, napi_value string) {
  size_t string_length;
  napi_status status;
  napi_valuetype type;
  status = napi_typeof(env, string, &type);
  if (status != napi_ok) return 1;
  if (type != napi_string) return 1;
  status = napi_get_value_string_utf8(env, string, NULL, 0, &string_length);
  if (status != napi_ok) return 1;
  return (string_length + 1);
}

void execute(napi_env env, void* data) {
  // printf("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\n");
  // int millis = 8;
  // struct timespec duration;
  // duration.tv_sec = millis / 1000;
  // duration.tv_nsec = (millis % 1000) * 1000000;
  // const struct timespec* duration_ptr = &duration;
  // struct timespec remaining;
  // int slept = nanosleep(duration_ptr, &remaining);
  // printf("=================================================== woke up\n");
  // if (slept == -1) {
  //   // interrupted by signal
  //   printf("=================================================== %d", errno);
  // }
}

void complete(
  napi_env env,
  napi_status async_work_status,
  void* data
) {
  // printf("entering complete\n");

  indy_callback* callback = (indy_callback*) data;

  if (
    async_work_status == napi_cancelled ||
    async_work_status == napi_generic_failure || 
    callback->cancelled
  ) {
    printf("============================CANCELLED\n");
    return;
  }

  if (callback != NULL) {
    if (!callback->completed) {
      // printf("work not completed\n");
      napi_status status;
      napi_async_work work;
      status = napi_create_async_work(
        env,
        execute,
        complete,
        callback,
        &work
      );
      NAPI_CHECK_STATUS_VOID("napi_create_async_work");

      callback = (indy_callback*) data;
      if (callback->completed) {
        status = napi_delete_async_work(env, work);
        NAPI_CHECK_STATUS_VOID("napi_delete_async_work");
        printf("========================================going to NEVERMIND\n");
        goto nevermind;
      }
      status = napi_queue_async_work(env, work);
      // printf("REQUEUING %d\n", callback->handle);
      NAPI_CHECK_STATUS_VOID("napi_queue_async_work");
      return;
    }
  } else {
    printf("-------------------------callback was NULL before check completed\n");
    return;
  }

  nevermind:
  printf("COMPLETED %d\n", callback->handle);

  napi_status status;
  // napi_value global, err, js_callback, result;

  napi_handle_scope scope;

  printf("before napi_open_handle_scope\n");
  status = napi_open_handle_scope(env, &scope);
  NAPI_CHECK_STATUS_VOID("napi_open_handle_scope");
  printf("after napi_open_handle_scope\n");

  napi_value global, err, js_callback;

  printf("before napi_get_global\n");
  if (callback != NULL) {
    status = napi_get_global(env, &global);
    if (status != napi_ok) {
      napi_throw_error(env, "napi_get_global");
      return;
    }
  } else {
    printf("-------------------------callback was NULL before napi_get_global\n");
    return;
  }

  printf("before napi_get_reference_value\n");
  if (callback != NULL) {
    if (env != NULL && callback->callback_ref != NULL) {
      status = napi_get_reference_value(
        env,
        callback->callback_ref,
        &js_callback
      );
      if (status != napi_ok) {
        napi_throw_error(env, "napi_get_reference_value");
        return;
      }
      if (!js_callback) {
        printf("-------------------------js_callback is NULL\n");
        return;
      }
    } else {
      printf("-------------------------callback_ref or env is NULL\n");
      return;
    }
  } else {
    printf("-------------------------callback was NULL before napi_get_reference_value\n");
    return;
  }
  

  printf("before napi_delete_reference\n");
  if (callback != NULL) {
    if (callback->callback_ref != NULL) {
      status = napi_delete_reference(env, callback->callback_ref);
      if (status != napi_ok) {
        napi_throw_error(env, "napi_delete_reference");
        return;
      }
    } else {
      printf("--------------------------callback_ref is NULL\n");
      return;
    }
  } else {
    printf("-------------------------callback was NULL before napi_delete_reference\n");
    return;
  }

  printf("before napi_create_number\n");
  if (callback != NULL) {
    status = napi_create_number(env, (double) callback->error, &err);
    if (status != napi_ok) {
      napi_throw_error(env, "napi_create_number");
      return;
    }
  } else {
    printf("-------------------------callback was NULL before napi_create_number\n");
    return;
  }
  
  printf("before arg binding\n");
  size_t total_args = callback->n_char_results + callback->n_handle_results;
  size_t argc = 1 + total_args;
  napi_value argv[argc];

  argv[0] = err;
  size_t argc_idx = 1;
  size_t i = 0;
  for (; i < callback->n_handle_results; i++, argc_idx++) {
    napi_value res;

    printf("attempting to bind arg %d\n", callback->handle_results[i]);

    status = napi_create_number(env, (double) callback->handle_results[i], &res);
    NAPI_CHECK_STATUS_VOID("napi_create_number");
    argv[argc_idx] = res;
  }

  for (i = 0; i < callback->n_char_results; i++, argc_idx++) {
    napi_value res;

    printf("attempting to bind arg %s\n", callback->char_results[i]);

    status = napi_create_string_utf8(
      env,
      callback->char_results[i],
      strlen(callback->char_results[i]),
      &res
    );
    NAPI_CHECK_STATUS_VOID("napi_create_string_utf8");
    argv[argc_idx] = res;
  }

  printf("before napi_make_callback\n");
  status = napi_make_callback(
    env,
    global,
    js_callback,
    argc_idx,
    argv,
    NULL
  );
  if (status != napi_ok) {
    napi_throw_error(env, "napi_make_callback");
    return;
  }

  printf("before napi_close_handle_scope\n");
  status = napi_close_handle_scope(env, scope);
  NAPI_CHECK_STATUS_VOID("napi_close_handle_scope");
  printf("after napi_close_handle_scope\n");

  printf("before set called\n");
  if (callback != NULL) {
    callback->called = true;
  } else {
    printf("-------------------------callback was NULL before setting called\n");
    return;
  }

  // if (callback != NULL) {
  //   printf("before free_callback\n");
  //   free_callback(callback->handle);
  //   printf("after free_callback %p %s\n", callback, callback ? "NOT NULL" : "NULL");
  // } else {
  //   printf("-------------------------callback was NULL before free_callback\n");
  //   return;
  // }
  
  // if (callback == NULL) {
  //   printf("-----------callback is NULL can you believe it!\n");
  // }
  
  printf("leaving complete\n");
}