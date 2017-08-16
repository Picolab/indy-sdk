
void decrypt_on_decrypted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* decrypted
) {
  printf("decrypt_on_decrypted\n");
  printf("command handle %d, error %d, decrypted %s\n", command_handle, error, decrypted);

  // TODO napi_make_callback
}

void encrypt_on_encrypted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* encrypted,
  const char* nonce
) {
  printf("encrypt_on_encrypted\n");
  printf("command handle %d, error %d, encrypted %s, nonce %s\n", command_handle, error, encrypted, nonce);

  // TODO napi_make_callback
}

void verify_signature_on_verified(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_bool_t verified
) {
  printf("verify_signature_on_verified\n");
  printf("command handle %d, error %d, verified %d\n", command_handle, error, verified);

  // TODO napi_make_callback
}

void sign_on_signed(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* signature
) {
  printf("sign_on_signed\n");
  printf("command handle %d, error %d, signature %s\n", command_handle, error, signature);

  // TODO napi_make_callback
}

void store_their_did_on_their_did_stored(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("store_their_did_on_their_did_stored\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void replace_keys_on_keys_replaced(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* signing_key,
  const char* encryption_key
) {
  printf("replace_keys_on_keys_replaced\n");
  printf("command handle %d, error %d, signing key %s, encryption key %s\n", command_handle, error, signing_key, encryption_key);

  // TODO napi_make_callback
}

void create_and_store_my_did_on_my_did_created_and_stored(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* did,
  const char* signing_key,
  const char* encryption_key
) {
  printf("create_and_store_my_did_on_my_did_created_and_stored\n");
  printf("command handle %d, error %d, did %s, signing key %s, encryption key %s\n", command_handle, error, did, signing_key, encryption_key);

  // TODO napi_make_callback
}

napi_value decrypt(napi_env env, napi_callback_info info) {
  printf("decrypt\n");

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

  napi_value result;
  double res = indy_decrypt(
    command_handle,
    wallet_handle,
    my_did,
    did,
    encrypted_msg,
    nonce,
    decrypt_on_decrypted
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value encrypt(napi_env env, napi_callback_info info) {
  printf("encrypt\n");

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

  napi_value result;
  double res = indy_encrypt(
    command_handle,
    wallet_handle,
    pool_handle,
    my_did,
    did,
    msg,
    encrypt_on_encrypted
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value verify_signature(napi_env env, napi_callback_info info) {
  printf("verify_signature\n");

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

  napi_value result;
  double res = indy_verify_signature(
    command_handle,
    wallet_handle,
    pool_handle,
    did,
    signature,
    verify_signature_on_verified
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value sign(napi_env env, napi_callback_info info) {
  printf("sign\n");

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

  napi_value result;
  double res = indy_sign(
    command_handle,
    wallet_handle,
    did,
    msg,
    sign_on_signed
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value store_their_did(napi_env env, napi_callback_info info) {
  printf("store_their_did\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], identity_json);

  napi_value result;
  double res = indy_store_their_did(
    command_handle,
    wallet_handle,
    identity_json,
    store_their_did_on_their_did_stored
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value replace_keys(napi_env env, napi_callback_info info) {
  printf("replace_keys\n");

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

  napi_value result;
  double res = indy_replace_keys(
    command_handle,
    wallet_handle,
    did,
    identity_json,
    replace_keys_on_keys_replaced
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value create_and_store_my_did(napi_env env, napi_callback_info info) {
  printf("create_and_store_my_did\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], did_json);

  napi_value result;
  double res = indy_create_and_store_my_did(
    command_handle,
    wallet_handle,
    did_json,
    create_and_store_my_did_on_my_did_created_and_stored
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}