// ffi.Library returns ... i'm not sure.... but it's this type ;)
export type FFIEntryPoint = any

// currently the FFI only requires a single configuration parameter
export interface FFIInterfaceConfig {
  libraryPath?:string
}

// FFI Type Strings
export const ffi_json_data_string = 'string'
export const ffi_name = 'string'
export const ffi_did = 'string'
export const ffi_string = 'string'
export const ffi_pool_name = 'string'
export const ffi_config_object = 'string'
export const ffi_string_data = 'string'
export const ffi_command_handle = 'int'
export const ffi_handle = 'int'
export const ffi_wallet_type_name = 'string'
export const ffi_wallet_name = 'string'
export const ffi_wallet_handle = 'int'
export const ffi_error_code = 'int'
export const ffi_void = 'void'
export const ffi_callback = 'pointer'
export const ffi_int_xref = 'int'
export const ffi_len = 'int'
export const ffi_seq_no = 'int'
export const ffi_bytes = 'pointer'
export const ffi_pool_handle = 'int'
export const ffi_listener_handle = 'int'
export const ffi_connection_handle = 'int'

// Rust Lib Native Types
export type rust_did = string
export type rust_error_code = number
export type rust_command_handle = number
export type rust_object_handle = number
export type rust_pool_handle = rust_object_handle
export type rust_wallet_handle = rust_object_handle
export type rust_listener_handle = rust_object_handle
export type rust_connection_handle = rust_object_handle

// This configuration format is driven by the FFI module.  It is separated
// from the implementation.  See ../runtime.ts for information about the
// instantiation of this interface.
//
// This is the central object from which any automatic code generation should
// proceed.
export const FFIConfiguration = {
  // pool.rs
  'indy_create_pool_ledger_config': [ffi_error_code, [ffi_command_handle,ffi_name,ffi_json_data_string,ffi_callback]],
  'indy_open_pool_ledger':[ffi_error_code, [ffi_command_handle, ffi_name, ffi_json_data_string, ffi_callback]],
  'indy_refresh_pool_ledger':[ffi_error_code, [ffi_command_handle, ffi_handle, ffi_callback]],
  'indy_close_pool_ledger':[ffi_error_code, [ffi_command_handle, ffi_handle, ffi_callback]],
  'indy_delete_pool_ledger_config':[ffi_error_code, [ffi_command_handle, ffi_name, ffi_callback]],

  // wallet.rs
  'indy_register_wallet_type':[ffi_error_code,[ffi_command_handle, ffi_wallet_type_name,
     ffi_callback, ffi_callback, ffi_callback, ffi_callback, ffi_callback, ffi_callback,
     ffi_callback, ffi_callback, ffi_callback, ffi_callback]],
  'indy_create_wallet':[ffi_error_code,[ffi_command_handle, ffi_pool_name, ffi_wallet_name, ffi_wallet_type_name, ffi_json_data_string, ffi_json_data_string, ffi_callback]],
  'indy_open_wallet':[ffi_error_code,[ffi_command_handle, ffi_wallet_name, ffi_config_object, ffi_json_data_string, ffi_callback]],
  'indy_close_wallet':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_callback]],
  'indy_delete_wallet':[ffi_error_code,[ffi_command_handle, ffi_wallet_name, ffi_json_data_string, ffi_callback]],

	// ledger.rs
	'indy_sign_and_submit_request':[ffi_error_code,[ffi_command_handle, ffi_pool_handle, ffi_wallet_handle, ffi_did, ffi_json_data_string, ffi_callback]],
	'indy_submit_request':[ffi_error_code,[ffi_command_handle, ffi_pool_handle, ffi_json_data_string, ffi_callback]],
	'indy_sign_request':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_did, ffi_json_data_string, ffi_callback]],
	'indy_build_get_ddo_request':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_did, ffi_callback]],
	'indy_build_nym_request':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_did, ffi_string, ffi_string, ffi_string, ffi_callback]],
	'indy_build_attrib_request':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_did, ffi_string, ffi_string, ffi_string, ffi_callback]],
	'indy_build_get_attrib_request':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_did, ffi_string_data, ffi_callback]],
	'indy_build_get_nym_request':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_did, ffi_callback]],
	'indy_build_schema_request':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_string_data, ffi_callback]],
	'indy_build_get_schema_request':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_string, ffi_string_data, ffi_callback]],
	'indy_build_claim_def_txn':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_int_xref, ffi_string, ffi_string_data, ffi_callback]],
	'indy_build_get_claim_def_txn':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_int_xref, ffi_string, ffi_string, ffi_callback]],
	'indy_build_node_request':[ffi_error_code,[ffi_command_handle, ffi_did, ffi_did, ffi_string_data, ffi_callback]],
	'indy_build_get_txn_request':[ffi_error_code,[ffi_command_handle, ffi_did, 'int', ffi_callback]],

	// signus.rs
	'indy_create_and_store_my_did':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_string, ffi_callback]],
	'indy_replace_keys':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_did, ffi_json_data_string, ffi_callback]],
	'indy_store_their_did':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_json_data_string, ffi_callback]],
	'indy_sign':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_did, ffi_bytes, ffi_len, ffi_callback]],
	'indy_verify_signature':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_pool_handle, ffi_did, ffi_bytes, ffi_len, ffi_bytes, ffi_len, ffi_callback]],
	'indy_encrypt':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_pool_handle, ffi_did, ffi_did, ffi_bytes, ffi_len, ffi_callback]],
	'indy_decrypt':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_did, ffi_did, ffi_bytes, ffi_len, ffi_bytes, ffi_len, ffi_callback]],

	// anoncreds.rs
	'indy_issuer_create_and_store_claim_def':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_did, ffi_json_data_string, ffi_string, 'bool', ffi_callback]],
	'indy_issuer_create_and_store_revoc_reg':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_did, ffi_seq_no, 'int', ffi_callback]],
	'indy_issuer_create_claim':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_json_data_string, ffi_json_data_string, ffi_seq_no, 'int', ffi_callback]],
	'indy_issuer_revoke_claim':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_seq_no, ffi_seq_no, ffi_callback]],
	'indy_prover_store_claim_offer':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_json_data_string, ffi_callback]],
	'indy_prover_get_claim_offers':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_json_data_string, ffi_callback]],
	'indy_prover_create_master_secret':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_string, ffi_callback]],
	'indy_prover_create_and_store_claim_req':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_did, ffi_json_data_string, ffi_json_data_string, ffi_string, ffi_callback]],
	'indy_prover_store_claim':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_json_data_string, ffi_callback]],
	'indy_prover_get_claims':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_json_data_string, ffi_callback]],
	'indy_prover_get_claims_for_proof_req':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_json_data_string, ffi_callback]],
	'indy_prover_create_proof':[ffi_error_code,[ffi_command_handle, ffi_wallet_handle, ffi_json_data_string, ffi_json_data_string, ffi_json_data_string, ffi_string, ffi_json_data_string, ffi_json_data_string, ffi_callback]],
	'indy_verifier_verify_proof':[ffi_error_code,[ffi_command_handle, ffi_json_data_string, ffi_json_data_string, ffi_json_data_string, ffi_json_data_string]],

	// agent.rs
	'indy_agent_connect':[ffi_error_code,[ffi_command_handle, ffi_pool_handle, ffi_wallet_handle, ffi_did, ffi_did, ffi_callback, ffi_callback]],
	'indy_agent_listen':[ffi_error_code,[ffi_command_handle, ffi_string, ffi_callback, ffi_callback, ffi_callback]],
	'indy_agent_add_identity':[ffi_error_code,[ffi_command_handle, ffi_listener_handle, ffi_pool_handle, ffi_wallet_handle, ffi_did, ffi_callback]],
	'indy_agent_remove_identity':[ffi_error_code,[ffi_command_handle, ffi_listener_handle, ffi_wallet_handle, ffi_did, ffi_callback]],
	'indy_agent_send':[ffi_error_code,[ffi_command_handle, ffi_connection_handle, ffi_string, ffi_callback]],
	'indy_agent_close_connection':[ffi_error_code,[ffi_command_handle, ffi_connection_handle, ffi_callback]],
	'indy_agent_close_listener':[ffi_error_code,[ffi_command_handle,ffi_listener_handle,ffi_callback]]

}
