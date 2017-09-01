
import {
  libindy_middleware,
  libindy_middleware_context,
  create_pool_ledger_config_options,
  open_pool_ledger_options,
  wallet_type_definition,
  rust_connection_handle,
  rust_listener_handle,
  rust_command_handle,
  rust_wallet_handle,
  rust_pool_handle,
  rust_did,
  agent_message_callback_type,
  agent_connection_callback_type
} from '../bridge'

// this simply adds to the promise library, recording the distinction
// between synchronous functions returning a promise and functions
// returning a result.  No functionality is added here, only the symbolic
// marker explicit in this construct: 'await bridge.async.<rust-function>'
export class NotYetImplemented implements libindy_middleware {


  // pool.rs
  create_pool_ledger_config(ctx:libindy_middleware_context,configuration_name:string,config_data:create_pool_ledger_config_options) : Promise<void> {
    throw 'nyi'
    }
  delete_pool_ledger_config(ctx:libindy_middleware_context,configuration_name:string) : Promise<void> {
    throw 'nyi'
    }
  open_pool_ledger(ctx:libindy_middleware_context,configuration_name:string,config_data:open_pool_ledger_options) : Promise<rust_pool_handle> {
    throw 'nyi'
    }
  refresh_pool_ledger(ctx:libindy_middleware_context,pool_handle:rust_pool_handle) : Promise<void> {
    throw 'nyi'
  }
  close_pool_ledger(ctx:libindy_middleware_context,pool_handle:rust_pool_handle) : Promise<void> {
    throw 'nyi'
  }

  // wallet.rs
  register_wallet_type(ctx:libindy_middleware_context,wallet_type_name:string, wallet_callbacks:wallet_type_definition) : Promise<void> {
    throw 'nyi'
  }
  create_wallet(ctx:libindy_middleware_context,pool_name:string, wallet_name:string, wallet_type_name:string,config_data:any,credentials:any) : Promise<void> {
    throw 'nyi'
  }
  open_wallet(ctx:libindy_middleware_context,wallet_name:string,runtime_config:any,credentials:string) : Promise<rust_wallet_handle> {
    throw 'nyi'
  }
  close_wallet(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle) : Promise<void> {
    throw 'nyi'
  }
  delete_wallet(ctx:libindy_middleware_context,wallet_name:string,credentials:any) : Promise<void> {
    throw 'nyi'
  }

  // ledger.rs
  sign_and_submit_request(ctx:libindy_middleware_context,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:any) : Promise<void> {
    throw 'nyi'
  }
  submit_request(ctx:libindy_middleware_context,pool_handle:rust_pool_handle,request_json:any) : Promise<void> {
    throw 'nyi'
  }
  sign_request(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,submitter_did:rust_did,request_json:any)  : Promise<void> {
    throw 'nyi'
  }
  build_get_ddo_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did) : Promise<void> {
    throw 'nyi'
  }
  build_nym_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did,verkey:string,alias:string,role:string) : Promise<void> {
    throw 'nyi'
  }
  build_attrib_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did,hash:string,raw:string,enc:string) : Promise<void> {
    throw 'nyi'
  }
  build_get_attrib_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did,data:any) : Promise<void> {
    throw 'nyi'
  }
  build_get_nym_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did) : Promise<void> {
    throw 'nyi'
  }
  build_schema_request(ctx:libindy_middleware_context,submitter_did:rust_did,data:any) : Promise<void> {
    throw 'nyi'
  }
  build_get_schema_request(ctx:libindy_middleware_context,submitter_did:rust_did,dest:string,data:any) : Promise<void> {
    throw 'nyi'
  }
  build_claim_def_txn(ctx:libindy_middleware_context,submitter_did:rust_did,xref:number,signature_type:string, data:any) : Promise<void> {
    throw 'nyi'
  }
  build_get_claim_def_txn(ctx:libindy_middleware_context,submitter_did:rust_did,xref:number,signature_type:string,origin:string) : Promise<void> {
    throw 'nyi'
  }
  build_node_request(ctx:libindy_middleware_context,submitter_did:rust_did,target_did:rust_did,data:any) : Promise<void> {
    throw 'nyi'
  }
  build_get_txn_request(ctx:libindy_middleware_context,submitter_did:rust_did,data:number) : Promise<void> {
    throw 'nyi'
  }

  // signus.rs
  create_and_store_my_did(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,did_json:any) : Promise<void> {
    throw 'nyi'
  }
  replace_keys(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,did:rust_did,identity_json:any) : Promise<void> {
    throw 'nyi'
  }
  store_their_did(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,identity_json:any) : Promise<void> {
    throw 'nyi'
  }
  sign(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,did:rust_did, message:Buffer)  : Promise<void> {
    throw 'nyi'
  }
  verify_signature(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,did:rust_did, message:Buffer, signature:Buffer)  : Promise<void> {
    throw 'nyi'
  }
  encrypt(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,pool_handle:rust_pool_handle,my_did:rust_did,did:rust_did, message:Buffer)  : Promise<void> {
    throw 'nyi'
  }
  decrypt(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,myDid:rust_did,did:rust_did, encrypted_message:Buffer,nonce:Buffer)  : Promise<void> {
    throw 'nyi'
  }

  // anoncreds.rs
  issuer_create_and_store_claim_def(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_json:any,signature_type:string,create_non_revoc:boolean)  : Promise<void> {
    throw 'nyi'
  }
  issuer_create_and_store_revoc_reg(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,issuer_did:rust_did,schema_seq_no:number,max_claim_num:number) : Promise<void> {
    throw 'nyi'
  }
  issuer_create_claim(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,claim_req_json:number,claim_json:number,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void> {
    throw 'nyi'
  }
  issuer_revoke_claim(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,revoc_reg_seq_no:number,user_revoc_index:number) : Promise<void> {
    throw 'nyi'
  }
  prover_store_claim_offer(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,claim_offer_json:any) : Promise<void> {
    throw 'nyi'
  }
  prover_get_claim_offers(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,filter_json:any) : Promise<void> {
    throw 'nyi'
  }
  prover_create_master_secret(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,master_secret_name:string) : Promise<void> {
    throw 'nyi'
  }
  prover_create_and_store_claim_req(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,prover_did:rust_did,claim_offer_json:any,claim_def_json:any,master_secret_name:string) : Promise<void> {
    throw 'nyi'
  }
  prover_store_claim(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,claims_json:any) : Promise<void> {
    throw 'nyi'
  }
  prover_get_claims(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,filter_json:any) : Promise<void> {
    throw 'nyi'
  }
  prover_get_claims_for_proof_req(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,proof_request_json:any) : Promise<void> {
    throw 'nyi'
  }
  prover_create_proof(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle,proof_req_json:any,requested_claims_json:any,schemas_json:any,master_secret_name:string,claim_defs_json:any,revoc_regs_json:any) : Promise<void> {
    throw 'nyi'
  }
  verifier_verify_proof(ctx:libindy_middleware_context,proof_request_json:any,proof_json:any,schemas_json:any,claim_defs_jsons:any,revoc_regs_json:any) : Promise<void> {
    throw 'nyi'
  }

  agent_connect(ctx:libindy_middleware_context,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,sender_did:rust_did,receiver_did:rust_did,message_cb:agent_message_callback_type) : Promise<rust_connection_handle> {
    throw 'nyi'
    }
  agent_listen(ctx:libindy_middleware_context,endpoint:string,connection_cb:agent_connection_callback_type,message_cb:agent_message_callback_type) : Promise<rust_listener_handle> {
    throw 'nyi'
    }
  agent_add_identity(ctx:libindy_middleware_context,listener_handle:rust_listener_handle,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void>  {
    throw 'nyi'
    }
  agent_remove_identity(ctx:libindy_middleware_context,listener_handle:rust_listener_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void> {
    throw 'nyi'
    }
  agent_send(ctx:libindy_middleware_context,connection_handle:rust_connection_handle,message:string) : Promise<void> {
    throw 'nyi'
    }
  agent_close_connection(ctx:libindy_middleware_context,connection_handle:rust_connection_handle) : Promise<void> {
    throw 'nyi'
    }
  agent_close_listener(ctx:libindy_middleware_context,listener_handle:rust_listener_handle)  : Promise<void> {
    throw 'nyi'
    }

}
