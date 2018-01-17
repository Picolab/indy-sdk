import { ErrorCode } from '../error'
import {
  JSON_Datum,
  FilesystemPath,
  json_object_or_serialized,
  agent_connection_callback_type,
  agent_message_callback_type,
  rust_connection_handle,
  rust_listener_handle,
  rust_command_handle,
  rust_wallet_handle,
  rust_pool_handle,
  rust_did,
  create_pool_ledger_config_options,
  open_pool_ledger_options,
  wallet_type_definition,
  wallet_credentials,
  libindy_bridge,
  open_wallet_options,
  delete_wallet_options
} from './api'

import {
  PromiseImplementation
} from './promise'


export class libindy_middleware_context {
  private position : number
  readonly first : libindy_middleware
  readonly wrappers : libindy_middleware[]
  resolve:(...args:any[]) => void
  reject:(...args:any[]) => void

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

export class BridgeEntryPoint implements libindy_bridge {
  private layers:libindy_middleware[]

  constructor(ffi:any,config?:any) {
    this.layers = [new PromiseImplementation(ffi,config)]
  }
  use(wrapper:libindy_middleware) {
    this.layers.push(wrapper)
  }

  // pool.rs
  create_pool_ledger_config(configuration_name:string,config_data?:create_pool_ledger_config_options) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.create_pool_ledger_config(ctx,configuration_name,config_data)
    }
  delete_pool_ledger_config(configuration_name:string) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.delete_pool_ledger_config(ctx,configuration_name)
    }
  open_pool_ledger(configuration_name:string,config_data?:json_object_or_serialized<open_pool_ledger_options>) : Promise<rust_pool_handle> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.open_pool_ledger(ctx,configuration_name,config_data)
    }
  refresh_pool_ledger(pool_handle:rust_pool_handle) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.refresh_pool_ledger(ctx,pool_handle)
    }
  close_pool_ledger(pool_handle:rust_pool_handle) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.close_pool_ledger(ctx,pool_handle)
    }

  // wallet.rs
  register_wallet_type(wallet_type_name:string, wallet_callbacks:wallet_type_definition) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.register_wallet_type(ctx,wallet_type_name,wallet_callbacks)
    }
  create_wallet(pool_name:string, wallet_name:string, wallet_type_name:string,config_data:any,credentials:json_object_or_serialized<wallet_credentials>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.create_wallet(ctx,pool_name,wallet_name,wallet_type_name,config_data,credentials)
    }
  open_wallet(wallet_name:string,runtime_config:any,credentials:string) : Promise<rust_wallet_handle> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.open_wallet(ctx,wallet_name,runtime_config,credentials)
    }
  close_wallet(wallet_handle:rust_wallet_handle) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.close_wallet(ctx,wallet_handle)
    }
  delete_wallet(wallet_name:string,credentials:any) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.delete_wallet(ctx,wallet_name,credentials)
    }

  // ledger.rs
  sign_and_submit_request(pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.sign_and_submit_request(ctx,pool_handle,wallet_handle,submitter_did,request_json)
    }
  submit_request(pool_handle:rust_pool_handle,request_json:any) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.submit_request(ctx,pool_handle,request_json)
    }
  sign_request(wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:any)  : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.sign_request(ctx,wallet_handle,submitter_did,request_json)
    }
  build_get_ddo_request(submitter_did:rust_did,target_did:rust_did) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_get_ddo_request(ctx,submitter_did,target_did)
    }
  build_nym_request(submitter_did:rust_did,target_did:rust_did,verkey:string,alias:string,role:string) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_nym_request(ctx,submitter_did,target_did,verkey,alias,role)
    }
  build_attrib_request(submitter_did:rust_did,target_did:rust_did,hash:string,raw:string,enc:string) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_attrib_request(ctx,submitter_did,target_did,hash,raw,enc)
    }
  build_get_attrib_request(submitter_did:rust_did,target_did:rust_did,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_get_attrib_request(ctx,submitter_did,target_did,data)
    }
  build_get_nym_request(submitter_did:rust_did,target_did:rust_did) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_get_nym_request(ctx,submitter_did,target_did)
    }
  build_schema_request(submitter_did:rust_did,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_schema_request(ctx,submitter_did,data)
    }
  build_get_schema_request(submitter_did:rust_did,dest:string,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_get_schema_request(ctx,submitter_did,dest,data)
    }
  build_claim_def_txn(submitter_did:rust_did,xref:number,signature_type:string, data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_claim_def_txn(ctx,submitter_did,xref,signature_type,data)
    }
  build_get_claim_def_txn(submitter_did:rust_did,xref:number,signature_type:string,origin:string) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_get_claim_def_txn(ctx,submitter_did,xref,signature_type,origin)
    }
  build_node_request(submitter_did:rust_did,target_did:rust_did,data:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_node_request(ctx,submitter_did,target_did,data)
    }
  build_get_txn_request(submitter_did:rust_did,data:number) : Promise<JSON_Datum> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.build_get_txn_request(ctx,submitter_did,data)
    }

  // signus.rs
  create_and_store_my_did(wallet_handle:rust_wallet_handle,did_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.create_and_store_my_did(ctx,wallet_handle,did_json)
    }
  replace_keys(wallet_handle:rust_wallet_handle,did:rust_did,identity_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.replace_keys(ctx,wallet_handle,did,identity_json)
    }
  store_their_did(wallet_handle:rust_wallet_handle,identity_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.store_their_did(ctx,wallet_handle,identity_json)
    }
  sign(wallet_handle:rust_wallet_handle,did:rust_did, message:Buffer)  : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.sign(ctx,wallet_handle,did,message)
    }
  verify_signature(wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,did:rust_did, message:Buffer, signature:Buffer)  : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.verify_signature(ctx,wallet_handle,pool_handle,did,message,signature)
    }
  encrypt(wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,my_did:rust_did,did:rust_did, message:Buffer)  : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.encrypt(ctx,wallet_handle,pool_handle,my_did,did,message)
    }
  decrypt(wallet_handle:rust_wallet_handle,myDid:rust_did,did:rust_did, encrypted:Buffer,nonce:Buffer)  : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.decrypt(ctx,wallet_handle,myDid,did,encrypted,nonce)
    }

    // anoncreds.rs
  issuer_create_and_store_claim_def(wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_json:json_object_or_serialized<JSON_Datum>,signature_type:string,create_non_revoc:boolean)  : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.issuer_create_and_store_claim_def(ctx,wallet_handle,issuer_did,schema_json,signature_type,create_non_revoc)
    }
  issuer_create_and_store_revoc_reg(wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_seq_no:number,max_claim_num:number) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.issuer_create_and_store_revoc_reg(ctx,wallet_handle,issuer_did,schema_seq_no,max_claim_num)
    }
  issuer_create_claim(wallet_handle:rust_wallet_handle,claim_req_json:number,claim_json:number,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.issuer_create_claim(ctx,wallet_handle,claim_req_json,claim_json,revoc_reg_seq_no,user_revoc_index)
    }
  issuer_revoke_claim(wallet_handle:rust_wallet_handle,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.issuer_revoke_claim(ctx,wallet_handle,revoc_reg_seq_no,revoc_reg_seq_no)
    }
  prover_store_claim_offer(wallet_handle:rust_wallet_handle,claim_offer_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.prover_store_claim_offer(ctx,wallet_handle,claim_offer_json)
    }
  prover_get_claim_offers(wallet_handle:rust_wallet_handle,filter_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.prover_get_claim_offers(ctx,wallet_handle,filter_json)
    }
  prover_create_master_secret(wallet_handle:rust_wallet_handle,master_secret_name:string) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.prover_create_master_secret(ctx,wallet_handle,master_secret_name)
    }
  prover_create_and_store_claim_req(wallet_handle:rust_wallet_handle,prover_did:rust_did,claim_offer_json:json_object_or_serialized<JSON_Datum>,claim_def_json:json_object_or_serialized<JSON_Datum>,master_secret_name:string) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.prover_create_and_store_claim_req(ctx,wallet_handle,prover_did,claim_offer_json,claim_def_json,master_secret_name)
    }
  prover_store_claim(wallet_handle:rust_wallet_handle,claims_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.prover_store_claim(ctx,wallet_handle,claims_json)
    }
  prover_get_claims(wallet_handle:rust_wallet_handle,filter_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.prover_get_claims(ctx,wallet_handle,filter_json)
    }
  prover_get_claims_for_proof_req(wallet_handle:rust_wallet_handle,proof_request_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.prover_get_claims_for_proof_req(ctx,wallet_handle,proof_request_json)
    }
  prover_create_proof(wallet_handle:rust_wallet_handle,proof_req_json:json_object_or_serialized<JSON_Datum>,requested_claims_json:json_object_or_serialized<JSON_Datum>,schemas_json:json_object_or_serialized<JSON_Datum>,master_secret_name:string,claim_defs_json:json_object_or_serialized<JSON_Datum>,revoc_regs_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.prover_create_proof(ctx,wallet_handle,proof_req_json,requested_claims_json,schemas_json,master_secret_name,claim_defs_json,revoc_regs_json)
    }
  verifier_verify_proof(proof_request_json:json_object_or_serialized<JSON_Datum>,proof_json:json_object_or_serialized<JSON_Datum>,schemas_json:json_object_or_serialized<JSON_Datum>,claim_defs_jsons:json_object_or_serialized<JSON_Datum>,revoc_regs_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.verifier_verify_proof(ctx,proof_request_json,proof_json,schemas_json,claim_defs_jsons,revoc_regs_json)
    }

  // agent.rs
  agent_connect(pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,sender_did:rust_did,receiver_did:rust_did,message_cb:agent_message_callback_type) : Promise<rust_connection_handle> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.agent_connect(ctx,pool_handle,wallet_handle,sender_did,receiver_did,message_cb)
    }
  agent_listen(endpoint:string,connection_cb:agent_connection_callback_type,message_cb:agent_message_callback_type) : Promise<rust_listener_handle> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.agent_listen(ctx,endpoint,connection_cb,message_cb)
    }
  agent_add_identity(listener_handle:rust_listener_handle,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void>  {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.agent_add_identity(ctx,listener_handle,pool_handle,wallet_handle,did)
    }
  agent_remove_identity(listener_handle:rust_listener_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.agent_remove_identity(ctx,listener_handle,wallet_handle,did)
    }
  agent_send(connection_handle:rust_connection_handle,message:string) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.agent_send(ctx,connection_handle,message)
    }
  agent_close_connection(connection_handle:rust_connection_handle) : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.agent_close_connection(ctx,connection_handle)
    }
  agent_close_listener(listener_handle:rust_listener_handle)  : Promise<void> {
    const ctx = new libindy_middleware_context(this.layers)
    return ctx.first.agent_close_listener(ctx,listener_handle)
    }

}
