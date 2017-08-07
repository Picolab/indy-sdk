
#include <napi.h>

#include <indy_types.h>
#include <indy_core.h>

#include "napi_macros.h"

struct async_work_data {
  char* indy_function_name;
  indy_error_t err;
  indy_handle_t listener_handle;
  indy_handle_t command_handle;
  indy_handle_t pool_handle;
  indy_handle_t wallet_handle;
  char* res;
  napi_ref user_callback_ref;
};

typedef struct async_work_data async_work_data;

void agent_connect_on_connect(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t connection_handle
) {
  // invoke user callback mapped to command_handle
  printf("agent_connect_on_connect\n");
  printf(
    "command handle %d, error %d, connection handle %d\n",
    command_handle,
    error,
    connection_handle
  );

  // TODO napi_make_callback
}

void agent_connect_on_message(
  indy_handle_t connection_handle,
  indy_error_t error,
  const char* message
) {
  printf("agent_connect_on_message\n");
  printf(
    "connection handle %d, error %d, message %s\n",
    connection_handle,
    error,
    message
  );
  
  // TODO napi_make_callback
}

void agent_listen_on_listening(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t listener_handle
) {
  printf("agent_listen_on_listening\n");
  printf(
    "command handle %d, error %d, listener handle %d\n",
    command_handle,
    error,
    listener_handle
  );

  // TODO napi_make_callback
}

void agent_listen_on_connection(
  indy_handle_t listener_handle,
  indy_error_t error,
  indy_handle_t connection_handle,
  const char* sender_did,
  const char* receiver_did
) {
  printf("agent_listen_on_connection\n");
  printf(
    "listener handle %d, error %d, connection handle %d, sender did %s, receiver did %s\n",
    listener_handle,
    error,
    connection_handle,
    sender_did,
    receiver_did
  );
  
  // TODO napi_make_callback
}

void agent_listen_on_message(
  indy_handle_t connection_handle,
  indy_error_t error,
  const char* message
) {
  printf("agent_listen_on_message\n");
  printf("connection handle %d, error %d, message %s\n", connection_handle, error, message);

  // TODO napi_make_callback
}

void agent_add_identity_on_identity_added(indy_handle_t command_handle, indy_error_t error) {
  printf("agent_add_identity_on_identity_added\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void agent_remove_identity_on_identity_removed(indy_handle_t command_handle, indy_error_t error) {
  printf("agent_remove_identity_on_identity_removed\n");
  printf("command handle %d, error %d\n", command_handle, error);
  
  // TODO napi_make_callback
}

napi_value agent_add_identity(napi_env env, napi_callback_info info) {
  printf("agent_add_identity\n");

  NAPI_EXPECTING_ARGS(6);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_NUMBER(argv[1]);
  NAPI_ENSURE_NUMBER(argv[2]);
  NAPI_ENSURE_NUMBER(argv[3]);
  NAPI_ENSURE_STRING(argv[4]);
  NAPI_ENSURE_FUNCTION(argv[5]);

  indy_handle_t command_handle, listener_handle, pool_handle, wallet_handle;
  size_t string_length, written;
  char* did = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], listener_handle);
  NAPI_NUMBER_TO_INT32(argv[2], pool_handle);
  NAPI_NUMBER_TO_INT32(argv[3], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[4], did);

  // TODO store ref to user callback(s) and heap allocate a data context

  double res = indy_agent_add_identity(
    command_handle,
    listener_handle,
    pool_handle,
    wallet_handle,
    did,
    agent_add_identity_on_identity_added
  );

  napi_value result;
  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value agent_close_connection(napi_env env, napi_callback_info info) {
  printf("agent_close_connection\n");
  return NULL;
}

napi_value agent_close_listener(napi_env env, napi_callback_info info) {
  printf("agent_close_listener\n");
  return NULL;
}

napi_value agent_connect(napi_env env, napi_callback_info info) {
  printf("agent_connect\n");
  
  NAPI_EXPECTING_ARGS(7);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_NUMBER(argv[1]);
  NAPI_ENSURE_NUMBER(argv[2]);
  NAPI_ENSURE_STRING(argv[3]);
  NAPI_ENSURE_STRING(argv[4]);
  NAPI_ENSURE_FUNCTION(argv[5]);
  NAPI_ENSURE_FUNCTION(argv[6]);

  indy_handle_t command_handle, pool_handle, wallet_handle;
  size_t string_length, written;
  char* sender_did = 0;
  char* receiver_did = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);
  NAPI_NUMBER_TO_INT32(argv[2], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[3], sender_did);
  NAPI_STRING_TO_UTF8(argv[4], receiver_did);

  // TODO store ref to user callback(s) and heap allocate a data context

  double res = indy_agent_connect(
    command_handle,
    pool_handle,
    wallet_handle,
    sender_did,
    receiver_did,
    agent_connect_on_connect,
    agent_connect_on_message
  );
  napi_value result;
  NAPI_DOUBLE_TO_NUMBER(res, result);
  // double to_convert = res;
  // status = napi_create_number(env, to_convert, &result);
  // NAPI_CHECK_STATUS("napi_create_number");
  return result;
}

napi_value agent_listen(napi_env env, napi_callback_info info) {
  printf("agent_listen\n");

  NAPI_EXPECTING_ARGS(5);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_STRING(argv[1]);
  NAPI_ENSURE_FUNCTION(argv[2]);
  NAPI_ENSURE_FUNCTION(argv[3]);
  NAPI_ENSURE_FUNCTION(argv[4]);

  indy_handle_t command_handle;
  size_t string_length, written;
  char* endpoint = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], endpoint);

  // TODO store ref to user callback(s) and heap allocate a data context

  double res = indy_agent_listen(
    command_handle,
    endpoint,
    agent_listen_on_listening,
    agent_listen_on_connection,
    agent_listen_on_message
  );
  
  napi_value result;
  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value agent_remove_identity(napi_env env, napi_callback_info info) {
  printf("agent_remove_identity\n");

  NAPI_EXPECTING_ARGS(5);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_NUMBER(argv[1]);
  NAPI_ENSURE_NUMBER(argv[2]);
  NAPI_ENSURE_STRING(argv[3]);
  NAPI_ENSURE_FUNCTION(argv[4]);

  indy_handle_t command_handle, listener_handle, wallet_handle;
  size_t string_length, written;
  char* did = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], listener_handle);
  NAPI_NUMBER_TO_INT32(argv[2], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[3], did);

  double res = indy_agent_remove_identity(
    command_handle,
    listener_handle,
    wallet_handle,
    did,
    agent_remove_identity_on_identity_removed
  );

  napi_value result;
  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value agent_send(napi_env env, napi_callback_info info) {
  printf("agent_send\n");
  return NULL;
}

napi_value build_attrib_request(napi_env env, napi_callback_info info) {
  printf("build_attrib_request\n");
  return NULL;
}

napi_value build_claim_def_txn(napi_env env, napi_callback_info info) {
  printf("build_claim_def_txn\n");
  return NULL;
}

napi_value build_get_attrib_request(napi_env env, napi_callback_info info) {
  printf("build_get_attrib_request\n");
  return NULL;
}

napi_value build_get_claim_def_txn(napi_env env, napi_callback_info info) {
  printf("build_get_claim_def_txn\n");
  return NULL;
}

napi_value build_get_ddo_request(napi_env env, napi_callback_info info) {
  printf("build_get_ddo_request\n");
  return NULL;
}

napi_value build_get_nym_request(napi_env env, napi_callback_info info) {
  printf("build_get_nym_request\n");
  return NULL;
}

napi_value build_get_schema_request(napi_env env, napi_callback_info info) {
  printf("build_get_schema_request\n");
  return NULL;
}

napi_value build_get_txn_request(napi_env env, napi_callback_info info) {
  printf("build_get_txn_request\n");
  return NULL;
}

napi_value build_node_request(napi_env env, napi_callback_info info) {
  printf("build_node_request\n");
  return NULL;
}

napi_value build_nym_request(napi_env env, napi_callback_info info) {
  printf("build_nym_request\n");
  return NULL;
}

napi_value build_schema_request(napi_env env, napi_callback_info info) {
  printf("build_schema_request\n");
  return NULL;
}

napi_value close_pool_ledger(napi_env env, napi_callback_info info) {
  printf("close_pool_ledger\n");
  return NULL;
}

napi_value close_wallet(napi_env env, napi_callback_info info) {
  printf("close_wallet\n");
  return NULL;
}

napi_value create_and_store_my_did(napi_env env, napi_callback_info info) {
  printf("create_and_store_my_did\n");
  return NULL;
}

napi_value create_pool_ledger_config(napi_env env, napi_callback_info info) {
  printf("create_pool_ledger_config\n");
  return NULL;
}

napi_value create_wallet(napi_env env, napi_callback_info info) {
  printf("create_wallet\n");
  return NULL;
}

napi_value decrypt(napi_env env, napi_callback_info info) {
  printf("decrypt\n");
  return NULL;
}

napi_value delete_pool_ledger_config(napi_env env, napi_callback_info info) {
  printf("delete_pool_ledger_config\n");
  return NULL;
}

napi_value delete_wallet(napi_env env, napi_callback_info info) {
  printf("delete_wallet\n");
  return NULL;
}

napi_value encrypt(napi_env env, napi_callback_info info) {
  printf("encrypt\n");
  return NULL;
}

napi_value issuer_create_and_store_claim_def(napi_env env, napi_callback_info info) {
  printf("issuer_create_and_store_claim_def\n");
  return NULL;
}

napi_value issuer_create_and_store_revoc_reg(napi_env env, napi_callback_info info) {
  printf("issuer_create_and_store_revoc_reg\n");
  return NULL;
}

napi_value issuer_create_claim(napi_env env, napi_callback_info info) {
  printf("issuer_create_claim\n");
  return NULL;
}

napi_value issuer_revoke_claim(napi_env env, napi_callback_info info) {
  printf("issuer_revoke_claim\n");
  return NULL;
}

napi_value open_pool_ledger(napi_env env, napi_callback_info info) {
  printf("open_pool_ledger\n");
  return NULL;
}

napi_value open_wallet(napi_env env, napi_callback_info info) {
  printf("open_wallet\n");
  return NULL;
}

napi_value prover_create_and_store_claim_req(napi_env env, napi_callback_info info) {
  printf("prover_create_and_store_claim_req\n");
  return NULL;
}

napi_value prover_create_master_secret(napi_env env, napi_callback_info info) {
  printf("prover_create_master_secret\n");
  return NULL;
}

napi_value prover_create_proof(napi_env env, napi_callback_info info) {
  printf("prover_create_proof\n");
  return NULL;
}

napi_value prover_get_claim_offers(napi_env env, napi_callback_info info) {
  printf("prover_get_claim_offers\n");
  return NULL;
}

napi_value prover_get_claims(napi_env env, napi_callback_info info) {
  printf("prover_get_claims\n");
  return NULL;
}

napi_value prover_get_claims_for_proof_req(napi_env env, napi_callback_info info) {
  printf("prover_get_claims_for_proof_req\n");
  return NULL;
}

napi_value prover_store_claim(napi_env env, napi_callback_info info) {
  printf("prover_store_claim\n");
  return NULL;
}

napi_value prover_store_claim_offer(napi_env env, napi_callback_info info) {
  printf("prover_store_claim_offer\n");
  return NULL;
}

napi_value refresh_pool_ledger(napi_env env, napi_callback_info info) {
  printf("refresh_pool_ledger\n");
  return NULL;
}

napi_value register_wallet_type(napi_env env, napi_callback_info info) {
  printf("register_wallet_type\n");
  return NULL;
}

napi_value replace_keys(napi_env env, napi_callback_info info) {
  printf("replace_keys\n");
  return NULL;
}

napi_value sign(napi_env env, napi_callback_info info) {
  printf("sign\n");
  return NULL;
}

napi_value sign_and_submit_request(napi_env env, napi_callback_info info) {
  printf("sign_and_submit_request\n");
  return NULL;
}

napi_value store_their_did(napi_env env, napi_callback_info info) {
  printf("store_their_did\n");
  return NULL;
}

napi_value submit_request(napi_env env, napi_callback_info info) {
  printf("submit_request\n");
  return NULL;
}

napi_value verifier_verify_proof(napi_env env, napi_callback_info info) {
  printf("verifier_verify_proof\n");
  return NULL;
}

napi_value verify_signature(napi_env env, napi_callback_info info) {
  printf("verify_signature\n");
  return NULL;
}


void init(
  napi_env env,
  napi_value exports,
  napi_value module,
  void* priv
) {
  printf("libindy init\n");

  napi_status status;
  napi_value fn;

  NAPI_DEFINE_METHOD("agent_add_identity", agent_add_identity);
  NAPI_DEFINE_METHOD("agent_close_connection", agent_close_connection);
  NAPI_DEFINE_METHOD("agent_close_listener", agent_close_listener);
  NAPI_DEFINE_METHOD("agent_connect", agent_connect);
  NAPI_DEFINE_METHOD("agent_listen", agent_listen);
  NAPI_DEFINE_METHOD("agent_remove_identity", agent_remove_identity);
  NAPI_DEFINE_METHOD("agent_send", agent_send);
  NAPI_DEFINE_METHOD("build_attrib_request", build_attrib_request);
  NAPI_DEFINE_METHOD("build_claim_def_txn", build_claim_def_txn);
  NAPI_DEFINE_METHOD("build_get_attrib_request", build_get_attrib_request);
  NAPI_DEFINE_METHOD("build_get_claim_def_txn", build_get_claim_def_txn);
  NAPI_DEFINE_METHOD("build_get_ddo_request", build_get_ddo_request);
  NAPI_DEFINE_METHOD("build_get_nym_request", build_get_nym_request);
  NAPI_DEFINE_METHOD("build_get_schema_request", build_get_schema_request);
  NAPI_DEFINE_METHOD("build_get_txn_request", build_get_txn_request);
  NAPI_DEFINE_METHOD("build_node_request", build_node_request);
  NAPI_DEFINE_METHOD("build_nym_request", build_nym_request);
  NAPI_DEFINE_METHOD("build_schema_request", build_schema_request);
  NAPI_DEFINE_METHOD("close_pool_ledger", close_pool_ledger);
  NAPI_DEFINE_METHOD("close_wallet", close_wallet);
  NAPI_DEFINE_METHOD("create_and_store_my_did", create_and_store_my_did);
  NAPI_DEFINE_METHOD("create_pool_ledger_config", create_pool_ledger_config);
  NAPI_DEFINE_METHOD("create_wallet", create_wallet);
  NAPI_DEFINE_METHOD("decrypt", decrypt);
  NAPI_DEFINE_METHOD("delete_pool_ledger_config", delete_pool_ledger_config);
  NAPI_DEFINE_METHOD("delete_wallet", delete_wallet);
  NAPI_DEFINE_METHOD("encrypt", encrypt);
  NAPI_DEFINE_METHOD("issuer_create_and_store_claim_def", issuer_create_and_store_claim_def);
  NAPI_DEFINE_METHOD("issuer_create_and_store_revoc_reg", issuer_create_and_store_revoc_reg);
  NAPI_DEFINE_METHOD("issuer_create_claim", issuer_create_claim);
  NAPI_DEFINE_METHOD("issuer_revoke_claim", issuer_revoke_claim);
  NAPI_DEFINE_METHOD("open_pool_ledger", open_pool_ledger);
  NAPI_DEFINE_METHOD("open_wallet", open_wallet);
  NAPI_DEFINE_METHOD("prover_create_and_store_claim_req", prover_create_and_store_claim_req);
  NAPI_DEFINE_METHOD("prover_create_master_secret", prover_create_master_secret);
  NAPI_DEFINE_METHOD("prover_create_proof", prover_create_proof);
  NAPI_DEFINE_METHOD("prover_get_claim_offers", prover_get_claim_offers);
  NAPI_DEFINE_METHOD("prover_get_claims", prover_get_claims);
  NAPI_DEFINE_METHOD("prover_get_claims_for_proof_req", prover_get_claims_for_proof_req);
  NAPI_DEFINE_METHOD("prover_store_claim", prover_store_claim);
  NAPI_DEFINE_METHOD("prover_store_claim_offer", prover_store_claim_offer);
  NAPI_DEFINE_METHOD("refresh_pool_ledger", refresh_pool_ledger);
  NAPI_DEFINE_METHOD("register_wallet_type", register_wallet_type);
  NAPI_DEFINE_METHOD("replace_keys", replace_keys);
  NAPI_DEFINE_METHOD("sign", sign);
  NAPI_DEFINE_METHOD("sign_and_submit_request", sign_and_submit_request);
  NAPI_DEFINE_METHOD("store_their_did", store_their_did);
  NAPI_DEFINE_METHOD("submit_request", submit_request);
  NAPI_DEFINE_METHOD("verifier_verify_proof", verifier_verify_proof);
  NAPI_DEFINE_METHOD("verify_signature", verify_signature);
}

NAPI_MODULE(libindy, init);