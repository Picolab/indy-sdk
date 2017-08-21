
#ifndef CALLBACK_HASH_INCLUDED
#define CALLBACK_HASH_INCLUDED

#include <thread>

#include "napi.h"
#include "indy_core.h"
#include "indy_types.h"

#include "hash/hash.h"

struct indy_callback {
  indy_handle_t handle;
  napi_ref callback_ref;
  std::mutex mutex;
  std::condition_variable cv;
  bool cancelled;
  bool completed;
  bool persists;
  indy_error_t error;
  size_t n_char_results;
  std::vector<char*> char_results;
  size_t n_handle_results;
  std::vector<indy_handle_t> handle_results;
  size_t n_bool_results;
  std::vector<indy_bool_t> bool_results;
};

typedef struct indy_callback indy_callback;

hash_t* callbacks = hash_new();

char* handle_to_key(indy_handle_t handle) {
  size_t len = 12;
  char* key = (char*) malloc(len);
  size_t written = snprintf(key, len, "%d", handle);
  if (written >= len) {
    printf("FATAL handle_to_key: handle too large\n");
    exit(1);
  }
  return key;
}

indy_callback* new_callback(
  indy_handle_t handle,
  napi_env env,
  napi_value js_callback
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
  callback->persists = false;
  callback->n_char_results = 0;
  callback->n_handle_results = 0;
  callback->n_bool_results = 0;
  
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
  char* key = handle_to_key(handle);
  int has = hash_has(callbacks, key);
  free(key);
  return has;
}

void set_callback(indy_callback* callback) {
  if (has_callback(callback->handle)) return;
  char* key = handle_to_key(callback->handle);
  hash_set(callbacks, key, callback);
}

indy_callback* get_callback(indy_handle_t handle) {
  char* key = handle_to_key(handle);
  indy_callback* callback = (indy_callback*) hash_get(callbacks, key);
  free(key);
  if (!callback) {
    printf("==================================== CALLBACK NULL\n");
    return NULL;
  }
  return callback;
}

void free_callback(indy_handle_t handle) {
  indy_callback* callback = get_callback(handle);
  if (callback == NULL) return;
  char* key = handle_to_key(handle);
  if (key != NULL) {
    hash_del(callbacks, key);
    free(key);
  }
  delete callback;
}

#endif