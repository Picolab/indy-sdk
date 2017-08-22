
#ifndef CALLBACK_HASH_INCLUDED
#define CALLBACK_HASH_INCLUDED

#include <map>
#include <thread>

#include "napi.h"
#include "indy_core.h"
#include "indy_types.h"

struct indy_callback {
  const char* libindy_method;
  indy_handle_t handle;
  indy_error_t error;
  bool cancelled;
  bool completed;
  bool multiple;
  bool has_new;
  bool creates_new_callback_from_results;
  std::mutex mutex;
  std::condition_variable cv;
  std::vector<napi_ref> callback_refs;
  std::vector<char*> char_results;
  std::vector<indy_handle_t> handle_results;
  std::vector<indy_bool_t> bool_results;
};

typedef struct indy_callback indy_callback;

std::map<indy_handle_t, indy_callback*> callbacks;

indy_callback* new_callback(
  indy_handle_t handle,
  napi_env env,
  std::vector<napi_value> js_callbacks
) {
  napi_status status;
  indy_callback* callback = new indy_callback;

  if (!callback) {
    perror("malloc indy_callback failed");
    exit(1);
  }

  printf("======================= ALLOCATED callback %d\n", handle);

  // defaults
  callback->handle = handle;
  callback->cancelled = false;
  callback->completed = false;
  callback->multiple = false;
  callback->creates_new_callback_from_results = false;
  
  for (napi_value js_callback : js_callbacks) {
    napi_ref callback_ref;
    status = napi_create_reference(env, js_callback, 1, &callback_ref);
    NAPI_CHECK_STATUS("napi_create_reference");
    callback->callback_refs.push_back(callback_ref);
  }

  return callback;
}

indy_callback* new_callback_from_existing(
  napi_env env,
  indy_callback* existing_callback,
  bool creates_new_callback_from_results,
  bool multiple
) {
  napi_status status;
  // copy the current callback functions to the new struct
  std::vector<napi_value> js_callbacks;
  for (napi_ref callback_ref : existing_callback->callback_refs) {
    napi_value js_callback;
    status = napi_get_reference_value(env, callback_ref, &js_callback);
    NAPI_CHECK_STATUS("napi_get_reference_value");
    js_callbacks.push_back(js_callback);
  }
  indy_callback* callback = new_callback(existing_callback->handle_results.at(0), env, js_callbacks);
  callback->creates_new_callback_from_results = creates_new_callback_from_results;
  callback->multiple = multiple;
  return callback;
}

void reset_callback(indy_callback* callback) {
  callback->cancelled = false;
  callback->completed = false;
  callback->error = Success;
  callback->char_results.clear();
  callback->handle_results.clear();
  callback->bool_results.clear();
}

indy_callback* get_callback(indy_handle_t handle) {
  try {
    return callbacks.at(handle);
  } catch (std::out_of_range ex) {
    return NULL;
  }
}

void set_callback(indy_callback* callback) {
  callbacks.insert(
    std::pair<
      indy_handle_t,
      indy_callback*
    >(
      callback->handle,
      callback
    )
  );
}

void free_callback(indy_handle_t handle) {
  indy_callback* callback = get_callback(handle);
  if (callback == NULL) return;
  callbacks.erase(handle);
  delete callback;
}

#endif