
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
  if (async_work_status == napi_cancelled) {
    // NOTE
    // we have to check this first as the struct associated
    // with this task will already have been deallocated
    printf("============================ CANCELLED\n");
    return;
  }

  indy_callback* callback = (indy_callback*) data;
  if (!callback) {
    printf("============================= NULL\n");
    return;
  }

  printf("TRACE complete %d\n", callback->handle);

  if (callback->cancelled == true) {
    printf("========================== CANCELLED %d\n", callback->handle);
    printf("========================== FREEING CALLBACK %d\n", callback->handle);
    free_callback(callback->handle);
    return;
  }

  napi_status status;
  napi_value global, err, js_callback;

  status = napi_get_global(env, &global);
  NAPI_CHECK_STATUS_VOID("napi_get_global");

  status = napi_get_reference_value(env, callback->callback_ref, &js_callback);
  NAPI_CHECK_STATUS_VOID("napi_get_reference_value");

  status = napi_delete_reference(env, callback->callback_ref);
  NAPI_CHECK_STATUS_VOID("napi_delete_reference");

  status = napi_create_number(env, (double) callback->error, &err);
  NAPI_CHECK_STATUS_VOID("napi_create_number");
  
  size_t argc_idx = 0;
  size_t argc = 1 + (
    callback->n_char_results +
    callback->n_handle_results +
    callback->n_bool_results
  );
  napi_value argv[argc];

  // bind error value
  argv[0] = err;
  argc_idx += 1;

  // FIXME
  // it'll probably be necessary to switch to a dictionary of results
  // as this method of binding results to the user-given callback is
  // unlikely to be ordered correctly for every libindy call

  for (indy_handle_t handle : callback->handle_results) {
    napi_value res;
    printf("attempting to bind number arg %d\n", handle);
    status = napi_create_number(env, (double) handle, &res);
    NAPI_CHECK_STATUS_VOID("napi_create_number");
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  for (char* char_res : callback->char_results) {
    napi_value res;
    printf("TRACE %d bind string arg %s\n", callback->handle, char_res);
    status = napi_create_string_utf8(env, char_res, strlen(char_res), &res);
    NAPI_CHECK_STATUS_VOID("napi_create_string_utf8");
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  for (indy_bool_t bool_result : callback->bool_results) {
    napi_value num;
    napi_value res;
    printf("TRACE %d bind boolean arg %d\n", callback->handle, bool_result);
    status = napi_create_number(env, (double) bool_result, &num);
    NAPI_CHECK_STATUS_VOID("napi_create_number");
    status = napi_coerce_to_bool(env, num, &res);
    NAPI_CHECK_STATUS_VOID("napi_coerce_to_bool");
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  status = napi_make_callback(env, global, js_callback, argc_idx, argv, NULL);
  NAPI_CHECK_STATUS_VOID("napi_make_callback");
  
  // FIXME
  // some callbacks will be invoked more than once by libindy
  // in these cases, the callback's result vectors need to be reset

  printf("========================== FREEING CALLBACK %d\n", callback->handle);
  free_callback(callback->handle);
}