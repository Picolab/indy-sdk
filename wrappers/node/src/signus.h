
void decrypt_on_decrypted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* decrypted
) {
  #ifdef INDY_LOG_DEBUG
  printf("decrypt_on_decrypted\n");
  #endif

  indy_callback* callback = get_callback(command_handle);
  if (!callback) return;

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) decrypted);
  callback->completed = true;
  callback->cv.notify_one();
}

void encrypt_on_encrypted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* encrypted,
  const char* nonce
) {
  #ifdef INDY_LOG_DEBUG
  printf("encrypt_on_encrypted\n");
  #endif

  indy_callback* callback = get_callback(command_handle);
  if (!callback) return;

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) encrypted);
  callback->char_results.push_back((char*) nonce);
  callback->completed = true;
  callback->cv.notify_one();
}

void verify_signature_on_verified(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_bool_t verified
) {
  #ifdef INDY_LOG_DEBUG
  printf("verify_signature_on_verified\n");
  #endif

  indy_callback* callback = get_callback(command_handle);
  if (!callback) return;

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->bool_results.push_back(verified);
  callback->completed = true;
  callback->cv.notify_one();
}

void sign_on_signed(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* signature
) {
  #ifdef INDY_LOG_DEBUG
  printf("sign_on_signed\n");
  #endif

  indy_callback* callback = get_callback(command_handle);
  if (!callback) return;

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) signature);
  callback->completed = true;
  callback->cv.notify_one();
}

void store_their_did_on_their_did_stored(
  indy_handle_t command_handle,
  indy_error_t error
) {
  #ifdef INDY_LOG_DEBUG
  printf("store_their_did_on_their_did_stored\n");
  #endif

  indy_callback* callback = get_callback(command_handle);
  if (!callback) return;

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->completed = true;
  callback->cv.notify_one();
}

void replace_keys_on_keys_replaced(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* signing_key,
  const char* encryption_key
) {
  #ifdef INDY_LOG_DEBUG
  printf("replace_keys_on_keys_replaced\n");
  #endif

  indy_callback* callback = get_callback(command_handle);
  if (!callback) return;

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) signing_key);
  callback->char_results.push_back((char*) encryption_key);
  callback->completed = true;
  callback->cv.notify_one();
}

void create_and_store_my_did_on_my_did_created_and_stored(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* did,
  const char* signing_key,
  const char* encryption_key
) {
  #ifdef INDY_LOG_DEBUG
  printf("create_and_store_my_did_on_my_did_created_and_stored\n");
  #endif

  indy_callback* callback = get_callback(command_handle);
  if (!callback) return;

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) did);
  callback->char_results.push_back((char*) signing_key);
  callback->char_results.push_back((char*) encryption_key);
  callback->completed = true;
  callback->cv.notify_one();
}

napi_value decrypt(napi_env env, napi_callback_info info) {
  #ifdef INDY_LOG_DEBUG
  printf("decrypt\n");
  #endif
  
  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(7);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_STRING(argv[5]);
  NAPI_REQUIRED_FUNCTION(argv[6]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], my_did);
  NAPI_STRING_TO_UTF8(argv[3], did);
  NAPI_STRING_TO_UTF8(argv[4], encrypted_msg);
  NAPI_STRING_TO_UTF8(argv[5], nonce);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[6]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_decrypt(
    command_handle,
    wallet_handle,
    my_did,
    did,
    encrypted_msg,
    nonce,
    decrypt_on_decrypted
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value encrypt(napi_env env, napi_callback_info info) {
  #ifdef INDY_LOG_DEBUG
  printf("encrypt\n");
  #endif

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(7);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_NUMBER(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_STRING(argv[5]);
  NAPI_REQUIRED_FUNCTION(argv[6]);

  indy_handle_t command_handle, wallet_handle, pool_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_NUMBER_TO_INT32(argv[2], pool_handle);
  NAPI_STRING_TO_UTF8(argv[3], my_did);
  NAPI_STRING_TO_UTF8(argv[4], did);
  NAPI_STRING_TO_UTF8(argv[5], msg);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[6]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_encrypt(
    command_handle,
    wallet_handle,
    pool_handle,
    my_did,
    did,
    msg,
    encrypt_on_encrypted
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value verify_signature(napi_env env, napi_callback_info info) {
  #ifdef INDY_LOG_DEBUG
  printf("verify_signature\n");
  #endif

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(6);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_NUMBER(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_FUNCTION(argv[5]);

  indy_handle_t command_handle, wallet_handle, pool_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_NUMBER_TO_INT32(argv[2], pool_handle);
  NAPI_STRING_TO_UTF8(argv[3], did);
  NAPI_STRING_TO_UTF8(argv[4], signature);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[5]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_verify_signature(
    command_handle,
    wallet_handle,
    pool_handle,
    did,
    signature,
    verify_signature_on_verified
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value sign(napi_env env, napi_callback_info info) {
  #ifdef INDY_LOG_DEBUG
  printf("sign\n");
  #endif

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(5);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], did);
  NAPI_STRING_TO_UTF8(argv[3], msg);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[4]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_sign(
    command_handle,
    wallet_handle,
    did,
    msg,
    sign_on_signed
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value store_their_did(napi_env env, napi_callback_info info) {
  #ifdef INDY_LOG_DEBUG
  printf("store_their_did\n");
  #endif

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], identity_json);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[3]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_store_their_did(
    command_handle,
    wallet_handle,
    identity_json,
    store_their_did_on_their_did_stored
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value replace_keys(napi_env env, napi_callback_info info) {
  #ifdef INDY_LOG_DEBUG
  printf("replace_keys\n");
  #endif

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(5);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], did);
  NAPI_STRING_TO_UTF8(argv[3], identity_json);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[4]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_replace_keys(
    command_handle,
    wallet_handle,
    did,
    identity_json,
    replace_keys_on_keys_replaced
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value create_and_store_my_did(napi_env env, napi_callback_info info) {
  #ifdef INDY_LOG_DEBUG
  printf("create_and_store_my_did\n");
  #endif

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], did_json);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[3]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_create_and_store_my_did(
    command_handle,
    wallet_handle,
    did_json,
    create_and_store_my_did_on_my_did_created_and_stored
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}