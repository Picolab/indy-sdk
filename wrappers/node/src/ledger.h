
#include <napi.h>

#include <indy_types.h>
#include <indy_core.h>

#include "napi_macros.h"

void sign_and_submit_request_on_request_signed_and_submitted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_result_json
) {
  printf("sign_and_submit_request_on_request_signed_and_submitted\n");
  printf("command handle %d, error %d, request result json %s\n", command_handle, error, request_result_json);

  // TODO napi_make_callback
}

void submit_request_on_request_submitted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_result_json
) {
  printf("submit_request_on_request_submitted\n");
  printf("command handle %d, error %d, request result json %s\n", command_handle, error, request_result_json);

  // TODO napi_make_callback
}

void build_get_ddo_request_on_get_ddo_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_result_json
) {
  printf("build_get_ddo_request_on_get_ddo_request_built\n");
  printf("command handle %d, error %d, request result json %s\n", command_handle, error, request_result_json);

  // TODO napi_make_callback
}

void build_nym_request_on_nym_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_nym_request_on_nym_request_built\n");
  printf("command handle %d, error %d, request json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

void build_attrib_request_on_attrib_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_attrib_request_on_attrib_request_built\n");
  printf("command handle %d, error %d, request json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

void build_get_attrib_request_on_get_attrib_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_attrib_request_on_get_attrib_request_built\n");
  printf("command handle %d, error %d, request json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

void build_get_nym_request_on_get_nym_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_nym_request_on_get_nym_request_built\n");
  printf("command handle %d, error %d, request json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

void build_schema_request_on_schema_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_schema_request_on_schema_request_built\n");
  printf("command handle %d, error %d, request json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

void build_get_schema_request_on_get_schema_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_schema_request_on_get_schema_request_built\n");
  printf("command handle %d, error %d, request json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

void build_claim_def_txn_on_claim_def_txn_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_claim_def_txn_on_claim_def_txn_built\n");
  printf("command handle %d, error %d, request_json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

void build_get_claim_def_txn_on_get_claim_def_txn_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_claim_def_txn_on_get_claim_def_txn_built\n");
  printf("command handle %d, error %d, request json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

void build_node_request_on_node_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_node_request_on_node_request_built\n");
  printf("command handle %d, error %d, request json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

void build_get_txn_request_on_get_txn_request_built(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* request_json
) {
  printf("build_get_txn_request_on_get_txn_request_built\n");
  printf("command handle %d, error %d, request json %s\n", command_handle, error, request_json);

  // TODO napi_make_callback
}

napi_value sign_and_submit_request(napi_env env, napi_callback_info info) {
  /// Signs and submits request message to validator pool.
  ///
  /// Adds submitter information to passed request json, signs it with submitter
  /// sign key (see wallet_sign), and sends signed request message
  /// to validator pool (see write_request).
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// pool_handle: pool handle (created by open_pool_ledger).
  /// wallet_handle: wallet handle (created by open_wallet).
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// request_json: Request data json.
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  /// Ledger*
  /// Crypto*
  printf("sign_and_submit_request\n");
  return NULL;
}

napi_value submit_request(napi_env env, napi_callback_info info) {
  /// Publishes request message to validator pool (no signing, unlike sign_and_submit_request).
  ///
  /// The request is sent to the validator pool as is. It's assumed that it's already prepared.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// pool_handle: pool handle (created by open_pool_ledger).
  /// request_json: Request data json.
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  /// Ledger*
  printf("submit_request\n");
  return NULL;
}

napi_value build_get_ddo_request(napi_env env, napi_callback_info info) {
  /// Builds a request to get a DDO.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// target_did: Id of Identity stored in secured Wallet.
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_get_ddo_request\n");
  return NULL;
}

napi_value build_nym_request(napi_env env, napi_callback_info info) {
  /// Builds a NYM request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// target_did: Id of Identity stored in secured Wallet.
  /// verkey: verification key
  /// alias
  /// role: Role of a user NYM record
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_nym_request\n");
  return NULL;
}

napi_value build_attrib_request(napi_env env, napi_callback_info info) {
  /// Builds an ATTRIB request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// target_did: Id of Identity stored in secured Wallet.
  /// hash: Hash of attribute data
  /// raw: represented as json, where key is attribute name and value is it's value
  /// enc: Encrypted attribute data
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_attrib_request\n");
  return NULL;
}

napi_value build_get_attrib_request(napi_env env, napi_callback_info info) {
  /// Builds a GET_ATTRIB request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// target_did: Id of Identity stored in secured Wallet.
  /// data: name (attribute name)
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_get_attrib_request\n");
  return NULL;
}

napi_value build_get_nym_request(napi_env env, napi_callback_info info) {
  /// Builds a GET_NYM request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// target_did: Id of Identity stored in secured Wallet.
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_get_nym_request\n");
  return NULL;
}

napi_value build_schema_request(napi_env env, napi_callback_info info) {
  /// Builds a SCHEMA request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// data: name, version, type, attr_names (ip, port, keys)
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_schema_request\n");
  return NULL;
}

napi_value build_get_schema_request(napi_env env, napi_callback_info info) {
  /// Builds a GET_SCHEMA request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// dest: Id of Identity stored in secured Wallet.
  /// data: name, version
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_get_schema_request\n");
  return NULL;
}

napi_value build_claim_def_txn(napi_env env, napi_callback_info info) {
  /// Builds an CLAIM_DEF request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// xref: Seq. number of schema
  /// signature_type
  /// data: components of a key in json: N, R, S, Z
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_claim_def_txn\n");
  return NULL;
}

napi_value build_get_claim_def_txn(napi_env env, napi_callback_info info) {
  /// Builds a GET_CLAIM_DEF request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// xref: Seq. number of schema
  /// signature_type: signature type (only CL supported now)
  /// origin: issuer did
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_get_claim_def_txn\n");
  return NULL;
}

napi_value build_node_request(napi_env env, napi_callback_info info) {
  /// Builds a NODE request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// target_did: Id of Identity stored in secured Wallet.
  /// data: id of a target NYM record
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_node_request\n");
  return NULL;
}

napi_value build_get_txn_request(napi_env env, napi_callback_info info) {
  /// Builds a GET_TXN request.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// submitter_did: Id of Identity stored in secured Wallet.
  /// data: seq_no of transaction in ledger
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// Request result as json.
  ///
  /// #Errors
  /// Common*
  printf("build_get_txn_request\n");
  return NULL;
}