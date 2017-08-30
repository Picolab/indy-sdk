// in a very real sense, this is the translation of ffi_* types
// back into rust_* types.

// import the strings which match the FFI declarations
import {
  ffi_command_handle,
  ffi_error_code,
  ffi_void,
  ffi_pool_handle,
  ffi_listener_handle,
  ffi_wallet_handle,
  ffi_connection_handle,
  ffi_did,
  ffi_string,
  ffi_json_data_string,
  ffi_wallet_type_name,
  ffi_wallet_name
} from './api'

// map the typescript native types that match the FFI callback decl
import {
  rust_object_handle,
  rust_command_handle,
  rust_error_code,
  rust_pool_handle,
  rust_listener_handle,
  rust_connection_handle,
  rust_did,
  rust_wallet_handle
} from './api'

// map the typescript native types that match the FFI callback decl
import { ErrorCode,IndyError } from '../error'

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
