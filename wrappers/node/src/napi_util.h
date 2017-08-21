
#include <thread>

#include "napi.h"

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
  indy_callback* callback = (indy_callback*) data;
  if (!callback) return;
  printf("TRACE execute %d\n", callback->handle);
  std::unique_lock<std::mutex> lock(callback->mutex);
  callback->cv.wait(lock, [callback] {
    return (
      callback->completed ||
      callback->called ||
      callback->cancelled
    );
  });
  lock.unlock();
}

void complete(
  napi_env env,
  napi_status async_work_status,
  void* data
) {
  indy_callback* callback = (indy_callback*) data;
  if (!callback) {
    printf("============================= NULL\n");
    return;
  }

  printf("TRACE complete %d\n", callback->handle);

  if (async_work_status == napi_cancelled) {
    printf("============================ CANCELLED\n");
    // NOTE void* data already freed by macro
    return;
  }

  if (callback->called == true) {
    printf("============================ CALLED %d\n", callback->handle);
    printf("========================== FREEING CALLBACK %d\n", callback->handle);
    free_callback(callback->handle);
    return;
  }

  if (callback->cancelled == true) {
    printf("========================== CANCELLED %d\n", callback->handle);
    printf("========================== FREEING CALLBACK %d\n", callback->handle);
    free_callback(callback->handle);
    return;
  }

  napi_status status;

  if (callback->completed == false) {
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
    
    if (callback->completed == true) {
      status = napi_delete_async_work(env, work);
      NAPI_CHECK_STATUS_VOID("napi_delete_async_work");
      printf("======================================== going to NEVERMIND\n");

      if (callback->called == true) {
        printf("============================ CALLED %d\n", callback->handle);
        printf("========================== FREEING CALLBACK %d\n", callback->handle);
        free_callback(callback->handle);
        return;
      }

      goto nevermind;
    }

    status = napi_queue_async_work(env, work);
    NAPI_CHECK_STATUS_VOID("napi_queue_async_work");
    return;
  }

  nevermind:

  napi_handle_scope scope;
  
  status = napi_open_handle_scope(env, &scope);
  NAPI_CHECK_STATUS_VOID("napi_open_handle_scope");

  napi_value global, err, js_callback;

  status = napi_get_global(env, &global);
  if (status != napi_ok) {
    napi_throw_error(env, "napi_get_global");
    return;
  }

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
    printf("------------------------- js_callback is NULL\n");
    printf("========================== FREEING CALLBACK %d\n", callback->handle);
    free_callback(callback->handle);
    return;
  }

  status = napi_delete_reference(env, callback->callback_ref);
  if (status != napi_ok) {
    napi_throw_error(env, "napi_delete_reference");
    return;
  }

  status = napi_create_number(env, (double) callback->error, &err);
  if (status != napi_ok) {
    napi_throw_error(env, "napi_create_number");
    return;
  }
  
  printf("before arg binding\n");
  size_t total_args = callback->n_char_results + callback->n_handle_results + callback->n_bool_results;
  size_t argc = 1 + total_args;
  napi_value argv[argc];

  argv[0] = err;
  size_t argc_idx = 1;

  // FIXME
  // it'll probably be necessary to switch to a dictionary of results
  // as this method of binding results to the user-given callback is
  // unlikely to be ordered correctly for every libindy call

  for (indy_handle_t handle : callback->handle_results) {
    napi_value res;
    printf("attempting to bind arg %d\n", handle);
    status = napi_create_number(env, (double) handle, &res);
    NAPI_CHECK_STATUS_VOID("napi_create_number");
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  for (char* char_res : callback->char_results) {
    napi_value res;
    printf("attempting to bind arg %s\n", char_res);
    status = napi_create_string_utf8(env, char_res, strlen(char_res), &res);
    NAPI_CHECK_STATUS_VOID("napi_create_string_utf8");
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  for (bool bool_result : callback->bool_results) {
    napi_value num;
    napi_value res;
    printf("attempting to bind arg %s\n", bool_result);
    status = napi_create_number(env, (double) bool_result, &num);
    NAPI_CHECK_STATUS_VOID("napi_create_number");
    status = napi_coerce_to_bool(env, num, &res);
    NAPI_CHECK_STATUS_VOID("napi_coerce_to_bool");
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  printf("before napi_make_callback\n");
  callback = (indy_callback*) data;
  if (callback->called == false) {
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
  }

  callback->called = true;
  printf("========================== FREEING CALLBACK %d\n", callback->handle);
  free_callback(callback->handle);
  
  status = napi_close_handle_scope(env, scope);
  NAPI_CHECK_STATUS_VOID("napi_close_handle_scope");

  printf("leaving complete\n");
}