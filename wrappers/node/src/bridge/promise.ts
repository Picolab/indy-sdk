
import { ErrorCode } from '../error'
import {
  libindy_bridge,
  create_pool_ledger_config_options,
  open_pool_ledger_options,
  wallet_type_definition,
  optional,
  wallet_credentials,
  json_object_or_serialized,
  JSON_Datum,
  open_wallet_options,
  delete_wallet_options,
  agent_connection_callback_type,
  agent_message_callback_type,
  rust_connection_handle,
  rust_listener_handle,
  rust_command_handle,
  rust_wallet_handle,
  rust_pool_handle,
  rust_did
} from './api'

import {
  FFICallbackBuilder,
  build_connection_callback,
  build_message_callback,
  build_object_handle_callback,
  build_receive_json_result_callback,
  build_default_callback,
} from '../rustlib'

import {
  libindy_middleware,
  libindy_middleware_context,
} from './middleware'

const debug = require('debug')('indy-sdk:promise')

export class PromiseImplementation implements libindy_middleware {
  private readonly ffi:any

  // we do not need to use the next_command_handle(), but it is exposed as a constant
  // here so we can identify it in the API if we need to use it.  it has a
  // constant value of zero.  We can make this an autoincrement if we need to
  // expose that for some reason, but it is always accessible in the ffi interface
  private command_handle : rust_command_handle = 0
  private next_command_handle() : rust_command_handle {
    if(this.increment_command_handle)
      this.command_handle++
    return this.command_handle;
  }

  private readonly validate_serialized_json_string_parameters : boolean = false
  private readonly increment_command_handle : boolean = false

  // allow the passing in of either string, object, or undefined and return
  // a JSON safe string
  private stringify_for_rust(payload:any) : string | undefined {
    if(payload === undefined || payload === null)
      return null
    if(typeof payload === "string") {
      if(this.validate_serialized_json_string_parameters)
        return JSON.stringify(JSON.parse(payload))
      // if not validating, just return the string as is
      return payload
    }
    // if this is anything other than a string or undefined, try to convert
    // it to a string
    return JSON.stringify(payload)
  }


  constructor(ffi:any,config?:{
    increment_command_handle?:boolean
    validate_serialized_json_string_parameters?:boolean
  }) {
    this.ffi = ffi

    this.increment_command_handle = (() => {
      if(config)
        return false || config.increment_command_handle
      return false
    })()

    this.validate_serialized_json_string_parameters = (() => {
      if(config)
        return false || config.validate_serialized_json_string_parameters
      return false
    })()
  }

  // when chaining middleware, if the caller has handed us a resolve/reject function
  // we need to make sure it is called after we call the core resolve/reject
  // implementation.
  private wrap_promise_completion(ctx:libindy_middleware_context,impl_resolve:any,impl_reject:any) : [any,any] {
    let resolve = impl_resolve
    let reject = impl_reject
    if(ctx.resolve) {
      resolve = (...args) => {
        impl_resolve(...args)
        ctx.resolve(...args)
      }
    }
    if(ctx.reject) {
      reject = (...args) => {
        impl_reject(...args)
        ctx.reject(...args)
      }
    }
    return [resolve,reject]
  }

  private call(ctx:libindy_middleware_context,
    target:any,callback_generator:any | null,...args) : Promise<any> {

    return new Promise<void>((resolve,reject) => {
      [resolve,reject] = this.wrap_promise_completion(ctx,resolve,reject)

      // apply appropriate callback if required
      if ( callback_generator !== null )
        args.push(callback_generator(resolve,reject))

      debug("CALLING:target = %s, args = %j",target.name,args)
      // call through the FFI
      const result = target(this.next_command_handle(),...args)

      debug("RESULT:%s",result)

      // these values will be returned by target
      // w/o calling the callback, so we must explicitly check for them
      // and reject the promise
      if(result != ErrorCode.Success) {
        debug("REJECTING BEFORE CALLBACK:result = %s",result)
        reject(result)
      }
    })
  }

  // pool.rs
  create_pool_ledger_config(ctx:libindy_middleware_context,
    configuration_name:string,
    config_data?:optional<json_object_or_serialized<create_pool_ledger_config_options>>) : Promise<void>
  {
    return this.call(ctx,
      this.ffi.indy_create_pool_ledger_config,
      build_default_callback,
      configuration_name,
      this.stringify_for_rust(config_data)
    )
  }
  delete_pool_ledger_config(ctx:libindy_middleware_context,configuration_name:string) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_delete_pool_ledger_config,
      build_default_callback,
      configuration_name
    )
  }
  open_pool_ledger(ctx:libindy_middleware_context,
    configuration_name:string,config_data?:
    json_object_or_serialized<open_pool_ledger_options>) : Promise<rust_pool_handle> {
    return this.call(ctx,
      this.ffi.indy_open_pool_ledger,
      build_object_handle_callback,
      configuration_name,
      this.stringify_for_rust(config_data)
    )
  }
  refresh_pool_ledger(ctx:libindy_middleware_context,pool_handle:rust_pool_handle) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_refresh_pool_ledger,
      build_default_callback,
      pool_handle
    )
  }
  close_pool_ledger(ctx:libindy_middleware_context,pool_handle:rust_pool_handle) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_close_pool_ledger,
      build_default_callback,
      pool_handle
    )
  }

  // wallet.rs
  register_wallet_type(ctx:libindy_middleware_context,wallet_type_name:string, wallet_callbacks:wallet_type_definition) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_register_wallet_type,
      build_default_callback,
      wallet_type_name,
      FFICallbackBuilder.build_create(wallet_callbacks.create),
      FFICallbackBuilder.build_open(wallet_callbacks.open),
      FFICallbackBuilder.build_set(wallet_callbacks.set),
      FFICallbackBuilder.build_get(wallet_callbacks.get),
      FFICallbackBuilder.build_get_not_expired(wallet_callbacks.get_not_expired),
      FFICallbackBuilder.build_list(wallet_callbacks.list),
      FFICallbackBuilder.build_close(wallet_callbacks.close),
      FFICallbackBuilder.build_delete(wallet_callbacks.delete),
      FFICallbackBuilder.build_free(wallet_callbacks.free),
      )
  }
  create_wallet(ctx:libindy_middleware_context,
    pool_name:string,
    wallet_name:string,
    wallet_type_name:string,
    config_data:optional<json_object_or_serialized<open_wallet_options>>,
    credentials:json_object_or_serialized<wallet_credentials>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_create_wallet,
      build_default_callback,
      pool_name,
      wallet_name,
      wallet_type_name,
      this.stringify_for_rust(config_data),
      this.stringify_for_rust(credentials)
    )

  }
  open_wallet(ctx:libindy_middleware_context,
    wallet_name:string,
    runtime_config:json_object_or_serialized<open_wallet_options>,
    credentials:json_object_or_serialized<wallet_credentials>) : Promise<rust_wallet_handle> {
    return this.call(ctx,
      this.ffi.indy_open_wallet,
      build_object_handle_callback,
      wallet_name,this.stringify_for_rust(runtime_config),this.stringify_for_rust(credentials),
    )
  }
  close_wallet(ctx:libindy_middleware_context,wallet_handle:rust_wallet_handle) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_close_wallet,
      build_default_callback,
      wallet_handle
    )
  }
  delete_wallet(ctx:libindy_middleware_context,
    wallet_name:string,
    credentials:json_object_or_serialized<wallet_credentials>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_delete_wallet,
      build_default_callback,
      wallet_name,this.stringify_for_rust(credentials),
    )
  }

  // ledger.rs
  sign_and_submit_request(ctx:libindy_middleware_context,
    pool_handle:rust_pool_handle,
    wallet_handle:rust_wallet_handle,
    submitter_did:rust_did,
    request_json:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_delete_wallet,
      build_receive_json_result_callback,
      pool_handle,wallet_handle,submitter_did,this.stringify_for_rust(request_json),
    )
  }
  submit_request(ctx:libindy_middleware_context,
    pool_handle:rust_pool_handle,
    request_json:json_object_or_serialized<JSON_Datum>) : Promise<JSON_Datum> {
      return this.call(ctx,
        this.ffi.indy_submit_request,
        build_receive_json_result_callback,
        pool_handle,this.stringify_for_rust(request_json),
      )
  }
  sign_request(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    submitter_did:rust_did,
    request_json:json_object_or_serialized<JSON_Datum>)  : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_sign_request,
      build_receive_json_result_callback,
      wallet_handle,submitter_did,this.stringify_for_rust(request_json),
    )
  }
  build_get_ddo_request(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    target_did:rust_did) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_get_ddo_request,
      build_receive_json_result_callback,
      submitter_did,target_did,
    )
  }
  build_nym_request(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    target_did:rust_did,
    verkey:string,
    alias:string,
    role:string) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_nym_request,
      build_receive_json_result_callback,
      submitter_did,target_did,verkey,alias,role,
    )
  }
  build_attrib_request(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    target_did:rust_did,
    hash:string,
    raw:string,
    enc:string) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_attrib_request,
      build_receive_json_result_callback,
      submitter_did,target_did,hash,raw,enc,
    )
  }
  build_get_attrib_request(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    target_did:rust_did,
    data:any) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_get_attrib_request,
      build_receive_json_result_callback,
      submitter_did,target_did,this.stringify_for_rust(data),
    )
  }
  build_get_nym_request(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    target_did:rust_did) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_get_nym_request,
      build_receive_json_result_callback,
      submitter_did,target_did,
    )
  }
  build_schema_request(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    data:any) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_schema_request,
      build_receive_json_result_callback,
      submitter_did,this.stringify_for_rust(data),
    )
  }
  build_get_schema_request(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    dest:string,
    data:any) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_get_schema_request,
      build_receive_json_result_callback,
      submitter_did,dest,this.stringify_for_rust(data),
    )
  }
  build_claim_def_txn(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    xref:number,
    signature_type:string,
    data:any) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_claim_def_txn,
      build_receive_json_result_callback,
      submitter_did,xref,signature_type,this.stringify_for_rust(data),
    )
  }
  build_get_claim_def_txn(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    xref:number,
    signature_type:string,
    origin:string) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_get_claim_def_txn,
      build_receive_json_result_callback,
      submitter_did,xref,signature_type,origin
    )
  }
  build_node_request(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    target_did:rust_did,
    data:any) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_node_request,
      build_receive_json_result_callback,
      submitter_did,target_did,this.stringify_for_rust(data)
    )
  }
  build_get_txn_request(ctx:libindy_middleware_context,
    submitter_did:rust_did,
    data:number) : Promise<JSON_Datum> {
    return this.call(ctx,
      this.ffi.indy_build_get_txn_request,
      build_receive_json_result_callback,
      submitter_did,data,
    )
  }

  // signus.rs
  create_and_store_my_did(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    did_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_create_and_store_my_did,
      build_receive_json_result_callback,
      wallet_handle,this.stringify_for_rust(did_json),
    )
  }
  replace_keys(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    did:rust_did,
    identity_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_create_and_store_my_did,
      build_default_callback,
      wallet_handle,did,this.stringify_for_rust(identity_json)
    )
  }
  store_their_did(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    identity_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_store_their_did,
      build_default_callback,
      wallet_handle,this.stringify_for_rust(identity_json),
    )
  }
  sign(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    did:rust_did,
    message:Buffer) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_sign,
      build_default_callback,
      wallet_handle,did,message.buffer,message.length,
    )
  }
  verify_signature(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    pool_handle:rust_pool_handle,
    did:rust_did,
    message:Buffer,
    signature:Buffer)  : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_verify_signature,
      build_receive_json_result_callback,
      wallet_handle,pool_handle,did,message.buffer,message.length,signature.buffer,signature.length,
    )
  }
  encrypt(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    pool_handle:rust_pool_handle,
    my_did:rust_did,
    did:rust_did,
    message:Buffer) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_encrypt,
      build_default_callback,
      wallet_handle,pool_handle,my_did,did,message.buffer,message.length,
    )
  }
  decrypt(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    myDid:rust_did,
    did:rust_did,
    encrypted:Buffer,
    nonce:Buffer)  : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_decrypt,
      build_default_callback,
      wallet_handle,myDid,did,encrypted.buffer,encrypted.length,nonce.buffer,nonce.length,
    )
  }

  // anoncreds.rs
  issuer_create_and_store_claim_def(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    issuer_did:rust_did,
    schema_json:any,
    signature_type:string,
    create_non_revoc:boolean)  : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_issuer_create_and_store_claim_def,
      build_default_callback,
      wallet_handle,issuer_did,this.stringify_for_rust(schema_json),signature_type,create_non_revoc,
    )
  }
  issuer_create_and_store_revoc_reg(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    issuer_did:rust_did,
    schema_seq_no:number,
    max_claim_num:number) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_issuer_create_and_store_revoc_reg,
      build_default_callback,
      wallet_handle,issuer_did,schema_seq_no,max_claim_num,
    )
  }
  issuer_create_claim(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    claim_req_json:number,
    claim_json:number,
    revoc_reg_seq_no:number,
    user_revoc_index:number) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_issuer_create_claim,
      build_default_callback,
      wallet_handle,this.stringify_for_rust(claim_req_json),this.stringify_for_rust(claim_json),revoc_reg_seq_no,user_revoc_index,
    )
  }
  issuer_revoke_claim(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    revoc_reg_seq_no:number,
    user_revoc_index:number) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_issuer_revoke_claim,
      build_default_callback,
      wallet_handle,revoc_reg_seq_no,user_revoc_index,
    )
  }
  prover_store_claim_offer(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    claim_offer_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_prover_store_claim_offer,
      build_default_callback,
      wallet_handle,this.stringify_for_rust(claim_offer_json),
    )
  }
  prover_get_claim_offers(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    filter_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_prover_get_claim_offers,
      build_default_callback,
      wallet_handle,this.stringify_for_rust(filter_json),
    )
  }
  prover_create_master_secret(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    master_secret_name:string) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_prover_create_master_secret,
      build_default_callback,
      wallet_handle,master_secret_name,
    )
  }
  prover_create_and_store_claim_req(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    prover_did:rust_did,
    claim_offer_json:json_object_or_serialized<JSON_Datum>,
    claim_def_json:json_object_or_serialized<JSON_Datum>,
    master_secret_name:string) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_prover_create_and_store_claim_req,
      build_default_callback,
      wallet_handle,prover_did,this.stringify_for_rust(claim_offer_json),this.stringify_for_rust(claim_def_json),master_secret_name,
    )
  }
  prover_store_claim(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    claims_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_prover_store_claim,
      build_default_callback,
      wallet_handle,this.stringify_for_rust(claims_json),
    )
  }
  prover_get_claims(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    filter_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_prover_get_claims,
      build_default_callback,
      wallet_handle,this.stringify_for_rust(filter_json),
    )
  }
  prover_get_claims_for_proof_req(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    proof_request_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_prover_get_claims_for_proof_req,
      build_default_callback,
      wallet_handle,this.stringify_for_rust(proof_request_json),
    )
  }
  prover_create_proof(ctx:libindy_middleware_context,
    wallet_handle:rust_wallet_handle,
    proof_req_json:json_object_or_serialized<JSON_Datum>,
    requested_claims_json:json_object_or_serialized<JSON_Datum>,
    schemas_json:json_object_or_serialized<JSON_Datum>,
    master_secret_name:string,
    claim_defs_json:json_object_or_serialized<JSON_Datum>,
    revoc_regs_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_prover_create_proof,
      build_default_callback,
      wallet_handle,this.stringify_for_rust(proof_req_json),this.stringify_for_rust(requested_claims_json),this.stringify_for_rust(schemas_json),master_secret_name,this.stringify_for_rust(claim_defs_json),this.stringify_for_rust(revoc_regs_json),
    )
  }
  verifier_verify_proof(ctx:libindy_middleware_context,
    proof_request_json:json_object_or_serialized<JSON_Datum>,
    proof_json:json_object_or_serialized<JSON_Datum>,
    schemas_json:json_object_or_serialized<JSON_Datum>,
    claim_defs_jsons:json_object_or_serialized<JSON_Datum>,
    revoc_regs_json:json_object_or_serialized<JSON_Datum>) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_verifier_verify_proof,
      build_default_callback,
      this.stringify_for_rust(proof_request_json),this.stringify_for_rust(proof_json),this.stringify_for_rust(schemas_json),this.stringify_for_rust(claim_defs_jsons),this.stringify_for_rust(revoc_regs_json),
    )
  }

  // agent.rs
  agent_connect(ctx:libindy_middleware_context,
    pool_handle:rust_pool_handle,
    wallet_handle:rust_wallet_handle,
    sender_did:rust_did,
    receiver_did:rust_did,
    message_cb:agent_message_callback_type) : Promise<rust_connection_handle> {

    return new Promise<rust_connection_handle>((resolve,reject) => {
      [resolve,reject] = this.wrap_promise_completion(ctx,resolve,reject)

      // call through the FFI
      const result = this.ffi.indy_agent_connect(this.next_command_handle(),
        pool_handle,wallet_handle,sender_did,receiver_did,
        build_object_handle_callback(resolve,reject),
        build_message_callback(message_cb)
      )
      // these values will be returned by target
      // w/o calling the callback, so we must explicitly check for them
      // and reject the promise
      if(result != ErrorCode.Success)
        reject(result)

    })
  }

  agent_listen(ctx:libindy_middleware_context,endpoint:string,connection_cb:agent_connection_callback_type,message_cb:agent_message_callback_type) : Promise<rust_listener_handle> {

    return new Promise<rust_listener_handle>((resolve,reject) => {
      [resolve,reject] = this.wrap_promise_completion(ctx,resolve,reject)

      // call through the FFI
      const result = this.ffi.indy_agent_listen(this.next_command_handle(),
        endpoint,
        build_object_handle_callback(resolve,reject),
        build_connection_callback(connection_cb),
        build_message_callback(message_cb)
      )
      // these values will be returned by target
      // w/o calling the callback, so we must explicitly check for them
      // and reject the promise
      if(result != ErrorCode.Success)
        reject(result)

    })
  }
  agent_add_identity(ctx:libindy_middleware_context,listener_handle:rust_listener_handle,pool_handle:rust_pool_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_agent_add_identity,
      build_default_callback,
      listener_handle,pool_handle,wallet_handle,did
    )
  }

  agent_remove_identity(ctx:libindy_middleware_context,listener_handle:rust_listener_handle,wallet_handle:rust_wallet_handle,did:rust_did) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_agent_remove_identity,
      build_default_callback,
      listener_handle,wallet_handle,did
    )
  }
  agent_send(ctx:libindy_middleware_context,connection_handle:rust_connection_handle,message:string) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_agent_send,
      build_default_callback,
      connection_handle,message
    )
  }
  agent_close_connection(ctx:libindy_middleware_context,connection_handle:rust_connection_handle) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_agent_close_connection,
      build_default_callback,
      connection_handle
    )
  }
  agent_close_listener(ctx:libindy_middleware_context,listener_handle:rust_listener_handle) : Promise<void> {
    return this.call(ctx,
      this.ffi.indy_agent_close_listener,
      build_default_callback,
      listener_handle
    )
  }

}
