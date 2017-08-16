
#ifndef CALLBACK_HASH_INCLUDED
#define CALLBACK_HASH_INCLUDED

#include <napi.h>
#include <indy_core.h>
#include <indy_types.h>

#include "hash/hash.h"

struct indy_callback {
  indy_handle_t handle;
  napi_ref callback_ref; // FIXME support N libindy callbacks per struct
  bool cancelled;
  bool completed;
  bool called;
  indy_error_t error;
  size_t n_char_results;
  char** char_results;
  size_t n_handle_results;
  indy_handle_t handle_results[];
};

typedef struct indy_callback indy_callback;

hash_t* callbacks = hash_new();

indy_callback* new_callback(
  indy_handle_t handle,
  napi_env env,
  napi_value js_callback
) {
  napi_status status;
  indy_callback* callback = (indy_callback*) malloc(sizeof(indy_callback));

  if (!callback) {
    perror("malloc indy_callback failed");
    exit(1);
  }

  // defaults
  callback->handle = handle;
  callback->cancelled = false;
  callback->called = false;
  callback->completed = false;
  callback->n_char_results = 0;
  callback->n_handle_results = 0;

  status = napi_create_reference(
    env,
    js_callback,
    1,
    &callback->callback_ref
  );
  NAPI_CHECK_STATUS("napi_create_reference");
  return callback;
}

int has_callback(indy_handle_t handle) {
  return hash_has(callbacks, handle);
}

void set_callback(indy_callback* callback) {
  if (has_callback(callback->handle)) return;
  hash_set(callbacks, callback->handle, callback);
}

indy_callback* get_callback(indy_handle_t handle) {
  return (indy_callback*) hash_get(callbacks, handle);
}

void free_callback(indy_handle_t handle) {
  if (!has_callback(handle)) return;
  indy_callback* callback = get_callback(handle);
  if (callback == NULL) return;
  hash_del(callbacks, handle);
  free(callback);
}

#endif