
void verifier_verify_proof_on_proof_verified(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_bool_t verified
) {
  printf("verifier_verify_proof_on_proof_verified\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_bool_results = 1;
  callback->bool_results.push_back(verified);
  callback->completed = true;
  callback->cv.notify_one();
}

void prover_create_proof_on_proof_created(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* proof_json
) {
  printf("prover_create_proof_on_proof_created\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_char_results = 1;
  callback->char_results.push_back((char*) proof_json);
  callback->completed = true;
  callback->cv.notify_one();
}

void prover_get_claims_for_proof_req_on_claims_for_proof_req_got(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claims_json
) {
  printf("prover_get_claims_for_proof_req_on_claims_for_proof_req_got\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_char_results = 1;
  callback->char_results.push_back((char*) claims_json);
  callback->completed = true;
  callback->cv.notify_one();
}

void prover_get_claims_on_claims_got(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claims_json
) {
  printf("prover_get_claims_on_claims_got\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_char_results = 1;
  callback->char_results.push_back((char*) claims_json);
  callback->completed = true;
  callback->cv.notify_one();
}

void prover_store_claim_on_claim_stored(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("prover_store_claim_on_claim_stored\n");
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

void prover_create_and_store_claim_req_on_claim_req_created_and_stored(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claim_req_json
) {
  printf("prover_create_and_store_claim_req_on_claim_req_created_and_stored\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_char_results = 1;
  callback->char_results.push_back((char*) claim_req_json);
  callback->completed = true;
  callback->cv.notify_one();
}

void prover_create_master_secret_on_master_secret_created(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("prover_create_master_secret_on_master_secret_created\n");
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

void prover_get_claim_offers_on_claim_offers_got(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claim_offers_json
) {
  printf("prover_get_claim_offers_on_claim_offers_got\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_char_results = 1;
  callback->char_results.push_back((char*) claim_offers_json);
  callback->completed = true;
  callback->cv.notify_one();
}

void prover_store_claim_offer_on_claim_offer_stored(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("prover_store_claim_offer_on_claim_offer_stored\n");
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

void issuer_revoke_claim_on_claim_revoked(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* revoc_reg_update_json
) {
  printf("issuer_revoke_claim_on_claim_revoked\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_char_results = 1;
  callback->char_results.push_back((char*) revoc_reg_update_json);
  callback->completed = true;
  callback->cv.notify_one();
}

void issuer_create_claim_on_claim_created(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* revoc_reg_update_json,
  const char* claim_json
) {
  printf("issuer_create_claim_on_claim_created\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_char_results = 2;
  callback->char_results.push_back((char*) revoc_reg_update_json);
  callback->char_results.push_back((char*) claim_json);
  callback->completed = true;
  callback->cv.notify_one();
}

void issuer_create_and_store_revoc_reg_on_revoc_reg_created_and_stored(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* revoc_reg_json,
  const char* revoc_reg_uuid
) {
  printf("issuer_create_and_store_revoc_reg_on_revoc_reg_created_and_stored\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_char_results = 2;
  callback->char_results.push_back((char*) revoc_reg_json);
  callback->char_results.push_back((char*) revoc_reg_uuid);
  callback->completed = true;
  callback->cv.notify_one();
}

void issuer_create_and_store_claim_def_on_claim_def_created_and_stored(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claim_def_json
) {
  printf("issuer_create_and_store_claim_def_on_claim_def_created_and_stored\n");
  indy_callback* callback = get_callback(command_handle);
  if (!callback) {
    perror("FATAL pointer to callback struct was null\n");
    exit(1);
  }

  std::lock_guard<std::mutex> lock(callback->mutex);
  callback->error = error;
  callback->n_char_results = 1;
  callback->char_results.push_back((char*) claim_def_json);
  callback->completed = true;
  callback->cv.notify_one();
}

napi_value verifier_verify_proof(napi_env env, napi_callback_info info) {
  printf("verifier_verify_proof\n");

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
  NAPI_STRING_TO_UTF8(argv[1], proof_request_json);
  NAPI_STRING_TO_UTF8(argv[2], proof_json);
  NAPI_STRING_TO_UTF8(argv[3], schemas_json);
  NAPI_STRING_TO_UTF8(argv[4], claim_defs_jsons);
  NAPI_STRING_TO_UTF8(argv[5], revoc_regs_json);

  indy_callback* callback = new_callback(command_handle, env, argv[6]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_verifier_verify_proof(
    command_handle,
    proof_request_json,
    proof_json,
    schemas_json,
    claim_defs_jsons,
    revoc_regs_json,
    verifier_verify_proof_on_proof_verified
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_create_proof(napi_env env, napi_callback_info info) {
  printf("prover_create_proof\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(9);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_REQUIRED_STRING(argv[4]);
  NAPI_REQUIRED_STRING(argv[5]);
  NAPI_REQUIRED_STRING(argv[6]);
  NAPI_REQUIRED_STRING(argv[7]);
  NAPI_REQUIRED_FUNCTION(argv[8]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], proof_req_json);
  NAPI_STRING_TO_UTF8(argv[3], requested_claims_json);
  NAPI_STRING_TO_UTF8(argv[4], schemas_json);
  NAPI_STRING_TO_UTF8(argv[5], master_secret_name);
  NAPI_STRING_TO_UTF8(argv[6], claim_defs_json);
  NAPI_STRING_TO_UTF8(argv[7], revoc_regs_json);

  indy_callback* callback = new_callback(command_handle, env, argv[8]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_prover_create_proof(
    command_handle,
    wallet_handle,
    proof_req_json,
    requested_claims_json,
    schemas_json,
    master_secret_name,
    claim_defs_json,
    revoc_regs_json,
    prover_create_proof_on_proof_created
  );
  
  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_get_claims_for_proof_req(napi_env env, napi_callback_info info) {
  printf("prover_get_claims_for_proof_req\n");
  
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
  NAPI_STRING_TO_UTF8(argv[2], proof_request_json);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_prover_get_claims_for_proof_req(
    command_handle,
    wallet_handle,
    proof_request_json,
    prover_get_claims_for_proof_req_on_claims_for_proof_req_got
  );
  
  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_get_claims(napi_env env, napi_callback_info info) {
  printf("prover_get_claims\n");
  
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
  NAPI_STRING_TO_UTF8(argv[2], filter_json);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_prover_get_claims(
    command_handle,
    wallet_handle,
    filter_json,
    prover_get_claims_on_claims_got
  );
  
  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_store_claim(napi_env env, napi_callback_info info) {
  printf("prover_store_claim\n");
  
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
  NAPI_STRING_TO_UTF8(argv[2], claims_json);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_prover_store_claim(
    command_handle,
    wallet_handle,
    claims_json,
    prover_store_claim_on_claim_stored
  );
  
  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_create_and_store_claim_req(napi_env env, napi_callback_info info) {
  printf("prover_create_and_store_claim_req\n");
  
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
  NAPI_STRING_TO_UTF8(argv[2], prover_did);
  NAPI_STRING_TO_UTF8(argv[3], claim_offer_json);
  NAPI_STRING_TO_UTF8(argv[4], claim_def_json);
  NAPI_STRING_TO_UTF8(argv[5], master_secret_name);
  
  indy_callback* callback = new_callback(command_handle, env, argv[6]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_prover_create_and_store_claim_req(
    command_handle,
    wallet_handle,
    prover_did,
    claim_offer_json,
    claim_def_json,
    master_secret_name, prover_create_and_store_claim_req_on_claim_req_created_and_stored
  );
  
  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_create_master_secret(napi_env env, napi_callback_info info) {
  printf("prover_create_master_secret\n");
  
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
  NAPI_STRING_TO_UTF8(argv[2], master_secret_name);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_prover_create_master_secret(
    command_handle,
    wallet_handle,
    master_secret_name,
    prover_create_master_secret_on_master_secret_created
  );
  
  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_get_claim_offers(napi_env env, napi_callback_info info) {
  printf("prover_get_claim_offers\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_OPTIONAL_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], filter_json);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_prover_get_claim_offers(
    command_handle,
    wallet_handle,
    filter_json,
    prover_get_claim_offers_on_claim_offers_got
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }
  
  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_store_claim_offer(napi_env env, napi_callback_info info) {
  printf("prover_store_claim_offer\n");

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
  NAPI_STRING_TO_UTF8(argv[2], claim_offer_json);

  indy_callback* callback = new_callback(command_handle, env, argv[3]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_prover_store_claim_offer(
    command_handle,
    wallet_handle,
    claim_offer_json,
    prover_store_claim_offer_on_claim_offer_stored
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value issuer_revoke_claim(napi_env env, napi_callback_info info) {
  printf("issuer_revoke_claim\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(5);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_NUMBER(argv[2]);
  NAPI_REQUIRED_NUMBER(argv[3]);
  NAPI_REQUIRED_FUNCTION(argv[4]);

  indy_handle_t command_handle, wallet_handle;
  indy_i32_t revoc_reg_seq_num, user_revoc_index;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_NUMBER_TO_INT32(argv[2], revoc_reg_seq_num);
  NAPI_NUMBER_TO_INT32(argv[3], user_revoc_index);

  indy_callback* callback = new_callback(command_handle, env, argv[4]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_issuer_revoke_claim(
    command_handle,
    wallet_handle,
    revoc_reg_seq_num,
    user_revoc_index,
    issuer_revoke_claim_on_claim_revoked
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value issuer_create_claim(napi_env env, napi_callback_info info) {
  printf("issuer_create_claim\n");
  
  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(7);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_OPTIONAL_NUMBER(argv[4]);
  NAPI_OPTIONAL_NUMBER(argv[5]);
  NAPI_REQUIRED_FUNCTION(argv[6]);

  indy_handle_t command_handle, wallet_handle;
  indy_i32_t revoc_req_seq_num, user_revoc_index;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], claim_req_json);
  NAPI_STRING_TO_UTF8(argv[3], claim_json);
  NAPI_NUMBER_TO_INT32(argv[4], revoc_req_seq_num);
  NAPI_NUMBER_TO_INT32(argv[5], user_revoc_index);

  indy_callback* callback = new_callback(command_handle, env, argv[6]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_issuer_create_claim(
    command_handle,
    wallet_handle,
    claim_req_json,
    claim_json,
    revoc_req_seq_num,
    user_revoc_index,
    issuer_create_claim_on_claim_created
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value issuer_create_and_store_revoc_reg(napi_env env, napi_callback_info info) {
  printf("issuer_create_and_store_revoc_reg\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(6);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_NUMBER(argv[3]);
  NAPI_REQUIRED_NUMBER(argv[4]);
  NAPI_REQUIRED_FUNCTION(argv[5]);

  indy_handle_t command_handle, wallet_handle;
  indy_i32_t schema_seq_num, max_claim_num;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], issuer_did);
  NAPI_NUMBER_TO_INT32(argv[3], schema_seq_num);
  NAPI_NUMBER_TO_INT32(argv[4], max_claim_num);

  indy_callback* callback = new_callback(command_handle, env, argv[5]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_issuer_create_and_store_revoc_reg(
    command_handle,
    wallet_handle,
    issuer_did,
    schema_seq_num,
    max_claim_num,
    issuer_create_and_store_revoc_reg_on_revoc_reg_created_and_stored
  );
  
  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value issuer_create_and_store_claim_def(napi_env env, napi_callback_info info) {
  printf("issuer_create_and_store_claim_def\n");

  napi_value result;
  int res;

  NAPI_EXPECTING_ARGS(7);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_STRING(argv[3]);
  NAPI_OPTIONAL_STRING(argv[4]);
  NAPI_REQUIRED_BOOLEAN(argv[5]);
  NAPI_REQUIRED_FUNCTION(argv[6]);

  indy_handle_t command_handle, wallet_handle;
  bool create_non_revoc;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], issuer_did);
  NAPI_STRING_TO_UTF8(argv[3], schema_json);
  NAPI_STRING_TO_UTF8(argv[4], signature_type);
  NAPI_BOOLEAN_TO_BOOL(argv[5], create_non_revoc);

  indy_callback* callback = new_callback(command_handle, env, argv[6]);
  if (!callback) {
    res = 1;
    NAPI_DOUBLE_TO_NUMBER(res, result);
    return result;
  }

  set_callback(callback);

  NAPI_ASYNC_CREATE(task, callback);
  NAPI_ASYNC_START(task);

  res = indy_issuer_create_and_store_claim_def(
    command_handle,
    wallet_handle,
    issuer_did,
    schema_json,
    signature_type,
    create_non_revoc,
    issuer_create_and_store_claim_def_on_claim_def_created_and_stored
  );

  if (res != 0) {
    NAPI_ASYNC_CANCEL(task);
  }

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}