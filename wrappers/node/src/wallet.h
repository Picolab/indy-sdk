
indy_error_t register_wallet_type_on_created(
  const char* name,
  const char* config,
  const char* credentials
) {
  printf("register_wallet_type_on_created\n");
  printf("name %s, config %s, credentials %s\n", name, config, credentials);

  // TODO napi_make_callback
  return Success;
}

indy_error_t register_wallet_type_on_opened(
  const char* name,
  const char* config,
  const char* runtime_config,
  const char* credentials,
  indy_handle_t* handle
) {
  printf("register_wallet_type_on_opened\n");
  printf(
    "name %s, config %s, runtime config %s, credentials %s, handle %d\n",
    name, config, runtime_config, credentials, *(handle)
  );

  // TODO napi_make_callback
  return Success;
}

indy_error_t register_wallet_type_on_set(
  indy_handle_t handle,
  const char* key,
  const char* value
) {
  printf("register_wallet_type_on_set\n");
  printf("handle %d, key %s, value %s\n", handle, key, value);

  // TODO napi_make_callback
  return Success;
}

indy_error_t register_wallet_type_on_got(
  indy_handle_t handle,
  const char* key,
  const char* const *value_ptr
) {
  printf("register_wallet_type_on_got\n");
  printf("handle %d, key %s, value %s\n", handle, key, *(value_ptr));

  // TODO napi_make_callback
  return Success;
}

indy_error_t register_wallet_type_on_not_expired_got(
  indy_handle_t handle,
  const char* key,
  const char *const *value_ptr
) {
  printf("register_wallet_type_on_not_expired_got\n");
  printf("handle %d, key %s, value %s\n", handle, key, *(value_ptr));
  
  // TODO napi_make_callback
  return Success;
}

indy_error_t register_wallet_type_on_listed(
  indy_handle_t handle,
  const char* key,
  const char *const *values_json_ptr
) {
  printf("register_wallet_type_on_listed\n");
  printf("handle %d, key %s, values json %s\n", handle, key, *(values_json_ptr));

  // TODO napi_make_callback
  return Success;
}

indy_error_t register_wallet_type_on_closed(
  indy_handle_t handle
) {
  printf("register_wallet_type_on_closed\n");
  printf("handle %d\n", handle);

  // TODO napi_make_callback
  return Success;
}

indy_error_t register_wallet_type_on_deleted(
  const char* name,
  const char* config,
  const char* credentials
) {
  printf("register_wallet_type_on_deleted\n");
  printf("name %s, config %s, credentials %s\n", name, config, credentials);

  // TODO napi_make_callback
  return Success;
}

indy_error_t register_wallet_type_on_freed(
  indy_handle_t handle,
  const char* str
) {
  printf("register_wallet_type_on_freed\n");
  printf("handle %d, str %s\n", handle, str);

  // TODO napi_make_callback
  return Success;
}

void create_wallet_on_wallet_created(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("create_wallet_on_wallet_created\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void open_wallet_on_wallet_opened(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t wallet_handle
) {
  printf("open_wallet_on_wallet_opened\n");
  printf("command handle %d, error %d, wallet handle %d\n", command_handle, error, wallet_handle);

  // TODO napi_make_callback
}

void close_wallet_on_wallet_closed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("close_wallet_on_wallet_closed\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void delete_wallet_on_wallet_deleted(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("delete_wallet_on_wallet_deleted\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

napi_value register_wallet_type(napi_env env, napi_callback_info info) {
  printf("register_wallet_type\n");

  NAPI_EXPECTING_ARGS(11);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);
  NAPI_REQUIRED_FUNCTION(argv[5]);
  NAPI_REQUIRED_FUNCTION(argv[6]);
  NAPI_REQUIRED_FUNCTION(argv[7]);
  NAPI_REQUIRED_FUNCTION(argv[8]);
  NAPI_REQUIRED_FUNCTION(argv[9]);
  NAPI_REQUIRED_FUNCTION(argv[10]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], wallet_type);

  napi_value result;
  double res = indy_register_wallet_type(
    command_handle,
    wallet_type,
    register_wallet_type_on_created,
    register_wallet_type_on_opened,
    register_wallet_type_on_set,
    register_wallet_type_on_got,
    register_wallet_type_on_not_expired_got,
    register_wallet_type_on_listed,
    register_wallet_type_on_closed,
    register_wallet_type_on_deleted,
    register_wallet_type_on_freed
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value create_wallet(napi_env env, napi_callback_info info) {
  printf("create_wallet\n");

  NAPI_EXPECTING_ARGS(7);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_OPTIONAL_STRING(argv[3]);
  NAPI_OPTIONAL_STRING(argv[4]);
  NAPI_OPTIONAL_STRING(argv[5]);
  NAPI_REQUIRED_FUNCTION(argv[6]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], pool_name);
  NAPI_STRING_TO_UTF8(argv[2], wallet_name);
  NAPI_STRING_TO_UTF8(argv[3], wallet_type);
  NAPI_STRING_TO_UTF8(argv[4], wallet_config_json);
  NAPI_STRING_TO_UTF8(argv[5], wallet_credentials_json);

  napi_value result;
  double res = indy_create_wallet(
    command_handle,
    pool_name,
    wallet_name,
    wallet_type,
    wallet_config_json,
    wallet_credentials_json,
    create_wallet_on_wallet_created
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value open_wallet(napi_env env, napi_callback_info info) {
  printf("open_wallet\n");

  NAPI_EXPECTING_ARGS(5);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_OPTIONAL_STRING(argv[2]);
  NAPI_OPTIONAL_STRING(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], name);
  NAPI_STRING_TO_UTF8(argv[2], runtime_config);
  NAPI_STRING_TO_UTF8(argv[3], credentials);

  napi_value result;
  double res = indy_open_wallet(
    command_handle,
    name,
    runtime_config,
    credentials,
    open_wallet_on_wallet_opened
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value close_wallet(napi_env env, napi_callback_info info) {
  printf("close_wallet\n");

  NAPI_EXPECTING_ARGS(3);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);

  napi_value result;
  double res = indy_close_wallet(
    command_handle,
    wallet_handle,
    close_wallet_on_wallet_closed
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value delete_wallet(napi_env env, napi_callback_info info) {
  printf("delete_wallet\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_OPTIONAL_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], name);
  NAPI_STRING_TO_UTF8(argv[2], credentials);

  napi_value result;
  double res = indy_delete_wallet(
    command_handle,
    name,
    credentials,
    delete_wallet_on_wallet_deleted
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}