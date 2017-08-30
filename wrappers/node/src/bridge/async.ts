
import {
  libindy_bridge,
  libindy_middleware,
  libindy_middleware_context,
  create_pool_ledger_config_options,
  open_pool_ledger_options,
  wallet_type_definition,
} from './api'
import {
  rust_listener_handle,
  rust_command_handle,
  rust_wallet_handle,
  rust_connection_handle,
  rust_pool_handle,
  rust_did,
  agent_message_callback_type,
  agent_connection_callback_type
} from '../ffi'

// this simply adds async to the promise library, recording the distinction
// between synchronous functions returning a promise and async functions
// returning a result.  No functionality is added here, only the symbolic
// marker explicit in this construct: 'await bridge.async.<rust-function>'
export class AsyncBridgeEntryPoint implements libindy_bridge {
  private readonly promise_to:libindy_bridge
  constructor(promise_to:libindy_bridge) {
    this.promise_to = promise_to
    }

  // pool.rs
  async create_pool_ledger_config(configuration_name:string,config_data:create_pool_ledger_config_options) : Promise<void> {
    return this.promise_to.create_pool_ledger_config(configuration_name,config_data)
    }
  async delete_pool_ledger_config(configuration_name:string) : Promise<void> {
    return this.promise_to.delete_pool_ledger_config(configuration_name)
    }
  async open_pool_ledger(configuration_name:string,config_data:open_pool_ledger_options) : Promise<rust_pool_handle> {
    return this.promise_to.open_pool_ledger(configuration_name,config_data)
    }
  async refresh_pool_ledger(pool_handle:rust_pool_handle) : Promise<void> {
    return this.promise_to.refresh_pool_ledger(pool_handle)
  }
  async close_pool_ledger(pool_handle:rust_pool_handle) : Promise<void> {
    return this.promise_to.close_pool_ledger(pool_handle)
  }

  // wallet.rs
  async register_wallet_type(wallet_type_name:string, wallet_callbacks:wallet_type_definition) : Promise<void> {
    return this.promise_to.register_wallet_type(wallet_type_name,wallet_callbacks)
  }
  async create_wallet(pool_name:string, wallet_name:string, wallet_type_name:string,config_data:any,credentials:any) : Promise<void> {
    return this.promise_to.create_wallet(pool_name,wallet_name,wallet_type_name,config_data,credentials)
  }
  async open_wallet(wallet_name:string,runtime_config:any,credentials:string) : Promise<rust_wallet_handle> {
    return this.promise_to.open_wallet(wallet_name,runtime_config,credentials)
  }
  async close_wallet(wallet_handle:rust_wallet_handle) : Promise<void> {
    return this.promise_to.close_wallet(wallet_handle)
  }
  async delete_wallet(wallet_name:string,credentials:any) : Promise<void> {
    return this.promise_to.delete_wallet(wallet_name,credentials)
  }

  // ledger.rs
  async sign_and_submit_request(pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:any) : Promise<void> {
    return this.promise_to.sign_and_submit_request(pool_handle,wallet_handle,submitter_did,request_json)
  }
  async submit_request(pool_handle:rust_pool_handle,request_json:any) : Promise<void> {
    return this.promise_to.submit_request(pool_handle,request_json)
  }
  async sign_request(wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:any)  : Promise<void> {
    return this.promise_to.sign_request(wallet_handle,submitter_did,request_json)
  }
  async build_get_ddo_request(submitter_did:rust_did,target_did:rust_did) : Promise<void> {
    return this.promise_to.build_get_ddo_request(submitter_did,target_did)
  }
  async build_nym_request(submitter_did:rust_did,target_did:rust_did,verkey:string,alias:string,role:string) : Promise<void> {
    return this.promise_to.build_nym_request(submitter_did,target_did,verkey,alias,role)
  }
  async build_attrib_request(submitter_did:rust_did,target_did:rust_did,hash:string,raw:string,enc:string) : Promise<void> {
    return this.promise_to.build_attrib_request(submitter_did,target_did,hash,raw,enc)
  }
  async build_get_attrib_request(submitter_did:rust_did,target_did:rust_did,data:any) : Promise<void> {
    return this.promise_to.build_get_attrib_request(submitter_did,target_did,data)
  }
  async build_get_nym_request(submitter_did:rust_did,target_did:rust_did) : Promise<void> {
    return this.promise_to.build_get_nym_request(submitter_did,target_did)
  }
  async build_schema_request(submitter_did:rust_did,data:any) : Promise<void> {
    return this.promise_to.build_schema_request(submitter_did,data)
  }
  async build_get_schema_request(submitter_did:rust_did,dest:string,data:any) : Promise<void> {
    return this.promise_to.build_get_schema_request(submitter_did,dest,data)
  }
  async build_claim_def_txn(submitter_did:rust_did,xref:number,signature_type:string, data:any) : Promise<void> {
    return this.promise_to.build_claim_def_txn(submitter_did,xref,signature_type,data)
  }
  async build_get_claim_def_txn(submitter_did:rust_did,xref:number,signature_type:string,origin:string) : Promise<void> {
    return this.promise_to.build_claim_def_txn(submitter_did,xref,signature_type,origin)
  }
  async build_node_request(submitter_did:rust_did,target_did:rust_did,data:any) : Promise<void> {
    return this.promise_to.build_node_request(submitter_did,target_did,data)
  }
  async build_get_txn_request(submitter_did:rust_did,data:number) : Promise<void> {
    return this.promise_to.build_get_txn_request(submitter_did,data)
  }

  // signus.rs
  async create_and_store_my_did(wallet_handle:rust_wallet_handle,did_json:any) : Promise<void> {
    return this.promise_to.create_and_store_my_did(wallet_handle,did_json)
  }
  async replace_keys(wallet_handle:rust_wallet_handle,did:rust_did,identity_json:any) : Promise<void> {
    return this.promise_to.replace_keys(wallet_handle,did,identity_json)
  }
  async store_their_did(wallet_handle:rust_wallet_handle,identity_json:any) : Promise<void> {
    return this.promise_to.store_their_did(wallet_handle,identity_json)
  }
  async sign(wallet_handle:rust_wallet_handle,did:rust_did, message:Buffer)  : Promise<void> {
    return this.promise_to.sign(wallet_handle,did,message)
  }
  async verify_signature(wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,did:rust_did, message:Buffer, signature:Buffer)  : Promise<void> {
    return this.promise_to.verify_signature(wallet_handle,pool_handle,did,message,signature)
  }
  async encrypt(wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,my_did:rust_did,did:rust_did, message:Buffer)  : Promise<void> {
    return this.promise_to.encrypt(wallet_handle,pool_handle,my_did,did,message)
  }
  async decrypt(wallet_handle:rust_wallet_handle,myDid:rust_did,did:rust_did, encrypted_message:Buffer,nonce:Buffer)  : Promise<void> {
    return this.promise_to.decrypt(wallet_handle,myDid,did,encrypted_message,nonce)
  }

  // anoncreds.rs
  async issuer_create_and_store_claim_def(wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_json:any,signature_type:string,create_non_revoc:boolean)  : Promise<void> {
    return this.promise_to.issuer_create_and_store_claim_def(wallet_handle,issuer_did,schema_json,signature_type,create_non_revoc)
  }
  async issuer_create_and_store_revoc_reg(wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_seq_no:number,max_claim_num:number) : Promise<void> {
    return this.promise_to.issuer_create_and_store_revoc_reg(wallet_handle,issuer_did,schema_seq_no,max_claim_num)
  }
  async issuer_create_claim(wallet_handle:rust_wallet_handle,claim_req_json:number,claim_json:number,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void> {
    return this.promise_to.issuer_create_claim(wallet_handle,claim_req_json,claim_json,revoc_reg_seq_no,user_revoc_index)
  }
  async issuer_revoke_claim(wallet_handle:rust_wallet_handle,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void> {
    return this.promise_to.issuer_revoke_claim(wallet_handle,revoc_reg_seq_no,user_revoc_index)
  }
  async prover_store_claim_offer(wallet_handle:rust_wallet_handle,claim_offer_json:any) : Promise<void> {
    return this.promise_to.prover_store_claim_offer(wallet_handle,claim_offer_json)
  }
  async prover_get_claim_offers(wallet_handle:rust_wallet_handle,filter_json:any) : Promise<void> {
    return this.promise_to.prover_get_claim_offers(wallet_handle,filter_json)
  }
  async prover_create_master_secret(wallet_handle:rust_wallet_handle,master_secret_name:string) : Promise<void> {
    return this.promise_to.prover_create_master_secret(wallet_handle,master_secret_name)
  }
  async prover_create_and_store_claim_req(wallet_handle:rust_wallet_handle,prover_did:rust_did,claim_offer_json:any,claim_def_json:any,master_secret_name:string) : Promise<void> {
    return this.promise_to.prover_create_and_store_claim_req(wallet_handle,prover_did,claim_offer_json,claim_def_json,master_secret_name)
  }
  async prover_store_claim(wallet_handle:rust_wallet_handle,claims_json:any) : Promise<void> {
    return this.promise_to.prover_store_claim(wallet_handle,claims_json)
  }
  async prover_get_claims(wallet_handle:rust_wallet_handle,filter_json:any) : Promise<void> {
    return this.promise_to.prover_get_claims(wallet_handle,filter_json)
  }
  async prover_get_claims_for_proof_req(wallet_handle:rust_wallet_handle,proof_request_json:any) : Promise<void> {
    return this.promise_to.prover_get_claims_for_proof_req(wallet_handle,proof_request_json)
  }
  async prover_create_proof(wallet_handle:rust_wallet_handle,proof_req_json:any,requested_claims_json:any,schemas_json:any,master_secret_name:string,claim_defs_json:any,revoc_regs_json:any) : Promise<void> {
    return this.promise_to.prover_create_proof(wallet_handle,proof_req_json,requested_claims_json,schemas_json,master_secret_name,claim_defs_json,revoc_regs_json)
  }
  async verifier_verify_proof(proof_request_json:any,proof_json:any,schemas_json:any,claim_defs_jsons:any,revoc_regs_json:any) : Promise<void> {
    return this.promise_to.verifier_verify_proof(proof_request_json,proof_json,schemas_json,claim_defs_jsons,revoc_regs_json)
  }


  // agent.rs
  async agent_connect(pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,sender_did:rust_did,receiver_did:rust_did,message_cb:agent_message_callback_type) : Promise<rust_connection_handle> {
    return this.promise_to.agent_connect(pool_handle,wallet_handle,sender_did,receiver_did,message_cb)
    }
  async agent_listen(endpoint:string,connection_cb:agent_connection_callback_type,message_cb:agent_message_callback_type) : Promise<rust_listener_handle> {
    return this.promise_to.agent_listen(endpoint,connection_cb,message_cb)
    }
  async agent_add_identity(listener_handle:rust_listener_handle,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void>  {
    return this.promise_to.agent_add_identity(listener_handle,pool_handle,wallet_handle,did)
    }
  async agent_remove_identity(listener_handle:rust_listener_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void> {
    return this.promise_to.agent_remove_identity(listener_handle,wallet_handle,did)
    }
  async agent_send(connection_handle:rust_connection_handle,message:string) : Promise<void> {
    return this.promise_to.agent_send(connection_handle,message)
    }
  async agent_close_connection(connection_handle:rust_connection_handle) : Promise<void> {
    return this.promise_to.agent_close_connection(connection_handle)
    }
  async agent_close_listener(listener_handle:rust_listener_handle)  : Promise<void> {
    return this.promise_to.agent_close_listener(listener_handle)
    }

}
