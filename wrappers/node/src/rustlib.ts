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


// map the typescript native types that match the FFI callback decl
import { ErrorCode,IndyError } from './error'

// required for ffi.Callback()
import * as ffi from 'ffi'

const debug = require('debug')('indy-sdk:ffi')

// these three are all promise callback
// resolves to void or throws error.  the rust library calls continue down this
// line, with a void resolution and an IndyError in the event of a non-zero
// ffi_error_code.
//
export function build_default_callback(resolve:any,reject:any) {
  return ffi.Callback(ffi_void, [ffi_command_handle, ffi_error_code],
    (command_handle:rust_command_handle, error_code:rust_error_code) => {
      if(error_code == 0) {
        debug("RESOLVING:%j",error_code)
        resolve()
      }
      else {
        debug("REJECTING:%j",error_code)
        reject(new IndyError(error_code))
      }
    });
}

// the open functions often hand back an integer value
export function build_object_handle_callback(resolve:any,reject:any) {
  return ffi.Callback(ffi_void, [ffi_command_handle, ffi_error_code,ffi_pool_handle],
    (command_handle:rust_command_handle, error_code:rust_error_code,result:rust_object_handle) => {
      if(error_code == 0) {
        resolve(result)
      }
      else {
        reject(new IndyError(error_code))
      }
    });
}

// used by ledger : indy_sign_and_submit_request, indy_sign_request,
// indy_submit_request, indy_build_get_ddo_request, indy_build_nym_request,
// indy_build_attrib_request, indy_build_get_attrib_request, indy_build_get_nym_request
// indy_build_schema_request, indy_build_get_schema_request, indy_build_claim_def_txn
// indy_build_get_claim_def_txn, indy_build_node_request, indy_build_get_txn_request,
export function build_receive_json_result_callback(resolve:any,reject:any) {
  return ffi.Callback(ffi_void, [ffi_command_handle, ffi_error_code,ffi_string],
  (command_handle:rust_command_handle, error_code:rust_error_code,result:string) => {
    if(error_code == 0) {
      try {
        const prasedResult : any = JSON.parse(result)
        // TODO - free result string
        console.log("DO WE NEED TO FREE RESULT STRING FROM RUST SIDE")
        resolve(prasedResult)
      }
      catch(error) {
        reject(error)
      }
    }
    else {
      reject(new IndyError(error_code))
    }
  });
}



// agent.rs callback support
/*
connection_cb: Option<extern fn(xlistener_handle: i32,
                                err: ErrorCode,
                                connection_handle: i32,
                                sender_did: *const c_char,
                                receiver_did: *const c_char)>,
*/
export type agent_connection_callback_type = (command_handle:rust_listener_handle, error_code:rust_error_code,connection_handle:rust_connection_handle,sender_did:rust_did,receiver_did:rust_did) => void
export function build_connection_callback(target:agent_connection_callback_type) {
  return ffi.Callback(ffi_void, [ffi_command_handle, ffi_error_code,ffi_connection_handle,ffi_did,ffi_did],target)
}

/*
message_cb: Option<extern fn(xconnection_handle: i32,
                             err: ErrorCode,
                             message: *const c_char)>) -> ErrorCode {
*/
export type agent_message_callback_type =  (command_handle:rust_command_handle, error_code:rust_error_code,message:string) => void
export function build_message_callback(target:agent_message_callback_type) {
  return ffi.Callback(ffi_void, [ffi_command_handle, ffi_error_code,ffi_string],target);
}



// TODO - wallet implementation type callback
/*
open(wallet_name:string,
  config:optional<json_object_or_serialized<open_wallet_options>>,
  runtime_config:optional<json_object_or_serialized<wallet_config>>,
  wallet_credentials:json_object_or_serialized<wallet_credentials>,
  return_handle:mutable<rust_wallet_handle>
): ErrorCode
*/
export type wallet_implementation_create_callback_type = (wallet_name:string,
  wallet_type_config:string,
  wallet_credentials:string) => ErrorCode
// TODO - map these to correct types
export type wallet_implementation_open_callback_type = (wallet_name:string,
  config:string,
  runtime_config:string,
  credentials:string,
  return_handle:any
  ) => ErrorCode
export type wallet_implementation_set_callback_type = (wallet_handle:rust_wallet_handle,key:string,value:string) => ErrorCode

// TODO - fix the mutable implementation
//export type wallet_implementation_get_callback_type = (wallet_handle:rust_wallet_handle,key:string,return_string:mutable<string>) => ErrorCode
//export type wallet_implementation_get_not_expired_callback_type = (wallet_handle:rust_wallet_handle,key:string,return_string:mutable<string>) => ErrorCode
//export type wallet_implementation_list_callback_type = (wallet_handle:rust_wallet_handle,key_prefix:string,return_string:mutable<string>) => ErrorCode
export type wallet_implementation_get_callback_type = (wallet_handle:rust_wallet_handle,key:string,return_string:any) => ErrorCode
export type wallet_implementation_get_not_expired_callback_type = (wallet_handle:rust_wallet_handle,key:string,return_string:any) => ErrorCode
export type wallet_implementation_list_callback_type = (wallet_handle:rust_wallet_handle,key_prefix:string,return_string:any) => ErrorCode
export type wallet_implementation_close_callback_type = (wallet_handle:rust_wallet_handle) => ErrorCode
export type wallet_implementation_delete_callback_type = (wallet_name:string,config:string) => ErrorCode
export type wallet_implementation_free_callback_type = (wallet_handle:rust_wallet_handle,value:string) => ErrorCode

export const ffi_pointer_pointer = 'pointer' // TODO - use ffi ref types

export const FFICallbackBuilder = {
  //create: Option<extern fn(name: *const c_char,
  //                       config: *const c_char,
  //                       credentials: *const c_char) -> ErrorCode>,
  build_create:(target:wallet_implementation_create_callback_type) => {
    const args = [ffi_wallet_name, ffi_json_data_string ,ffi_json_data_string]
    return ffi.Callback(ffi_error_code,args,target)
  },

  //open: Option<extern fn(name: *const c_char,
  //                       config: *const c_char,
  //                       runtime_config: *const c_char,
  //                       credentials: *const c_char,
  //                       handle: *mut i32) -> ErrorCode>,
  build_open:(target:wallet_implementation_open_callback_type) => {
    const args = [ffi_wallet_name, ffi_json_data_string,ffi_json_data_string,ffi_json_data_string,ffi_pointer_pointer]
    return ffi.Callback(ffi_error_code,args,target)
  },

  //set: Option<extern fn(handle: i32,
  //                    key: *const c_char,
  //                    value: *const c_char) -> ErrorCode>,
  build_set:(target:wallet_implementation_set_callback_type) => {
    const args = [ffi_wallet_handle,ffi_string,ffi_string]
      return ffi.Callback(ffi_error_code,args,target)
    },

  //get: Option<extern fn(handle: i32,
  //                    key: *const c_char,
  //                    value_ptr: *mut *const c_char) -> ErrorCode>,
  build_get:(target:wallet_implementation_get_callback_type) => {
    const args = [ffi_wallet_handle,ffi_string,ffi_pointer_pointer]
    return ffi.Callback(ffi_error_code,args,target)
  },

  //get_not_expired: Option<extern fn(handle: i32,
  //                                key: *const c_char,
  //                                value_ptr: *mut *const c_char) -> ErrorCode>,
  build_get_not_expired:(target:wallet_implementation_get_not_expired_callback_type) => {
    const args = [ffi_wallet_handle,ffi_string,ffi_pointer_pointer]
    return ffi.Callback(ffi_error_code,args,target)
  },

  //list: Option<extern fn(handle: i32,
  //                     key_prefix: *const c_char,
  //                     values_json_ptr: *mut *const c_char) -> ErrorCode>,
  build_list:(target:wallet_implementation_list_callback_type) => {
    const args = [ffi_wallet_handle,ffi_string,ffi_pointer_pointer]
    return ffi.Callback(ffi_error_code,args,target)
  },

  //close: Option<extern fn(handle: i32) -> ErrorCode>,
  build_close:(target:wallet_implementation_close_callback_type) => {
    const args = [ffi_wallet_handle]
    return ffi.Callback(ffi_error_code,args,target)
  },

  //delete: Option<extern fn(name: *const c_char,
  //                       config: *const c_char,
  //                       credentials: *const c_char) -> ErrorCode>,
  build_delete:(target:wallet_implementation_delete_callback_type) => {
    const args = [ffi_string,ffi_string,ffi_string]
    return ffi.Callback(ffi_error_code,args,target)
  },

  //free: Option<extern fn(wallet_handle: i32,
  //                     value: *const c_char) -> ErrorCode>,
  build_free:(target:wallet_implementation_free_callback_type) => {
    const args = [ffi_wallet_handle,ffi_string]
    return ffi.Callback(ffi_error_code,args,target)
  }
}
