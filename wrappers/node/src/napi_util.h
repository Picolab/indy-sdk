
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
  #ifdef INDY_LOG_DEBUG
  printf("entering %s handle %d\n", __func__, callback->handle);
  #endif

  napi_status status;
  napi_value global, err, js_callback;

  #ifdef INDY_LOG_DEBUG
  printf("acquiring reference to javascript global context\n");
  #endif

  status = napi_get_global(env, &global);
  NAPI_CHECK_STATUS_VOID("napi_get_global");

  #ifdef INDY_LOG_DEBUG
  printf("acquiring reference to javascript function\n");
  #endif
  napi_ref callback_ref = callback->callback_refs.at(0);
  status = napi_get_reference_value(env, callback_ref, &js_callback);
  NAPI_CHECK_STATUS_VOID("napi_get_reference_value");

  if (callback->multiple == false) {
    #ifdef INDY_LOG_DEBUG
    printf("handle %d may not invoke its callback N times\n", callback->handle);
    printf("deleting reference to javascript function for handle %d\n", callback->handle);
    #endif

    status = napi_delete_reference(env, callback_ref);
    NAPI_CHECK_STATUS_VOID("napi_delete_reference");
  }

  #ifdef INDY_LOG_DEBUG
  printf("creating javascript number value to represent libindy error for handle %d\n", callback->handle);
  #endif
  status = napi_create_number(env, (double) callback->error, &err);
  NAPI_CHECK_STATUS_VOID("napi_create_number");
  
  size_t argc_idx = 0;
  size_t argc = (
    callback->handle_results.size() + 
    callback->char_results.size() +
    callback->bool_results.size()
  ) + 1; // 1 for the error
  
  napi_value argv[argc];

  argv[0] = err; // node's conventional error-first
  argc_idx += 1;

  // FIXME
  // it'll probably be necessary to switch to a dictionary of results
  // as this method of binding results to the callback is
  // unlikely to be ordered correctly for every libindy call

  for (indy_handle_t handle : callback->handle_results) {
    napi_value res;

    #ifdef INDY_LOG_DEBUG
    printf("binding number arg %d for handle %d\n", handle, callback->handle);
    #endif

    status = napi_create_number(env, (double) handle, &res);
    NAPI_CHECK_STATUS_VOID("napi_create_number");
    
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  for (char* char_res : callback->char_results) {
    napi_value res;

    #ifdef INDY_LOG_DEBUG
    printf("binding string arg %s for handle %d\n", char_res, callback->handle);
    #endif

    status = napi_create_string_utf8(env, char_res, strlen(char_res), &res);
    NAPI_CHECK_STATUS_VOID("napi_create_string_utf8");
    
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  for (indy_bool_t bool_result : callback->bool_results) {
    napi_value num;
    napi_value res;

    #ifdef INDY_LOG_DEBUG
    printf("binding boolean arg %d for handle %d\n", bool_result, callback->handle);
    #endif
    
    status = napi_create_number(env, (double) bool_result, &num);
    NAPI_CHECK_STATUS_VOID("napi_create_number");
    
    status = napi_coerce_to_bool(env, num, &res);
    NAPI_CHECK_STATUS_VOID("napi_coerce_to_bool");
    
    argv[argc_idx] = res;
    argc_idx += 1;
  }

  #ifdef INDY_LOG_DEBUG
  printf("calling into javascript for handle %d\n", callback->handle);
  #endif
  status = napi_make_callback(env, global, js_callback, argc_idx, argv, NULL);
  NAPI_CHECK_STATUS_VOID("napi_make_callback");
}

void execute(napi_env env, void* data) {
  indy_callback* callback = (indy_callback*) data;
  if (!callback) {
    #ifdef INDY_LOG_WARN
    printf("entering %s but context data is NULL\n", __func__);
    #endif
    return;
  }

  #ifdef INDY_LOG_DEBUG
  printf("entering %s for handle %d\n", __func__, callback->handle);
  #endif

  while (true) {
    // construct a lock
    std::unique_lock<std::mutex> lock(callback->mutex);
    
    #ifdef INDY_LOG_DEBUG
    printf("constructed lock for handle %d\n", callback->handle);
    #endif

    // and wait to be notified of new data
    callback->cv.wait(lock, [callback] {
      return callback->cancelled || callback->completed;
    });

    #ifdef INDY_LOG_DEBUG
    printf("got wakeup signal for handle %d\n", callback->handle);
    #endif

    // if the current callback may be called N times
    if (callback->multiple) {

      #ifdef INDY_LOG_DEBUG
      printf("handle %d may invoke its callback multiple times\n", callback->handle);
      #endif

      // call into javascript with the latest results
      call_javascript_callback(env, callback);
      
      // if the results should be used to schedule a new thread
      if (callback->creates_new_callback_from_results == true) {
        
        #ifdef INDY_LOG_DEBUG
        printf("handle %d schedules new callbacks from its results\n", callback->handle);
        #endif

        indy_callback* next_callback;
        size_t libindy_method_length = strlen(callback->libindy_method);
        if (strncmp(callback->libindy_method, "agent_listen_connection", libindy_method_length) == 0) {

          #ifdef INDY_LOG_DEBUG
          printf("constructing new indy_callback struct from handle %d for agent_listen_connection\n", callback->handle);
          #endif

          // construct a new callback that can be called multiple
          // times but may not schedule new threads with its results
          next_callback = new_callback_from_existing(env, callback, true, false);
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
        
        #ifdef INDY_LOG_DEBUG
        printf("scheduling new callback from handle %d for %s\n", next_callback->handle, next_callback->libindy_method);
        #endif

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

    // and leave
    break;
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
    #ifdef INDY_LOG_INFO
    printf("entering %s but task is cancelled\n", __func__);
    #endif
    return;
  }

  indy_callback* callback = (indy_callback*) data;
  if (!callback) {
    #ifdef INDY_LOG_WARN
    printf("entering %s but context data is NULL\n", __func__);
    #endif
    return;
  }

  #ifdef INDY_LOG_DEBUG
  printf("entering %s for handle %d\n", __func__, callback->handle);
  #endif

  if (callback->cancelled == true) {
    #ifdef INDY_LOG_INFO
    printf("handle %d was cancelled\n", callback->handle);
    #endif
    
    #ifdef INDY_LOG_DEBUG
    printf("handle %d is being deallocated\n", callback->handle);
    #endif

    free_callback(callback->handle);
    return;
  }

  napi_status status;
  
  call_javascript_callback(env, callback);

  if (callback->creates_new_callback_from_results == true) {

    #ifdef INDY_LOG_DEBUG
    printf("handle %d schedules new callbacks from its results\n", callback->handle);
    #endif

    indy_callback* next_callback;
    size_t libindy_method_length = strlen(callback->libindy_method);

    if (strncmp(callback->libindy_method, "agent_listen_listening", libindy_method_length) == 0) {
      
      #ifdef INDY_LOG_DEBUG
      printf("constructing new indy_callback struct from handle %d for agent_listen_connection\n", callback->handle);
      #endif
      
      next_callback = new_callback_from_existing(env, callback, true, true);
      next_callback->libindy_method = "agent_listen_connection";
    } else if (strncmp(callback->libindy_method, "agent_connect_connect", libindy_method_length) == 0) {
      
      #ifdef INDY_LOG_DEBUG
      printf("constructing new indy_callback struct from handle %d for agent_connect_message\n", callback->handle);
      #endif

      next_callback = new_callback_from_existing(env, callback, true, false);
      next_callback->libindy_method = "agent_connect_message";
    } else {

      // if we got here it can only be programmer error
      // as every string comparison case is hardcoded based
      // on the behaviour of libindy calls
      printf("================================= FATAL didnt match a branch for next callback type\n");
      exit(1);
    }

    set_callback(next_callback);

    #ifdef INDY_LOG_DEBUG
    printf("scheduling new callback from handle %d for %s\n", next_callback->handle, next_callback->libindy_method);
    #endif

    napi_async_work work;
    status = napi_create_async_work(env, execute, complete, next_callback, &work);
    NAPI_CHECK_STATUS_VOID("napi_create_async_work");
    status = napi_queue_async_work(env, work);
    NAPI_CHECK_STATUS_VOID("napi_queue_async_work");
  }

  free_callback(callback->handle);
}