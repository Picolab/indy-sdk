import { ErrorCode } from '../error'
import {
  build_object_handle_callback,
  build_receive_json_result_callback,
  build_default_callback,
  agent_connection_callback_type,
  agent_message_callback_type,
  rust_connection_handle,
  rust_listener_handle,
  rust_command_handle,
  rust_wallet_handle,
  rust_pool_handle,
  rust_did
} from '../ffi'
export {
  agent_connection_callback_type,
  agent_message_callback_type,
  rust_connection_handle,
  rust_listener_handle,
  rust_command_handle,
  rust_wallet_handle,
  rust_pool_handle,
  rust_did
} from '../ffi'

export type JSON_Datum = any
export type FilesystemPath = string
export type IP_Port = number
export type IP_Addr = string
export type TXN_DEST = string
export type TXN_IDENTIFIER = string
export type TXN_ID = string
export type TXN_Type = string
export type json_object_or_serialized<T> = T | string
export type optional<T> = T | null | undefined


export interface BridgeInterfaceConfig {
  increment_command_handle?:boolean
  validate_serialized_json_string_parameters?:boolean,
}

export interface create_pool_ledger_config_options {
  /// {
  ///     "genesis_txn": string (optional), A path to genesis transaction file. If NULL, then a default one will be used.
  ///                    If file doesn't exists default one will be created.
  /// }
  genesis_txn?:FilesystemPath
}
export interface open_pool_ledger_options {
  ///     "refreshOnOpen": bool (optional), Forces pool ledger to be refreshed immediately after opening.
  ///                      Defaults to true.
  ///     "autoRefreshTime": int (optional), After this time in minutes pool ledger will be automatically refreshed.
  ///                        Use 0 to disable automatic refresh. Defaults to 24*60.
  ///     "networkTimeout": int (optional), Network timeout for communication with nodes in milliseconds.
  ///                       Defaults to 20000.  refreshOnOpen?:boolean
  refreshOnOpen?:boolean
  autoRefreshTime?:number
  networkTimeout?:number
}

export type wallet_type_config = any
export type wallet_config = any
export type wallet_credentials = any


export interface open_wallet_options {
  /// {
  ///     "freshnessTime": string (optional), Amount of minutes to consider wallet value as fresh. Defaults to 24*60.
  ///     ... List of additional supported keys are defined by wallet type.
  /// }
  freshnessTime?:number
}
export interface delete_wallet_options {
}
export interface mutable<T> {
  value:T
}

export interface wallet_type_definition {
  //create: Option<extern fn(name: *const c_char,
  //                       config: *const c_char,
  //                       credentials: *const c_char) -> ErrorCode>,
  create(wallet_name:string,
    wallet_type_config:string,
    wallet_credentials:string) : ErrorCode

  //open: Option<extern fn(name: *const c_char,
  //                       config: *const c_char,
  //                       runtime_config: *const c_char,
  //                       credentials: *const c_char,
  //                       handle: *mut i32) -> ErrorCode>,
  open(wallet_name:string,
    config:string,
    runtime_config:string,
    wallet_credentials:string,
    return_handle:mutable<rust_wallet_handle>
  ): ErrorCode
  //set: Option<extern fn(handle: i32,
  //                    key: *const c_char,
  //                    value: *const c_char) -> ErrorCode>,
  set(wallet_handle:rust_wallet_handle,key:string,value:string) : ErrorCode

  //get: Option<extern fn(handle: i32,
  //                    key: *const c_char,
  //                    value_ptr: *mut *const c_char) -> ErrorCode>,
  get(wallet_handle:rust_wallet_handle,key:string,return_string:mutable<string>) : ErrorCode

  //get_not_expired: Option<extern fn(handle: i32,
  //                                key: *const c_char,
  //                                value_ptr: *mut *const c_char) -> ErrorCode>,
  get_not_expired(wallet_handle:rust_wallet_handle,key:string,return_string:mutable<string>) : ErrorCode

  //list: Option<extern fn(handle: i32,
  //                     key_prefix: *const c_char,
  //                     values_json_ptr: *mut *const c_char) -> ErrorCode>,
  list(wallet_handle:rust_wallet_handle,key_prefix:string,return_string:mutable<string>) : ErrorCode

  //close: Option<extern fn(handle: i32) -> ErrorCode>,
  close(wallet_handle:rust_wallet_handle) : ErrorCode

  //delete: Option<extern fn(name: *const c_char,
  //                       config: *const c_char,
  //                       credentials: *const c_char) -> ErrorCode>,
  delete(wallet_name:string,config:optional<json_object_or_serialized<delete_wallet_options>>) : ErrorCode

  //free: Option<extern fn(wallet_handle: i32,
  //                     value: *const c_char) -> ErrorCode>,
  free(wallet_handle:rust_wallet_handle,value:string) : ErrorCode
}



export interface libindy_bridge {
  // pool.rs
  create_pool_ledger_config(configuration_name:string,config_data?:create_pool_ledger_config_options) : Promise<void>
  delete_pool_ledger_config(configuration_name:string) : Promise<void>
  open_pool_ledger(configuration_name:string,config_data?:json_object_or_serialized<open_pool_ledger_options>) : Promise<rust_pool_handle>
  refresh_pool_ledger(pool_handle:rust_pool_handle) : Promise<void>
  close_pool_ledger(pool_handle:rust_pool_handle) : Promise<void>

  // wallet.rs
  register_wallet_type(wallet_type_name:string, wallet_callbacks:wallet_type_definition) : Promise<void>
  create_wallet(pool_name:string, wallet_name:string, wallet_type_name:string,config_data:json_object_or_serialized<JSON_Datum>,credentials:json_object_or_serialized<wallet_credentials>) : Promise<void>
  open_wallet(wallet_name:string,runtime_config:json_object_or_serialized<JSON_Datum>,credentials:json_object_or_serialized<wallet_credentials>) : Promise<rust_wallet_handle>
  close_wallet(wallet_handle:rust_wallet_handle) : Promise<void>
  delete_wallet(wallet_name:string,credentials:json_object_or_serialized<wallet_credentials>) : Promise<void>

  // ledger.rs
  sign_and_submit_request(pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  submit_request(pool_handle:rust_pool_handle,request_json:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  sign_request(wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_ddo_request(submitter_did:rust_did,target_did:rust_did) : Promise<JSON_Datum>
  build_nym_request(submitter_did:rust_did,target_did:rust_did,verkey:string,alias:string,role:string) : Promise<JSON_Datum>
  build_attrib_request(submitter_did:rust_did,target_did:rust_did,hash:string,raw:string,enc:string) : Promise<JSON_Datum>
  build_get_attrib_request(submitter_did:rust_did,target_did:rust_did,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_nym_request(submitter_did:rust_did,target_did:rust_did) : Promise<JSON_Datum>
  build_schema_request(submitter_did:rust_did,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_schema_request(submitter_did:rust_did,dest:string,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_claim_def_txn(submitter_did:rust_did,xref:number,signature_type:string, data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_claim_def_txn(submitter_did:rust_did,xref:number,signature_type:string,origin:string) : Promise<JSON_Datum>
  build_node_request(submitter_did:rust_did,target_did:rust_did,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_txn_request(submitter_did:rust_did,data:number) : Promise<JSON_Datum>

  // signus.rs
  create_and_store_my_did(wallet_handle:rust_wallet_handle,did_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  replace_keys(wallet_handle:rust_wallet_handle,did:rust_did,identity_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  store_their_did(wallet_handle:rust_wallet_handle,identity_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  sign(wallet_handle:rust_wallet_handle,did:rust_did, message:Buffer) : Promise<void>
  verify_signature(wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,did:rust_did, message:Buffer, signature:Buffer) : Promise<void>
  encrypt(wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,my_did:rust_did,did:rust_did, message:Buffer) : Promise<void>
  decrypt(wallet_handle:rust_wallet_handle,myDid:rust_did,did:rust_did, encrypted:Buffer,nonce:Buffer) : Promise<void>

  // anoncreds.rs
  issuer_create_and_store_claim_def(wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_json:json_object_or_serialized<JSON_Datum>,signature_type:string,create_non_revoc:boolean)  : Promise<void>
  issuer_create_and_store_revoc_reg(wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_seq_no:number,max_claim_num:number) : Promise<void>
  issuer_create_claim(wallet_handle:rust_wallet_handle,claim_req_json:number,claim_json:number,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void>
  issuer_revoke_claim(wallet_handle:rust_wallet_handle,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void>
  prover_store_claim_offer(wallet_handle:rust_wallet_handle,claim_offer_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_get_claim_offers(wallet_handle:rust_wallet_handle,filter_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_create_master_secret(wallet_handle:rust_wallet_handle,master_secret_name:string) : Promise<void>
  prover_create_and_store_claim_req(wallet_handle:rust_wallet_handle,prover_did:rust_did,claim_offer_json:json_object_or_serialized<JSON_Datum>,claim_def_json:json_object_or_serialized<JSON_Datum>,master_secret_name:string) : Promise<void>
  prover_store_claim(wallet_handle:rust_wallet_handle,claims_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_get_claims(wallet_handle:rust_wallet_handle,filter_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_get_claims_for_proof_req(wallet_handle:rust_wallet_handle,proof_request_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_create_proof(wallet_handle:rust_wallet_handle,proof_req_json:json_object_or_serialized<JSON_Datum>,requested_claims_json:json_object_or_serialized<JSON_Datum>,schemas_json:json_object_or_serialized<JSON_Datum>,master_secret_name:string,claim_defs_json:json_object_or_serialized<JSON_Datum>,revoc_regs_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  verifier_verify_proof(proof_request_json:json_object_or_serialized<JSON_Datum>,proof_json:json_object_or_serialized<JSON_Datum>,schemas_json:json_object_or_serialized<JSON_Datum>,claim_defs_jsons:json_object_or_serialized<JSON_Datum>,revoc_regs_json:json_object_or_serialized<JSON_Datum>) : Promise<void>

  // agent.rs
  agent_connect(pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,sender_did:rust_did,receiver_did:rust_did,message_cb:agent_message_callback_type) : Promise<rust_connection_handle>
  agent_listen(endpoint:string,connection_cb:agent_connection_callback_type,message_cb:agent_message_callback_type) : Promise<rust_listener_handle>
  agent_add_identity(listener_handle:rust_listener_handle,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void>
  agent_remove_identity(listener_handle:rust_listener_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void>
  agent_send(connection_handle:rust_connection_handle,message:string) : Promise<void>
  agent_close_connection(connection_handle:rust_connection_handle) : Promise<void>
  agent_close_listener(listener_handle:rust_listener_handle)  : Promise<void>

}

export class libindy_middleware_context {
  private position : number
  readonly first : libindy_middleware
  readonly wrappers : libindy_middleware[]
  resolve:(...args) => void
  reject:(...args) => void

  constructor(wrappers:libindy_middleware[]) {
    this.position = wrappers.length - 1
    this.wrappers = wrappers
    this.resolve = undefined
    this.reject = undefined
    this.first = wrappers[this.position]
  }

  advance(resolve?:json_object_or_serialized<JSON_Datum>,reject?:json_object_or_serialized<JSON_Datum>) : libindy_middleware {
    if(this.position <= 0)
      throw "unable to advance"

    function wrap(before_method:json_object_or_serialized<JSON_Datum>,current_method:json_object_or_serialized<JSON_Datum>) {
      if(before_method !== undefined) {
        if(current_method !== undefined) {
          return (...args) => {
            before_method(...args)
            current_method(...args)
          }
        } else {
            return before_method
          }
      }
      else {
        if(current_method !== undefined) {
          return current_method
        } else {
            return undefined
          }
      }
    }

    this.position --
    this.resolve = wrap(this.resolve,resolve)
    this.reject = wrap(this.reject,reject)
    return this.wrappers[this.position]
  }

}


export interface libindy_middleware {
  // pool.rs
  create_pool_ledger_config(ctx:libindy_middleware_context,configuration_name:string,config_data?:create_pool_ledger_config_options) : Promise<void>
  delete_pool_ledger_config(ctx:libindy_middleware_context,configuration_name:string) : Promise<void>
  open_pool_ledger(ctx:libindy_middleware_context,configuration_name:string,config_data?:json_object_or_serialized<open_pool_ledger_options>) : Promise<rust_pool_handle>
  refresh_pool_ledger(ctx:libindy_middleware_context,pool_handle:rust_pool_handle) : Promise<void>
  close_pool_ledger(ctx:libindy_middleware_context,pool_handle:rust_pool_handle) : Promise<void>

  // wallet.rs
  register_wallet_type(ctx:libindy_middleware_context,wallet_type_name:string, wallet_callbacks:wallet_type_definition) : Promise<void>
  create_wallet(ctx:libindy_middleware_context,pool_name:string, wallet_name:string, wallet_type_name:string,config_data:json_object_or_serialized<JSON_Datum>,credentials:json_object_or_serialized<wallet_credentials>) : Promise<void>
  open_wallet(ctx:libindy_middleware_context,wallet_name:string,runtime_config:json_object_or_serialized<JSON_Datum>,credentials:json_object_or_serialized<wallet_credentials>) : Promise<rust_wallet_handle>
  close_wallet(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle) : Promise<void>
  delete_wallet(ctx:libindy_middleware_context,wallet_name:string,credentials:json_object_or_serialized<wallet_credentials>) : Promise<void>

  // ledger.rs
  sign_and_submit_request(ctx:libindy_middleware_context,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  submit_request(ctx:libindy_middleware_context,pool_handle:rust_pool_handle,request_json:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  sign_request(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_ddo_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did) : Promise<JSON_Datum>
  build_nym_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did,verkey:string,alias:string,role:string) : Promise<JSON_Datum>
  build_attrib_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did,hash:string,raw:string,enc:string) : Promise<JSON_Datum>
  build_get_attrib_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_nym_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did) : Promise<JSON_Datum>
  build_schema_request(ctx:libindy_middleware_context,submitter_did:rust_did,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_schema_request(ctx:libindy_middleware_context,submitter_did:rust_did,dest:string,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_claim_def_txn(ctx:libindy_middleware_context,submitter_did:rust_did,xref:number,signature_type:string, data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_claim_def_txn(ctx:libindy_middleware_context,submitter_did:rust_did,xref:number,signature_type:string,origin:string) : Promise<JSON_Datum>
  build_node_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum>
  build_get_txn_request(ctx:libindy_middleware_context,submitter_did:rust_did,data:number) : Promise<JSON_Datum>

  // signus.rs
  create_and_store_my_did(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,did_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  replace_keys(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,did:rust_did,identity_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  store_their_did(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,identity_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  sign(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,did:rust_did,message:Buffer) : Promise<void>
  verify_signature(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,did:rust_did, message:Buffer, signature:Buffer) : Promise<void>
  encrypt(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,my_did:rust_did,did:rust_did, message:Buffer) : Promise<void>
  decrypt(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,myDid:rust_did,did:rust_did, encrypted:Buffer,nonce:Buffer) : Promise<void>

  // anoncreds.rs
  issuer_create_and_store_claim_def(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_json:json_object_or_serialized<JSON_Datum>,signature_type:string,create_non_revoc:boolean)  : Promise<void>
  issuer_create_and_store_revoc_reg(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_seq_no:number,max_claim_num:number) : Promise<void>
  issuer_create_claim(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,claim_req_json:number,claim_json:number,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void>
  issuer_revoke_claim(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void>
  prover_store_claim_offer(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,claim_offer_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_get_claim_offers(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,filter_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_create_master_secret(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,master_secret_name:string) : Promise<void>
  prover_create_and_store_claim_req(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,prover_did:rust_did,claim_offer_json:json_object_or_serialized<JSON_Datum>,claim_def_json:json_object_or_serialized<JSON_Datum>,master_secret_name:string) : Promise<void>
  prover_store_claim(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,claims_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_get_claims(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,filter_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_get_claims_for_proof_req(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,proof_request_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  prover_create_proof(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,proof_req_json:json_object_or_serialized<JSON_Datum>,requested_claims_json:json_object_or_serialized<JSON_Datum>,schemas_json:json_object_or_serialized<JSON_Datum>,master_secret_name:string,claim_defs_json:json_object_or_serialized<JSON_Datum>,revoc_regs_json:json_object_or_serialized<JSON_Datum>) : Promise<void>
  verifier_verify_proof(ctx:libindy_middleware_context,proof_request_json:json_object_or_serialized<JSON_Datum>,proof_json:json_object_or_serialized<JSON_Datum>,schemas_json:json_object_or_serialized<JSON_Datum>,claim_defs_jsons:json_object_or_serialized<JSON_Datum>,revoc_regs_json:json_object_or_serialized<JSON_Datum>) : Promise<void>

  // agent.rs
  agent_connect(ctx:libindy_middleware_context,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,sender_did:rust_did,receiver_did:rust_did,message_cb:agent_message_callback_type) : Promise<rust_connection_handle>
  agent_listen(ctx:libindy_middleware_context,endpoint:string,connection_cb:agent_connection_callback_type,message_cb:agent_message_callback_type) : Promise<rust_listener_handle>
  agent_add_identity(ctx:libindy_middleware_context,listener_handle:rust_listener_handle,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void>
  agent_remove_identity(ctx:libindy_middleware_context,listener_handle:rust_listener_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void>
  agent_send(ctx:libindy_middleware_context,connection_handle:rust_connection_handle,message:string) : Promise<void>
  agent_close_connection(ctx:libindy_middleware_context,connection_handle:rust_connection_handle) : Promise<void>
  agent_close_listener(ctx:libindy_middleware_context,listener_handle:rust_listener_handle)  : Promise<void>

}

export { BridgeEntryPoint } from './wrapper'
export { AsyncBridgeEntryPoint } from './async'
