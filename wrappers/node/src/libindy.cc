
#include <napi.h>
#include <indy_types.h>
#include <indy_core.h>

#include "napi_macros.h"
#include "agent.h"
#include "signus.h"
#include "anoncreds.h"
#include "ledger.h"
#include "pool.h"
#include "wallet.h"

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

napi_value close_pool_ledger(napi_env env, napi_callback_info info) {
  printf("close_pool_ledger\n");
  return NULL;
}

napi_value create_pool_ledger_config(napi_env env, napi_callback_info info) {
  printf("create_pool_ledger_config\n");
  return NULL;
}

napi_value delete_pool_ledger_config(napi_env env, napi_callback_info info) {
  printf("delete_pool_ledger_config\n");
  return NULL;
}

napi_value open_pool_ledger(napi_env env, napi_callback_info info) {
  printf("open_pool_ledger\n");
  return NULL;
}

napi_value refresh_pool_ledger(napi_env env, napi_callback_info info) {
  printf("refresh_pool_ledger\n");
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