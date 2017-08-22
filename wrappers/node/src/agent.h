
void agent_connect_on_connect(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t connection_handle
) {
  printf("agent_connect_on_connect\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->handle_results.push_back(connection_handle);
  callback->completed = true;
  callback->cv.notify_one();
}

// NOTE called multiple times
void agent_connect_on_message(
  indy_handle_t connection_handle,
  indy_error_t error,
  const char* message
) {
  printf("agent_connect_on_message\n");
  indy_callback* callback = get_callback(connection_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) message);
  callback->completed = true;
  callback->cv.notify_one();
}

void agent_listen_on_listening(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t listener_handle
) {
  printf("agent_listen_on_listening\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->handle_results.push_back(listener_handle);
  callback->completed = true;
  callback->cv.notify_one();
}

// NOTE called multiple times
void agent_listen_on_connection(
  indy_handle_t listener_handle,
  indy_error_t error,
  indy_handle_t connection_handle,
  const char* sender_did,
  const char* receiver_did
) {
  printf("agent_listen_on_connection\n");
  indy_callback* callback = get_callback(listener_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->handle_results.push_back(connection_handle);
  callback->char_results.push_back((char*) sender_did);
  callback->char_results.push_back((char*) receiver_did);
  callback->completed = true;
  callback->cv.notify_one();
}

// NOTE called multiple times
void agent_listen_on_message(
  indy_handle_t connection_handle,
  indy_error_t error,
  const char* message
) {
  printf("agent_listen_on_message\n");
  indy_callback* callback = get_callback(connection_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) message);
  callback->completed = true;
  callback->cv.notify_one();
}

void agent_add_identity_on_identity_added(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("agent_add_identity_on_identity_added\n");
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

void agent_remove_identity_on_identity_removed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("agent_remove_identity_on_identity_removed\n");
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

void agent_send_on_message_sent(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("agent_send_on_message_sent\n");
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

void agent_close_connection_on_connection_closed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("agent_close_connection_on_connection_closed\n");
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

void agent_close_listener_on_listener_closed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("agent_close_listener\n");
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

napi_value agent_add_identity(napi_env env, napi_callback_info info) {
  printf("agent_add_identity\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(6);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_NUMBER(argv[2]);
  NAPI_REQUIRED_NUMBER(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_FUNCTION(argv[5]);

  indy_handle_t command_handle, listener_handle, pool_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], listener_handle);
  NAPI_NUMBER_TO_INT32(argv[2], pool_handle);
  NAPI_NUMBER_TO_INT32(argv[3], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[4], did);

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

  res = indy_agent_add_identity(
    command_handle,
    listener_handle,
    pool_handle,
    wallet_handle,
    did,
    agent_add_identity_on_identity_added
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value agent_close_connection(napi_env env, napi_callback_info info) {
  printf("agent_close_connection\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(3);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);

  indy_handle_t command_handle, connection_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], connection_handle);

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
  
  res = indy_agent_close_connection(
    command_handle,
    connection_handle,
    agent_close_connection_on_connection_closed
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value agent_close_listener(napi_env env, napi_callback_info info) {
  printf("agent_close_listener\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(3);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);

  indy_handle_t command_handle, listener_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], listener_handle);

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

  res = indy_agent_close_listener(
    command_handle,
    listener_handle,
    agent_close_listener_on_listener_closed
  );
  
  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value agent_connect(napi_env env, napi_callback_info info) {
  printf("agent_connect\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(7);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_NUMBER(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_FUNCTION(argv[5]);
  NAPI_REQUIRED_FUNCTION(argv[6]);

  indy_handle_t command_handle, pool_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);
  NAPI_NUMBER_TO_INT32(argv[2], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[3], sender_did);
  NAPI_STRING_TO_UTF8(argv[4], receiver_did);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[5]);
  js_callbacks.push_back(argv[6]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  callback->libindy_method = "agent_connect_connect";
  callback->creates_new_callback_from_results = true;

  set_callback(callback);

  res = indy_agent_connect(
    command_handle,
    pool_handle,
    wallet_handle,
    sender_did,
    receiver_did,
    agent_connect_on_connect,
    agent_connect_on_message
  );

  if (res == 0) {
    NAPI_ASYNC_CREATE(task, callback);
    NAPI_ASYNC_START(task);
  } else {
    free_callback(callback->handle);
  }
  
  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value agent_listen(napi_env env, napi_callback_info info) {
  printf("agent_listen\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(5);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_FUNCTION(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], endpoint);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[2]);
  js_callbacks.push_back(argv[3]);
  js_callbacks.push_back(argv[4]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  callback->libindy_method = "agent_listen_listening";
  callback->creates_new_callback_from_results = true;

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_agent_listen(
    command_handle,
    endpoint,
    agent_listen_on_listening,
    agent_listen_on_connection,
    agent_listen_on_message
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }
  
  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value agent_remove_identity(napi_env env, napi_callback_info info) {
  printf("agent_remove_identity\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(5);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_NUMBER(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);

  indy_handle_t command_handle, listener_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], listener_handle);
  NAPI_NUMBER_TO_INT32(argv[2], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[3], did);

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

  res = indy_agent_remove_identity(
    command_handle,
    listener_handle,
    wallet_handle,
    did,
    agent_remove_identity_on_identity_removed
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value agent_send(napi_env env, napi_callback_info info) {
  printf("agent_send\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, connection_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], connection_handle);
  NAPI_STRING_TO_UTF8(argv[2], message);

  std::vector<napi_value> js_callbacks;
  js_callbacks.push_back(argv[3]);
  indy_callback* callback = new_callback(command_handle, env, js_callbacks);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  set_callback(callback);

  res = indy_agent_send(
    command_handle,
    connection_handle,
    message,
    agent_send_on_message_sent
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}