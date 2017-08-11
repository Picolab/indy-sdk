
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

  NAPI_EXPECTING_ARGS(6);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_STRING(argv[1]);
  NAPI_ENSURE_STRING(argv[2]);
  NAPI_ENSURE_STRING(argv[3]);
  NAPI_ENSURE_STRING(argv[4]);
  NAPI_ENSURE_FUNCTION(argv[5]);

  indy_handle_t command_handle;
  size_t string_length, written;
  char* submitter_did = 0;
  char* schema_seq_num = 0;
  char* signature_type = 0;
  char* data = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], schema_seq_num);
  NAPI_STRING_TO_UTF8(argv[3], signature_type);
  NAPI_STRING_TO_UTF8(argv[4], data);

  napi_value result;
  double res = indy_build_claim_def_txn(
    command_handle,
    submitter_did,
    schema_seq_num,
    signature_type,
    data,
    build_claim_def_txn_on_claim_def_txn_built
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_get_claim_def_txn(napi_env env, napi_callback_info info) {
  printf("build_get_claim_def_txn\n");

  NAPI_EXPECTING_ARGS(6);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_STRING(argv[1]);
  NAPI_ENSURE_STRING(argv[2]);
  NAPI_ENSURE_STRING(argv[3]);
  NAPI_ENSURE_STRING(argv[4]);
  NAPI_ENSURE_FUNCTION(argv[5]);

  indy_handle_t command_handle;
  size_t string_length, written;
  char* submitter_did = 0;
  char* schema_seq_num = 0;
  char* signature_type = 0;
  char* origin = 0;
  
  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], schema_seq_num);
  NAPI_STRING_TO_UTF8(argv[3], signature_type);
  NAPI_STRING_TO_UTF8(argv[4], origin);

  napi_value result;
  double res = indy_build_get_claim_def_txn(
    command_handle,
    submitter_did,
    schema_seq_num,
    signature_type,
    origin,
    build_get_claim_def_txn_on_get_claim_def_txn_built
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_node_request(napi_env env, napi_callback_info info) {
  printf("build_node_request\n");

  NAPI_EXPECTING_ARGS(5);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_STRING(argv[1]);
  NAPI_ENSURE_STRING(argv[2]);
  NAPI_ENSURE_STRING(argv[3]);
  NAPI_ENSURE_FUNCTION(argv[4]);

  indy_handle_t command_handle;
  size_t string_length, written;
  char* submitter_did = 0;
  char* target_did = 0;
  char* data = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_STRING_TO_UTF8(argv[2], target_did);
  NAPI_STRING_TO_UTF8(argv[3], data);

  napi_value result;
  double res = indy_build_node_request(
    command_handle,
    submitter_did,
    target_did,
    data,
    build_node_request_on_node_request_built
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value build_get_txn_request(napi_env env, napi_callback_info info) {
  printf("build_get_txn_request\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_STRING(argv[1]);
  NAPI_ENSURE_NUMBER(argv[2]);
  NAPI_ENSURE_FUNCTION(argv[3]);

  indy_handle_t command_handle;
  size_t string_length, written;
  char* submitter_did = 0;
  indy_i32_t data;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], submitter_did);
  NAPI_NUMBER_TO_INT32(argv[2], data);

  napi_value result;
  double res = indy_build_get_txn_request(
    command_handle,
    submitter_did,
    data,
    build_get_txn_request_on_get_txn_request_built
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}