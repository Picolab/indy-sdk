
void sign_and_submit_request_on_request_signed_and_submitted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_result_json
) {
  printf("sign_and_submit_request_on_request_signed_and_submitted\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_result_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void submit_request_on_request_submitted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_result_json
) {
  printf("submit_request_on_request_submitted\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_result_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_get_ddo_request_on_get_ddo_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_result_json
) {
  printf("build_get_ddo_request_on_get_ddo_request_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_result_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_nym_request_on_nym_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_nym_request_on_nym_request_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_attrib_request_on_attrib_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_attrib_request_on_attrib_request_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_get_attrib_request_on_get_attrib_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_attrib_request_on_get_attrib_request_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_get_nym_request_on_get_nym_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_nym_request_on_get_nym_request_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_schema_request_on_schema_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_schema_request_on_schema_request_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_get_schema_request_on_get_schema_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_schema_request_on_get_schema_request_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_claim_def_txn_on_claim_def_txn_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_claim_def_txn_on_claim_def_txn_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_get_claim_def_txn_on_get_claim_def_txn_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_claim_def_txn_on_get_claim_def_txn_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_node_request_on_node_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_node_request_on_node_request_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

void build_get_txn_request_on_get_txn_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_txn_request_on_get_txn_request_built\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->char_results.push_back((char*) request_json);
  callback->n_char_results = 1;
  callback->completed = true;
  callback->cv.notify_one();
}

napi_value sign_and_submit_request(napi_env env, napi_callback_info info) {
  printf("sign_and_submit_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(6);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_NUMBER(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_FUNCTION(argv[5]);

  indy_handle_t command_handle, pool_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);
  NAPI_NUMBER_TO_INT32(argv[2], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[3], submitter_did);
  NAPI_STRING_TO_UTF8(argv[4], request_json);

  indy_callback* callback = new_callback(command_handle, env, argv[5]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_sign_and_submit_request(
    command_handle,
    pool_handle,
    wallet_handle,
    submitter_did,
    request_json,
    sign_and_submit_request_on_request_signed_and_submitted
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value submit_request(napi_env env, napi_callback_info info) {
  printf("submit_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, pool_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);
  NAPI_STRING_TO_UTF8(argv[2], request_json);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_submit_request(
    command_handle,
    pool_handle,
    request_json,
    submit_request_on_request_submitted
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_get_ddo_request(napi_env env, napi_callback_info info) {
  printf("build_get_ddo_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], target_did);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_get_ddo_request(
    command_handle,
    submitter_did,
    target_did,
    build_get_ddo_request_on_get_ddo_request_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_nym_request(napi_env env, napi_callback_info info) {
  printf("build_nym_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(7);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_STRING(argv[5]);
  NAPI_REQUIRED_FUNCTION(argv[6]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], target_did);
  NAPI_STRING_TO_UTF8(argv[3], verkey);
  NAPI_STRING_TO_UTF8(argv[4], alias);
  NAPI_STRING_TO_UTF8(argv[5], role);

  indy_callback* callback = new_callback(command_handle, env, argv[6]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_nym_request(
    command_handle,
    submitter_did,
    target_did,
    verkey,
    alias,
    role,
    build_nym_request_on_nym_request_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }
  
  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_attrib_request(napi_env env, napi_callback_info info) {
  printf("build_attrib_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(7);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_STRING(argv[5]);
  NAPI_REQUIRED_FUNCTION(argv[6]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], target_did);
  NAPI_STRING_TO_UTF8(argv[3], hash);
  NAPI_STRING_TO_UTF8(argv[4], raw);
  NAPI_STRING_TO_UTF8(argv[5], encrypted);

  indy_callback* callback = new_callback(command_handle, env, argv[6]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_attrib_request(
    command_handle,
    submitter_did,
    target_did,
    hash,
    raw,
    encrypted,
    build_attrib_request_on_attrib_request_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_get_attrib_request(napi_env env, napi_callback_info info) {
  printf("build_get_attrib_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(5);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], target_did);
  NAPI_STRING_TO_UTF8(argv[3], data);

  indy_callback* callback = new_callback(command_handle, env, argv[4]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_get_attrib_request(
    command_handle,
    submitter_did,
    target_did,
    data,
    build_get_attrib_request_on_get_attrib_request_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_get_nym_request(napi_env env, napi_callback_info info) {
  printf("build_get_nym_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], target_did);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_get_nym_request(
    command_handle,
    submitter_did,
    target_did,
    build_get_nym_request_on_get_nym_request_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_schema_request(napi_env env, napi_callback_info info) {
  printf("build_schema_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], data);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_schema_request(
    command_handle,
    submitter_did,
    data,
    build_schema_request_on_schema_request_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_get_schema_request(napi_env env, napi_callback_info info) {
  printf("build_get_schema_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(5);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], dest);
  NAPI_STRING_TO_UTF8(argv[3], data);

  indy_callback* callback = new_callback(command_handle, env, argv[4]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_get_schema_request(
    command_handle,
    submitter_did,
    dest,
    data,
    build_get_schema_request_on_get_schema_request_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_claim_def_txn(napi_env env, napi_callback_info info) {
  printf("build_claim_def_txn\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(6);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_FUNCTION(argv[5]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], schema_seq_num);
  NAPI_STRING_TO_UTF8(argv[3], signature_type);
  NAPI_STRING_TO_UTF8(argv[4], data);

  indy_callback* callback = new_callback(command_handle, env, argv[5]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_claim_def_txn(
    command_handle,
    submitter_did,
    schema_seq_num,
    signature_type,
    data,
    build_claim_def_txn_on_claim_def_txn_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_get_claim_def_txn(napi_env env, napi_callback_info info) {
  printf("build_get_claim_def_txn\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(6);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_FUNCTION(argv[5]);

  indy_handle_t command_handle;
  
  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], schema_seq_num);
  NAPI_STRING_TO_UTF8(argv[3], signature_type);
  NAPI_STRING_TO_UTF8(argv[4], origin);

  indy_callback* callback = new_callback(command_handle, env, argv[5]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_get_claim_def_txn(
    command_handle,
    submitter_did,
    schema_seq_num,
    signature_type,
    origin,
    build_get_claim_def_txn_on_get_claim_def_txn_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_node_request(napi_env env, napi_callback_info info) {
  printf("build_node_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(5);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);

  indy_handle_t command_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], target_did);
  NAPI_STRING_TO_UTF8(argv[3], data);

  indy_callback* callback = new_callback(command_handle, env, argv[4]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_node_request(
    command_handle,
    submitter_did,
    target_did,
    data,
    build_node_request_on_node_request_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_get_txn_request(napi_env env, napi_callback_info info) {
  printf("build_get_txn_request\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_STRING(argv[1]);
  NAPI_REQUIRED_NUMBER(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle;
  indy_i32_t data;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_NUMBER_TO_INT32(argv[2], data);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_build_get_txn_request(
    command_handle,
    submitter_did,
    data,
    build_get_txn_request_on_get_txn_request_built
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}