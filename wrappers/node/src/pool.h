
void create_pool_ledger_config_on_pool_ledger_config_created(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("create_pool_ledger_config_on_pool_ledger_config_created\n");
  // printf("command handle %d, error %d\n", command_handle, error);

  indy_callback* callback = get_callback(command_handle);

  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  callback->error = error;
  callback->completed = true;
  printf("config_created completed = true\n");
}

void open_pool_ledger_on_pool_ledger_opened(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t pool_handle
) {
  printf("open_pool_ledger_on_pool_ledger_opened\n");
  // printf("command handle %d, error %d, pool handle %d\n", command_handle, error, pool_handle);

  indy_callback* callback = get_callback(command_handle);
  if (callback == NULL) {
    printf("FATAL pointer to callback struct was null\n");
    return;
  }

  callback->error = error;
  callback->handle_results[0] = pool_handle;
  callback->n_handle_results = 1;
  callback->completed = true;
  printf("ledger_opened completed = true\n");
}

void refresh_pool_ledger_on_pool_ledger_refreshed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("refresh_pool_ledger_on_pool_ledger_refreshed\n");
  // printf("command handle %d, error %d\n", command_handle, error);

  indy_callback* callback = get_callback(command_handle);

  if (callback == NULL) {
    printf("FATAL pointer to callback struct was null\n");
    return;
  }

  callback->error = error;
  callback->completed = true;
  printf("ledger_refreshed completed = true\n");
}

void close_pool_ledger_on_pool_ledger_closed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("close_pool_ledger_on_pool_ledger_closed\n");
  // printf("command handle %d, error %d\n", command_handle, error);

  indy_callback* callback = get_callback(command_handle);

  if (callback == NULL) {
    printf("FATAL pointer to callback struct was null\n");
    return;
  }

  callback->error = error;
  callback->completed = true;
  printf("ledger_closed completed = true\n");
}

void delete_pool_ledger_config_on_pool_ledger_config_deleted(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("delete_pool_ledger_config_on_pool_ledger_config_deleted\n");
  // printf("command handle %d, error %d\n", command_handle, error);

  indy_callback* callback = get_callback(command_handle);
  if (callback == NULL) {
    printf("FATAL pointer to callback struct was null\n");
    return;
  }

  callback->error = error;
  callback->completed = true;
  printf("config_deleted completed = true\n");
}

napi_value create_pool_ledger_config(napi_env env, napi_callback_info info) {
  printf("create_pool_ledger_config\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_OPTIONAL_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], config_name);
  NAPI_STRING_TO_UTF8(argv[2], config);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);

  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }
  
  set_callback(callback);

  res = indy_create_pool_ledger_config(
    command_handle,
    config_name,
    config,
    create_pool_ledger_config_on_pool_ledger_config_created
  );

  if (res == 0) {
    NAPI_ASYNC_CREATE(task, callback);
    NAPI_ASYNC_START(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value open_pool_ledger(napi_env env, napi_callback_info info) {
  printf("open_pool_ledger\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_OPTIONAL_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], config_name);
  NAPI_STRING_TO_UTF8(argv[2], config);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  set_callback(callback);

  napi_value result;
  double res = indy_open_pool_ledger(
    command_handle,
    config_name,
    config,
    open_pool_ledger_on_pool_ledger_opened
  );

  if (res == 0) {
    NAPI_ASYNC_CREATE(task, callback);
    NAPI_ASYNC_START(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value refresh_pool_ledger(napi_env env, napi_callback_info info) {
  printf("refresh_pool_ledger\n");

  NAPI_EXPECTING_ARGS(3);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);

  indy_handle_t command_handle, pool_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);

  indy_callback* callback = new_callback(command_handle, env, argv[2]);
  set_callback(callback);

  napi_value result;
  double res = indy_refresh_pool_ledger(
    command_handle,
    pool_handle,
    refresh_pool_ledger_on_pool_ledger_refreshed
  );

  if (res == 0) {
    NAPI_ASYNC_CREATE(task, callback);
    NAPI_ASYNC_START(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value close_pool_ledger(napi_env env, napi_callback_info info) {
  printf("close_pool_ledger\n");

  NAPI_EXPECTING_ARGS(3);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);

  indy_handle_t command_handle, pool_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);

  indy_callback* callback = new_callback(command_handle, env, argv[2]);
  set_callback(callback);

  napi_value result;
  double res = indy_close_pool_ledger(
    command_handle,
    pool_handle,
    close_pool_ledger_on_pool_ledger_closed
  );

  if (res == 0) {
    NAPI_ASYNC_CREATE(task, callback);
    NAPI_ASYNC_START(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value delete_pool_ledger_config(napi_env env, napi_callback_info info) {
  printf("delete_pool_ledger_config\n");
  
  NAPI_EXPECTING_ARGS(3);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], config_name);

  indy_callback* callback = new_callback(command_handle, env, argv[2]);
  set_callback(callback);

  napi_value result;
  double res = indy_delete_pool_ledger_config(
    command_handle,
    config_name,
    delete_pool_ledger_config_on_pool_ledger_config_deleted
  );

  if (res == 0) {
    NAPI_ASYNC_CREATE(task, callback);
    NAPI_ASYNC_START(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}