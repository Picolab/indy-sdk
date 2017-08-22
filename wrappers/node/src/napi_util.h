
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

void call_javascript_callback(napi_env env, indy_callback* callback) {
  napi_status status;
  napi_value global, err, js_callback;

  status = napi_get_global(env, &global);
  NAPI_CHECK_STATUS_VOID("napi_get_global");

  napi_ref callback_ref = callback->callback_refs.at(0);
  status = napi_get_reference_value(env, callback_ref, &js_callback);
  NAPI_CHECK_STATUS_VOID("napi_get_reference_value");

  if (callback->multiple == false) {
    status = napi_delete_reference(env, callback_ref);
    NAPI_CHECK_STATUS_VOID("napi_delete_reference");
  }

  status = napi_create_number(env, (double) callback->error, &err);
  NAPI_CHECK_STATUS_VOID("napi_create_number");
  
  size_t argc_idx = 0;
  size_t argc = (
    callback->handle_results.size() + 
    callback->char_results.size() +
    callback->bool_results.size()
  ) + 1; // 1 for the error
  
  napi_value argv[argc];

  // bind error value
  argv[0] = err;
  argc_idx += 1;

  // FIXME
  // it'll probably be necessary to switch to a dictionary of results
  // as this method of binding results to the callback is
  // unlikely to be ordered correctly for every libindy call

  for (indy_handle_t handle : callback->handle_results) {
    napi_value res;
    printf("TRACE %d binding number arg %d\n", callback->handle, handle);

    status = napi_create_number(env, (double) handle, &res);
    NAPI_CHECK_STATUS_VOID("napi_create_number");
    
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  for (char* char_res : callback->char_results) {
    napi_value res;
    printf("TRACE %d binding string arg %s\n", callback->handle, char_res);
    
    status = napi_create_string_utf8(env, char_res, strlen(char_res), &res);
    NAPI_CHECK_STATUS_VOID("napi_create_string_utf8");
    
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  for (indy_bool_t bool_result : callback->bool_results) {
    napi_value num;
    napi_value res;
    printf("TRACE %d binding boolean arg %d\n", callback->handle, bool_result);
    
    status = napi_create_number(env, (double) bool_result, &num);
    NAPI_CHECK_STATUS_VOID("napi_create_number");
    
    status = napi_coerce_to_bool(env, num, &res);
    NAPI_CHECK_STATUS_VOID("napi_coerce_to_bool");
    
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  status = napi_make_callback(env, global, js_callback, argc_idx, argv, NULL);
  NAPI_CHECK_STATUS_VOID("napi_make_callback");
}

void execute(napi_env env, void* data) {
  indy_callback* callback = (indy_callback*) data;
  if (!callback) return;
  printf("TRACE execute %d\n", callback->handle);

  while (true) {
    // construct a lock
    std::unique_lock<std::mutex> lock(callback->mutex);
    
    // and wait to be notified of new data
    callback->cv.wait(lock, [callback] {
      return callback->cancelled || callback->completed;
    });

    // if the current callback may be called N times
    if (callback->multiple) {

      // call into javascript with the latest results
      call_javascript_callback(env, callback);
      
      // if the results should be used to schedule a new thread
      if (callback->creates_new_callback_from_results == true) {
        
        indy_callback* next_callback;
        size_t libindy_method_length = strlen(callback->libindy_method);
        if (strncmp(callback->libindy_method, "agent_listen_connection", libindy_method_length) == 0) {
          // construct a new callback that can be called multiple
          // times but may not schedule new threads with its results
          next_callback = new_callback_from_existing(env, callback, true, false);
          
          // we actually dont need to name it because we won't reschedule with results
          next_callback->libindy_method = "agent_listen_message";
        } else {
          // if we got here, it's definitely programmer error
          // because all the cases for scheduling new threads
          // from the current callback results are hardcoded
          printf("================================= FATAL didnt match a branch for next callback type\n");
          exit(1);
        }

        // add to global map
        set_callback(next_callback);
        
        // schedule the new callback for execution
        napi_status status;
        napi_async_work work;
        status = napi_create_async_work(env, execute, complete, next_callback, &work);
        NAPI_CHECK_STATUS_VOID("napi_create_async_work");
        status = napi_queue_async_work(env, work);
        NAPI_CHECK_STATUS_VOID("napi_queue_async_work");
      }
      
      // reset the current callback result vectors
      reset_callback(callback);

      // unlock
      lock.unlock();
      
      // and start again!
      continue;
    }

    // unlock
    lock.unlock();
    return;
  }
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
  
  call_javascript_callback(env, callback);

  if (callback->creates_new_callback_from_results == true) {

    indy_callback* next_callback;
    size_t libindy_method_length = strlen(callback->libindy_method);

    if (strncmp(callback->libindy_method, "agent_listen_listening", libindy_method_length) == 0) {
      next_callback = new_callback_from_existing(env, callback, true, true);
      next_callback->libindy_method = "agent_listen_connection";
    } else if (strncmp(callback->libindy_method, "agent_connect_connect", libindy_method_length) == 0) {
      next_callback = new_callback_from_existing(env, callback, true, false);
    } else {
      printf("================================= FATAL didnt match a branch for next callback type\n");
      exit(1);
    }

    set_callback(next_callback);

    napi_async_work work;
    status = napi_create_async_work(env, execute, complete, next_callback, &work);
    NAPI_CHECK_STATUS_VOID("napi_create_async_work");
    status = napi_queue_async_work(env, work);
    NAPI_CHECK_STATUS_VOID("napi_queue_async_work");
  }

  free_callback(callback->handle);
}