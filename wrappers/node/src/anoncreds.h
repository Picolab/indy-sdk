
#include <napi.h>

#include <indy_types.h>
#include <indy_core.h>

#include "napi_macros.h"

void verifier_verify_proof_on_proof_verified(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_bool_t verified
) {
  printf("verifier_verify_proof_on_proof_verified\n");
  printf("command handle %d, error %d, verified %d\n");

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

void prover_get_claims_for_proof_req_on_claims_for_proof_req_gotten(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claims_json
) {
  printf("prover_get_claims_for_proof_req_on_claims_for_proof_req_gotten\n");
  printf("command handle %d, error %d, claims json %s\n", command_handle, error, claims_json);

  // TODO napi_make_callback
}

void prover_get_claims_on_claims_gotten(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claims_json
) {
  printf("prover_get_claims_on_claims_gotten\n");
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

void prover_get_claim_offers_on_claim_offers_gotten(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* claim_offers_json
) {
  printf("prover_get_claim_offers_on_claim_offers_gotten\n");
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

napi_value verifier_verify_proof(napi_env env, napi_callback_info info) {
  printf("verifier_verify_proof\n");

  // indy_handle_t command_handle,
  // const char *    proof_request_json,
  // const char *    proof_json,
  // const char *    schemas_json,
  // const char *    claim_defs_jsons,
  // const char *    revoc_regs_json

  return NULL;
}

napi_value prover_create_proof(napi_env env, napi_callback_info info) {
  printf("prover_create_proof\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    proof_req_json,
  // const char *    requested_claims_json,
  // const char *    schemas_json,
  // const char *    master_secret_name,
  // const char *    claim_defs_json,
  // const char *    revoc_regs_json

  return NULL;
}

napi_value prover_get_claims_for_proof_req(napi_env env, napi_callback_info info) {
  printf("prover_get_claims_for_proof_req\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    proof_request_json

  return NULL;
}

napi_value prover_get_claims(napi_env env, napi_callback_info info) {
  printf("prover_get_claims\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    filter_json

  return NULL;
}

napi_value prover_store_claim(napi_env env, napi_callback_info info) {
  printf("prover_store_claim\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    claims_json

  return NULL;
}

napi_value prover_create_and_store_claim_req(napi_env env, napi_callback_info info) {
  printf("prover_create_and_store_claim_req\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    prover_did,
  // const char *    claim_offer_json,
  // const char *    claim_def_json,
  // const char *    master_secret_name

  return NULL;
}

napi_value prover_create_master_secret(napi_env env, napi_callback_info info) {
  printf("prover_create_master_secret\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    master_secret_name

  return NULL;
}

napi_value prover_get_claim_offers(napi_env env, napi_callback_info info) {
  printf("prover_get_claim_offers\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *filter_json

  return NULL;
}

napi_value prover_store_claim_offer(napi_env env, napi_callback_info info) {
  printf("prover_store_claim_offer\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    claim_offer_json

  return NULL;
}

napi_value issuer_revoke_claim(napi_env env, napi_callback_info info) {
  printf("issuer_revoke_claim\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // indy_i32_t    revoc_reg_seq_no,
  // indy_i32_t    user_revoc_index

  return NULL;
}

napi_value issuer_create_claim(napi_env env, napi_callback_info info) {
  printf("issuer_create_claim\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    claim_req_json,
  // const char *    claim_json,
  // indy_i32_t    revoc_reg_seq_no,
  // indy_i32_t    user_revoc_index

  return NULL;
}

napi_value issuer_create_and_store_revoc_reg(napi_env env, napi_callback_info info) {
  printf("issuer_create_and_store_revoc_reg\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    issuer_did,
  // indy_i32_t    schema_seq_no,
  // indy_i32_t    max_claim_num

  return NULL;
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

napi_value issuer_create_and_store_claim_def(napi_env env, napi_callback_info info) {
  printf("issuer_create_and_store_claim_def\n");

  // indy_handle_t command_handle,
  // indy_handle_t wallet_handle,
  // const char *    issuer_did,
  // const char *    schema_json,
  // const char *    signature_type,
  // indy_bool_t   create_non_revoc

  return NULL;
}