
void verifier_verify_proof_on_proof_verified(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_bool_t verified
) {
  printf("verifier_verify_proof_on_proof_verified\n");
  printf("command handle %d, error %d, verified %d\n", command_handle, error, verified);

  // TODO napi_make_callback
}

void prover_create_proof_on_proof_created(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* proof_json
) {
  printf("prover_create_proof_on_proof_created\n");
  printf("command handle %d, error %d, proof json %s\n", command_handle, error, proof_json);
}

void prover_get_claims_for_proof_req_on_claims_for_proof_req_got(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claims_json
) {
  printf("prover_get_claims_for_proof_req_on_claims_for_proof_req_got\n");
  printf("command handle %d, error %d, claims json %s\n", command_handle, error, claims_json);

  // TODO napi_make_callback
}

void prover_get_claims_on_claims_got(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claims_json
) {
  printf("prover_get_claims_on_claims_got\n");
  printf("command handle %d, error %d, claims json %s\n", command_handle, error, claims_json);

  // TODO napi_make_callback
}

void prover_store_claim_on_claim_stored(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("prover_store_claim_on_claim_stored\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void prover_create_and_store_claim_req_on_claim_req_created_and_stored(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claim_req_json
) {
  printf("prover_create_and_store_claim_req_on_claim_req_created_and_stored\n");
  printf("command handle %d, error %d, claim req json %s\n", command_handle, error, claim_req_json);

  // TODO napi_make_callback
}

void prover_create_master_secret_on_master_secret_created(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("prover_create_master_secret_on_master_secret_created\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void prover_get_claim_offers_on_claim_offers_got(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claim_offers_json
) {
  printf("prover_get_claim_offers_on_claim_offers_got\n");
  printf("command handle %d, error %d, claim offers json %s\n", command_handle, error, claim_offers_json);

  // TODO napi_make_callback
}

void prover_store_claim_offer_on_claim_offer_stored(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("prover_store_claim_offer_on_claim_offer_stored\n");
  printf("command handle %d, error %d\n", command_handle, error);
}

void issuer_revoke_claim_on_claim_revoked(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* revoc_reg_update_json
) {
  printf("issuer_revoke_claim_on_claim_revoked\n");
  printf("command handle %d, error %d, revocation reg update json %s\n", command_handle, error, revoc_reg_update_json);

  // TODO napi_make_callback
}

void issuer_create_claim_on_claim_created(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* revoc_reg_update_json,
  const char* claim_json
) {
  printf("issuer_create_claim_on_claim_created\n");
  printf("command handle %d, error %d, revocation reg update json %s, claim json %s\n", command_handle, error, revoc_reg_update_json, claim_json);

  // TODO napi_make_callback
}

void issuer_create_and_store_revoc_reg_on_revoc_reg_created_and_stored(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* revoc_reg_json,
  const char* revoc_reg_uuid
) {
  printf("issuer_create_and_store_revoc_reg_on_revoc_reg_created_and_stored\n");
  printf("command handle %d, error %d, revocation reg json %s, revocation reg uuid %s\n", command_handle, error, revoc_reg_json, revoc_reg_uuid);

  // TODO napi_make_callback
}

void issuer_create_and_store_claim_def_on_claim_def_created_and_stored(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claim_def_json
) {
  printf("issuer_create_and_store_claim_def_on_claim_def_created_and_stored\n");
  printf("command handle %d, error %d, claim def json %s\n", command_handle, error, claim_def_json);

  // TODO napi_make_callback
}

napi_value verifier_verify_proof(napi_env env, napi_callback_info info) {
  printf("verifier_verify_proof\n");

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

  napi_value result;
  double res = indy_verifier_verify_proof(
    command_handle,
    proof_request_json,
    proof_json,
    schemas_json,
    claim_defs_jsons,
    revoc_regs_json,
    verifier_verify_proof_on_proof_verified
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_create_proof(napi_env env, napi_callback_info info) {
  printf("prover_create_proof\n");

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

  napi_value result;
  double res = indy_prover_create_proof(
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

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_get_claims_for_proof_req(napi_env env, napi_callback_info info) {
  printf("prover_get_claims_for_proof_req\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], proof_request_json);

  napi_value result;
  double res = indy_prover_get_claims_for_proof_req(
    command_handle,
    wallet_handle,
    proof_request_json,
    prover_get_claims_for_proof_req_on_claims_for_proof_req_got
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_get_claims(napi_env env, napi_callback_info info) {
  printf("prover_get_claims\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], filter_json);

  napi_value result;
  double res = indy_prover_get_claims(
    command_handle,
    wallet_handle,
    filter_json,
    prover_get_claims_on_claims_got
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_store_claim(napi_env env, napi_callback_info info) {
  printf("prover_store_claim\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], claims_json);

  napi_value result;
  double res = indy_prover_store_claim(
    command_handle,
    wallet_handle,
    claims_json,
    prover_store_claim_on_claim_stored
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value prover_create_and_store_claim_req(napi_env env, napi_callback_info info) {
  printf("prover_create_and_store_claim_req\n");

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

  napi_value result;
  double res = indy_prover_create_and_store_claim_req(
    command_handle,
    wallet_handle,
    prover_did,
    claim_offer_json,
    claim_def_json,
    master_secret_name, prover_create_and_store_claim_req_on_claim_req_created_and_stored
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value prover_create_master_secret(napi_env env, napi_callback_info info) {
  printf("prover_create_master_secret\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], master_secret_name);

  napi_value result;
  double res = indy_prover_create_master_secret(
    command_handle,
    wallet_handle,
    master_secret_name,
    prover_create_master_secret_on_master_secret_created
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value prover_get_claim_offers(napi_env env, napi_callback_info info) {
  printf("prover_get_claim_offers\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_OPTIONAL_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], filter_json);

  napi_value result;
  double res = indy_prover_get_claim_offers(
    command_handle,
    wallet_handle,
    filter_json,
    prover_get_claim_offers_on_claim_offers_got
  );
  
  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value prover_store_claim_offer(napi_env env, napi_callback_info info) {
  printf("prover_store_claim_offer\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_REQUIRED_NUMBER(argv[0]);
  NAPI_REQUIRED_NUMBER(argv[1]);
  NAPI_REQUIRED_STRING(argv[2]);
  NAPI_REQUIRED_FUNCTION(argv[3]);

  indy_handle_t command_handle, wallet_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[2], claim_offer_json);

  napi_value result;
  double res = indy_prover_store_claim_offer(
    command_handle,
    wallet_handle,
    claim_offer_json,
    prover_store_claim_offer_on_claim_offer_stored
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value issuer_revoke_claim(napi_env env, napi_callback_info info) {
  printf("issuer_revoke_claim\n");

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

  napi_value result;
  double res = indy_issuer_revoke_claim(
    command_handle,
    wallet_handle,
    revoc_reg_seq_num,
    user_revoc_index,
    issuer_revoke_claim_on_claim_revoked
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value issuer_create_claim(napi_env env, napi_callback_info info) {
  printf("issuer_create_claim\n");

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

  napi_value result;
  double res = indy_issuer_create_claim(
    command_handle,
    wallet_handle,
    claim_req_json,
    claim_json,
    revoc_req_seq_num,
    user_revoc_index,
    issuer_create_claim_on_claim_created
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value issuer_create_and_store_revoc_reg(napi_env env, napi_callback_info info) {
  printf("issuer_create_and_store_revoc_reg\n");

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

  napi_value result;
  double res = indy_issuer_create_and_store_revoc_reg(
    command_handle,
    wallet_handle,
    issuer_did,
    schema_seq_num,
    max_claim_num,
    issuer_create_and_store_revoc_reg_on_revoc_reg_created_and_stored
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value issuer_create_and_store_claim_def(napi_env env, napi_callback_info info) {
  printf("issuer_create_and_store_claim_def\n");

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

  napi_value result;
  double res = indy_issuer_create_and_store_claim_def(
    command_handle,
    wallet_handle,
    issuer_did,
    schema_json,
    signature_type,
    create_non_revoc,
    issuer_create_and_store_claim_def_on_claim_def_created_and_stored
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}