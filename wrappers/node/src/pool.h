
void create_pool_ledger_config_on_pool_ledger_config_created(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("create_pool_ledger_config_on_pool_ledger_config_created\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->completed = true;
  callback->cv.notify_one();
}

void open_pool_ledger_on_pool_ledger_opened(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t pool_handle
) {
  printf("open_pool_ledger_on_pool_ledger_opened\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    printf("FATAL pointer to callback struct was null\n");
    return;
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->handle_results.push_back(pool_handle);
  callback->completed = true;
  callback->cv.notify_one();
}

void refresh_pool_ledger_on_pool_ledger_refreshed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("refresh_pool_ledger_on_pool_ledger_refreshed\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    printf("FATAL pointer to callback struct was null\n");
    return;
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->completed = true;
  callback->cv.notify_one();
}

void close_pool_ledger_on_pool_ledger_closed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("close_pool_ledger_on_pool_ledger_closed\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    printf("FATAL pointer to callback struct was null\n");
    return;
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->completed = true;
  callback->cv.notify_one();
}

void delete_pool_ledger_config_on_pool_ledger_config_deleted(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("delete_pool_ledger_config_on_pool_ledger_config_deleted\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    printf("FATAL pointer to callback struct was null\n");
    return;
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->completed = true;
  callback->cv.notify_one();
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

  res = indy_create_pool_ledger_config(
    command_handle,
    config_name,
    config,
    create_pool_ledger_config_on_pool_ledger_config_created
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value open_pool_ledger(napi_env env, napi_callback_info info) {
  printf("open_pool_ledger\n");

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

  res = indy_open_pool_ledger(
    command_handle,
    config_name,
    config,
    open_pool_ledger_on_pool_ledger_opened
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value refresh_pool_ledger(napi_env env, napi_callback_info info) {
  printf("refresh_pool_ledger\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(3);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);

  indy_handle_t command_handle, pool_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[2]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_refresh_pool_ledger(
    command_handle,
    pool_handle,
    refresh_pool_ledger_on_pool_ledger_refreshed
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value close_pool_ledger(napi_env env, napi_callback_info info) {
  printf("close_pool_ledger\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(3);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);

  indy_handle_t command_handle, pool_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[2]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_close_pool_ledger(
    command_handle,
    pool_handle,
    close_pool_ledger_on_pool_ledger_closed
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value delete_pool_ledger_config(napi_env env, napi_callback_info info) {
  printf("delete_pool_ledger_config\n");
  
  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(3);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], config_name);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[2]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_delete_pool_ledger_config(
    command_handle,
    config_name,
    delete_pool_ledger_config_on_pool_ledger_config_deleted
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}