import * as ffi from 'ffi'

// this is a translation of the libindy error code enumeration
export class ErrorCodes {
    static Success = 0

    // Common errors

    // Caller passed invalid value as param 1 (null invalid json and etc..)
    static CommonInvalidParam1 = 100

    // Caller passed invalid value as param 2 (null invalid json and etc..)
    static CommonInvalidParam2 = 101

    // Caller passed invalid value as param 3 (null invalid json and etc..)
    static CommonInvalidParam3 = 102

    // Caller passed invalid value as param 4 (null invalid json and etc..)
    static CommonInvalidParam4 = 103

    // Caller passed invalid value as param 5 (null invalid json and etc..)
    static CommonInvalidParam5 = 104

    // Caller passed invalid value as param 6 (null invalid json and etc..)
    static CommonInvalidParam6 = 105

    // Caller passed invalid value as param 7 (null invalid json and etc..)
    static CommonInvalidParam7 = 106

    // Caller passed invalid value as param 8 (null invalid json and etc..)
    static CommonInvalidParam8 = 107

    // Caller passed invalid value as param 9 (null invalid json and etc..)
    static CommonInvalidParam9 = 108

    // Caller passed invalid value as param 10 (null invalid json and etc..)
    static CommonInvalidParam10 = 109

    // Caller passed invalid value as param 11 (null invalid json and etc..)
    static CommonInvalidParam11 = 110

    // Caller passed invalid value as param 12 (null invalid json and etc..)
    static CommonInvalidParam12 = 111

    // Invalid library state was detected in runtime. It signals library bug
    static CommonInvalidState = 112

    // Object (json config key claim and etc...) passed by library caller has invalid structure
    static CommonInvalidStructure = 113

    // IO Error
    static CommonIOError = 114

    // Wallet errors
    // Caller passed invalid wallet handle
    static WalletInvalidHandle = 200

    // Unknown type of wallet was passed on create_wallet
    static WalletUnknownTypeError = 201

    // Attempt to register already existing wallet type
    static WalletTypeAlreadyRegisteredError = 202

    // Attempt to create wallet with name used for another exists wallet
    static WalletAlreadyExistsError = 203

    // Requested entity id isn't present in wallet
    static WalletNotFoundError = 204

    // Trying to use wallet with pool that has different name
    static WalletIncompatiblePoolError = 205

    // Trying to open wallet that was opened already
    static WalletAlreadyOpenedError = 206

    // Ledger errors
    // Trying to open pool ledger that wasn't created before
    static PoolLedgerNotCreatedError = 300

    // Caller passed invalid pool ledger handle
    static PoolLedgerInvalidPoolHandle = 301

    // Pool ledger terminated
    static PoolLedgerTerminated = 302

    // No concensus during ledger operation
    static LedgerNoConsensusError = 303

    // Attempt to send unknown or incomplete transaction message
    static LedgerInvalidTransaction = 304

    // Attempt to send transaction without the necessary privileges
    static LedgerSecurityError = 305

    // Attempt to create pool ledger config with name used for another existing pool
    static PoolLedgerConfigAlreadyExistsError = 306

    // Revocation registry is full and creation of new registry is necessary
    static AnoncredsRevocationRegistryFullError = 400

    static AnoncredsInvalidUserRevocIndex = 401

    static AnoncredsAccumulatorIsFull = 402

    static AnoncredsNotIssuedError = 403

    // Attempt to generate master secret with dupplicated name
    static AnoncredsMasterSecretDuplicateNameError = 404

    static AnoncredsProofRejected = 405

    // Signus errors
    // Unknown format of DID entity keys
    static SignusUnknownCryptoError = 500

}

// this is a base error class for throwing, when, for example, a callback
// only gets an integer and it wants to map it to the Enum
export class IndyError extends Error {
  readonly code:number
  constructor (code: number) {
    super()
    this.code = code
  }
};

// automatically configure and instantiate the rust library FFI interface w/o
// chance for configuration or intervention by the user
const bindings = ffi.Library('libindy',{
  // pool.rs
  'indy_create_pool_ledger_config': ['int', ['int','string','string','pointer']],
  'indy_open_pool_ledger':['int', ['int', 'string', 'string', 'pointer']],
  'indy_refresh_pool_ledger':['int', ['int', 'int', 'pointer']],
  'indy_close_pool_ledger':['int', ['int', 'int', 'pointer']],
  'indy_delete_pool_ledger_config':['int', ['int', 'string', 'pointer']],

  // wallet.rs
  'indy_register_wallet_type':['int',['int', 'string',
     'pointer', 'pointer', 'pointer', 'pointer', 'pointer', 'pointer',
     'pointer', 'pointer', 'pointer', 'pointer']],
  'indy_create_wallet':['int',['int', 'string', 'string', 'string', 'string', 'string', 'pointer']],
  'indy_open_wallet':['int',['int', 'string', 'string', 'string', 'pointer']],
  'indy_close_wallet':['int',['int', 'int', 'pointer']],
  'indy_delete_wallet':['int',['int', 'string', 'string', 'pointer']],

	// ledger.rs
	'indy_sign_and_submit_request':['int',['int', 'int', 'int', 'string', 'string', 'pointer']],
	'indy_submit_request':['int',['int', 'int', 'string', 'pointer']],
	'indy_sign_request':['int',['int', 'int', 'string', 'string', 'pointer']],
	'indy_build_get_ddo_request':['int',['int', 'string', 'string', 'pointer']],
	'indy_build_nym_request':['int',['int', 'string', 'string', 'string', 'string', 'string', 'pointer']],
	'indy_build_attrib_request':['int',['int', 'string', 'string', 'string', 'string', 'string', 'pointer']],
	'indy_build_get_attrib_request':['int',['int', 'string', 'string', 'string', 'pointer']],
	'indy_build_get_nym_request':['int',['int', 'string', 'string', 'pointer']],
	'indy_build_schema_request':['int',['int', 'string', 'string', 'pointer']],
	'indy_build_get_schema_request':['int',['int', 'string', 'string', 'string', 'pointer']],
	'indy_build_claim_def_txn':['int',['int', 'string', 'int', 'string', 'string', 'pointer']],
	'indy_build_get_claim_def_txn':['int',['int', 'string', 'int', 'string', 'string', 'pointer']],
	'indy_build_node_request':['int',['int', 'string', 'string', 'string', 'pointer']],
	'indy_build_get_txn_request':['int',['int', 'string', 'int', 'pointer']],

	// signus.rs
	'indy_create_and_store_my_did':['int',['int', 'int', 'string', 'pointer']],
	'indy_replace_keys':['int',['int', 'int', 'string', 'string', 'pointer']],
	'indy_store_their_did':['int',['int', 'int', 'string', 'pointer']],
	'indy_sign':['int',['int', 'int', 'string', 'pointer', 'int', 'pointer']],
	'indy_verify_signature':['int',['int', 'int', 'int', 'string', 'pointer', 'int', 'pointer', 'int', 'pointer']],
	'indy_encrypt':['int',['int', 'int', 'int', 'string', 'string', 'pointer', 'int', 'pointer']],
	'indy_decrypt':['int',['int', 'int', 'string', 'string', 'pointer', 'int', 'pointer', 'int', 'pointer']],

	// anoncreds.rs
	'indy_issuer_create_and_store_claim_def':['int',['int', 'int', 'string', 'string', 'string', 'bool', 'pointer']],
	'indy_issuer_create_and_store_revoc_reg':['int',['int', 'int', 'string', 'int', 'int', 'pointer']],
	'indy_issuer_create_claim':['int',['int', 'int', 'string', 'string', 'int', 'int', 'pointer']],
	'indy_issuer_revoke_claim':['int',['int', 'int', 'int', 'int', 'pointer']],
	'indy_prover_store_claim_offer':['int',['int', 'int', 'string', 'pointer']],
	'indy_prover_get_claim_offers':['int',['int', 'int', 'string', 'pointer']],
	'indy_prover_create_master_secret':['int',['int', 'int', 'string', 'pointer']],
	'indy_prover_create_and_store_claim_req':['int',['int', 'int', 'string', 'string', 'string', 'string', 'pointer']],
	'indy_prover_store_claim':['int',['int', 'int', 'string', 'pointer']],
	'indy_prover_get_claims':['int',['int', 'int', 'string', 'pointer']],
	'indy_prover_get_claims_for_proof_req':['int',['int', 'int', 'string', 'pointer']],
	'indy_prover_create_proof':['int',['int', 'int', 'string', 'string', 'string', 'string', 'string', 'string', 'pointer']],
	'indy_verifier_verify_proof':['int',['int', 'string', 'string', 'string', 'string']],

	// agent.rs
	'indy_agent_connect':['int',['int', 'int', 'int', 'string', 'string', 'pointer', 'pointer']],
	'indy_agent_listen':['int',['int', 'string', 'pointer', 'pointer', 'pointer']],
	'indy_agent_add_identity':['int',['int', 'int', 'int', 'int', 'string', 'pointer']],
	'indy_agent_remove_identity':['int',['int', 'int', 'int', 'string', 'pointer']],
	'indy_agent_send':['int',['int', 'int', 'string', 'pointer']],
	'indy_agent_close_connection':['int',['int', 'int', 'pointer']],
	'indy_agent_close_listener':['int',['int','int','pointer']]

})



// these three are all promise callback
// resolves to void or throws error.  the rust library calls continue down this
// line, with a void resolution and an IndyError in the event of a non-zero
// 'int'.
//
function build_default_callback(resolve:any,reject:any) {
  return ffi.Callback('void', ['int','int'],
    (command_handle:number, error_code:number) => {
      if(error_code == 0) {
        resolve()
      }
      else {
        reject(new IndyError(error_code))
      }
    });
}

// the open functions often hand back an integer value
function build_object_handle_callback(resolve:any,reject:any) {
  return ffi.Callback('void', ['int','int','int'],
    (command_handle:number, error_code:number,result:number) => {
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
  return ffi.Callback('void', ['int', 'int','string'],
  (command_handle:number, error_code:number,result:string) => {
    if(error_code == 0) {
      try {
        const prasedResult : any = JSON.parse(result)
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
                                err: number,
                                connection_handle: i32,
                                sender_did: *const c_char,
                                receiver_did: *const c_char)>,
*/
export function build_connection_callback(target:(command_handle:number, error_code:number,connection_handle:number,sender_did:string,receiver_did:string) => void) {
  return ffi.Callback('void', ['int', 'int','int','string','string'],target)
}

/*
message_cb: Option<extern fn(xconnection_handle: i32,
                             err: number,
                             message: *const c_char)>) -> number {
*/
export function build_message_callback(target:(command_handle:number, error_code:number,message:string) => void) {
  return ffi.Callback('void', ['int', 'int','string'],target);
}



export const FFICallbackBuilder = {
  //create: Option<extern fn(name: *const c_char,
  //                       config: *const c_char,
  //                       credentials: *const c_char) -> number>,
  build_create:(target:()=>any) => {
    const args = ['string', 'string' ,'string']
    return ffi.Callback('int',args,target)
  },

  //open: Option<extern fn(name: *const c_char,
  //                       config: *const c_char,
  //                       runtime_config: *const c_char,
  //                       credentials: *const c_char,
  //                       handle: *mut i32) -> number>,
  build_open:(target:()=>any) => {
    const args = ['string', 'string','string','string','pointer']
    return ffi.Callback('int',args,target)
  },

  //set: Option<extern fn(handle: i32,
  //                    key: *const c_char,
  //                    value: *const c_char) -> number>,
  build_set:(target:()=>any) => {
    const args = ['int','string','string']
      return ffi.Callback('int',args,target)
    },

  //get: Option<extern fn(handle: i32,
  //                    key: *const c_char,
  //                    value_ptr: *mut *const c_char) -> number>,
  build_get:(target:()=>any) => {
    const args = ['int','string','pointer']
    return ffi.Callback('int',args,target)
  },

  //get_not_expired: Option<extern fn(handle: i32,
  //                                key: *const c_char,
  //                                value_ptr: *mut *const c_char) -> number>,
  build_get_not_expired:(target:()=>any) => {
    const args = ['int','string','pointer']
    return ffi.Callback('int',args,target)
  },

  //list: Option<extern fn(handle: i32,
  //                     key_prefix: *const c_char,
  //                     values_json_ptr: *mut *const c_char) -> number>,
  build_list:(target:()=>any) => {
    const args = ['int','string','pointer']
    return ffi.Callback('int',args,target)
  },

  //close: Option<extern fn(handle: i32) -> number>,
  build_close:(target:()=>any) => {
    const args = ['int']
    return ffi.Callback('int',args,target)
  },

  //delete: Option<extern fn(name: *const c_char,
  //                       config: *const c_char,
  //                       credentials: *const c_char) -> number>,
  build_delete:(target:()=>any) => {
    const args = ['string','string','string']
    return ffi.Callback('int',args,target)
  },

  //free: Option<extern fn(wallet_handle: i32,
  //                     value: *const c_char) -> number>,
  build_free:(target:()=>any) => {
    const args = ['int','string']
    return ffi.Callback('int',args,target)
  }
}




// allow the passing in of either string, object, or undefined and return
// a JSON safe string
function stringify_for_rust(payload:any) : string | undefined {
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



function call(
    target:any,callback_generator:any | null,...args) : Promise<any> {

    return new Promise<void>((resolve,reject) => {

      // apply appropriate callback if required
      if ( callback_generator !== null )
        args.push(callback_generator(resolve,reject))

      // call through the FFI
      const result = target(this.next_command_handle(),...args)

      // these values will be returned by target
      // w/o calling the callback, so we must explicitly check for them
      // and reject the promise
      if(result != ErrorCodes.Success) {
        reject(result)
      }
    })
  }

// pool.rs
export function create_pool_ledger_config(
  configuration_name:string,
  config_data?:any) : Promise<void>
{
  return call(
    ffi.indy_create_pool_ledger_config,
    build_default_callback,
    configuration_name,
    this.stringify_for_rust(config_data)
  )
}

export function  delete_pool_ledger_config(configuration_name:string) : Promise<void> {
  return call(
    ffi.indy_delete_pool_ledger_config,
    build_default_callback,
    configuration_name
  )
}

export function  open_pool_ledger(
  configuration_name:string,config_data?:any) : Promise<number> {
  return call(
    ffi.indy_open_pool_ledger,
    build_object_handle_callback,
    configuration_name,
    this.stringify_for_rust(config_data)
  )
}
export function  refresh_pool_ledger(pool_handle:number) : Promise<void> {
  return call(
    ffi.indy_refresh_pool_ledger,
    build_default_callback,
    pool_handle
  )
}
export function close_pool_ledger(pool_handle:number) : Promise<void> {
  return call(
    ffi.indy_close_pool_ledger,
    build_default_callback,
    pool_handle
  )
}

// wallet.rs
export function register_wallet_type(wallet_type_name:string, wallet_callbacks:any) : Promise<void> {
  return call(
    ffi.indy_register_wallet_type,
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
export function create_wallet(
  pool_name:string,
  wallet_name:string,
  wallet_type_name:string,
  config_data?:any,
  credentials?:any) : Promise<void> {
  return call(
    ffi.indy_create_wallet,
    build_default_callback,
    pool_name,
    wallet_name,
    wallet_type_name,
    this.stringify_for_rust(config_data),
    this.stringify_for_rust(credentials)
  )

}
export function open_wallet(
  wallet_name:string,
  runtime_config:any,
  credentials:any) : Promise<number> {
  return call(
    ffi.indy_open_wallet,
    build_object_handle_callback,
    wallet_name,this.stringify_for_rust(runtime_config),this.stringify_for_rust(credentials),
  )
}
export function close_wallet(wallet_handle:number) : Promise<void> {
  return call(
    ffi.indy_close_wallet,
    build_default_callback,
    wallet_handle
  )
}
export function delete_wallet(
  wallet_name:string,
  credentials:any) : Promise<void> {
  return call(
    ffi.indy_delete_wallet,
    build_default_callback,
    wallet_name,this.stringify_for_rust(credentials),
  )
}

// ledger.rs
export function sign_and_submit_request(
  pool_handle:number,
  wallet_handle:number,
  submitter_did:string,
  request_json:any) : Promise<any> {
  return call(
    ffi.indy_delete_wallet,
    build_receive_json_result_callback,
    pool_handle,wallet_handle,submitter_did,this.stringify_for_rust(request_json),
  )
}
export function submit_request(
  pool_handle:number,
  request_json:any ): Promise<any> {
    return call(
      ffi.indy_submit_request,
      build_receive_json_result_callback,
      pool_handle,this.stringify_for_rust(request_json),
    )
}
export function sign_request(
  wallet_handle:number,
  submitter_did:string,
  request_json:any)  : Promise<any> {
  return call(
    ffi.indy_sign_request,
    build_receive_json_result_callback,
    wallet_handle,submitter_did,this.stringify_for_rust(request_json),
  )
}
export function build_get_ddo_request(
  submitter_did:string,
  target_did:string) : Promise<any> {
  return call(
    ffi.indy_build_get_ddo_request,
    build_receive_json_result_callback,
    submitter_did,target_did,
  )
}
export function build_nym_request(
  submitter_did:string,
  target_did:string,
  verkey:string,
  alias:string,
  role:string) : Promise<any> {
  return call(
    ffi.indy_build_nym_request,
    build_receive_json_result_callback,
    submitter_did,target_did,verkey,alias,role,
  )
}
export function build_attrib_request(
  submitter_did:string,
  target_did:string,
  hash:string,
  raw:string,
  enc:string) : Promise<any> {
  return call(
    ffi.indy_build_attrib_request,
    build_receive_json_result_callback,
    submitter_did,target_did,hash,raw,enc,
  )
}
export function build_get_attrib_request(
  submitter_did:string,
  target_did:string,
  data:any) : Promise<any> {
  return call(
    ffi.indy_build_get_attrib_request,
    build_receive_json_result_callback,
    submitter_did,target_did,this.stringify_for_rust(data),
  )
}
export function build_get_nym_request(
  submitter_did:string,
  target_did:string) : Promise<any> {
  return call(
    ffi.indy_build_get_nym_request,
    build_receive_json_result_callback,
    submitter_did,target_did,
  )
}
export function build_schema_request(
  submitter_did:string,
  data:any) : Promise<any> {
  return call(
    ffi.indy_build_schema_request,
    build_receive_json_result_callback,
    submitter_did,this.stringify_for_rust(data),
  )
}
export function build_get_schema_request(
  submitter_did:string,
  dest:string,
  data:any) : Promise<any> {
  return call(
    ffi.indy_build_get_schema_request,
    build_receive_json_result_callback,
    submitter_did,dest,this.stringify_for_rust(data),
  )
}
export function build_claim_def_txn(
  submitter_did:string,
  xref:number,
  signature_type:string,
  data:any) : Promise<any> {
  return call(
    ffi.indy_build_claim_def_txn,
    build_receive_json_result_callback,
    submitter_did,xref,signature_type,this.stringify_for_rust(data),
  )
}
export function build_get_claim_def_txn(
  submitter_did:string,
  xref:number,
  signature_type:string,
  origin:string) : Promise<any> {
  return call(
    ffi.indy_build_get_claim_def_txn,
    build_receive_json_result_callback,
    submitter_did,xref,signature_type,origin
  )
}
export function build_node_request(
  submitter_did:string,
  target_did:string,
  data:any) : Promise<any> {
  return call(
    ffi.indy_build_node_request,
    build_receive_json_result_callback,
    submitter_did,target_did,this.stringify_for_rust(data)
  )
}
export function build_get_txn_request(
  submitter_did:string,
  data:number) : Promise<any> {
  return call(
    ffi.indy_build_get_txn_request,
    build_receive_json_result_callback,
    submitter_did,data,
  )
}

// signus.rs
export function create_and_store_my_did(
  wallet_handle:number,
  did_json:any) : Promise<void> {
  return call(
    ffi.indy_create_and_store_my_did,
    build_receive_json_result_callback,
    wallet_handle,this.stringify_for_rust(did_json),
  )
}
export function replace_keys(
  wallet_handle:number,
  did:string,
  identity_json:any) : Promise<void> {
  return call(
    ffi.indy_create_and_store_my_did,
    build_default_callback,
    wallet_handle,did,this.stringify_for_rust(identity_json)
  )
}
export function store_their_did(
  wallet_handle:number,
  identity_json:any) : Promise<void> {
  return call(
    ffi.indy_store_their_did,
    build_default_callback,
    wallet_handle,this.stringify_for_rust(identity_json),
  )
}
export function sign(
  wallet_handle:number,
  did:string,
  message:Buffer) : Promise<void> {
  return call(
    ffi.indy_sign,
    build_default_callback,
    wallet_handle,did,message.buffer,message.length,
  )
}
export function verify_signature(
  wallet_handle:number,
  pool_handle:number,
  did:string,
  message:Buffer,
  signature:Buffer)  : Promise<void> {
  return call(
    ffi.indy_verify_signature,
    build_receive_json_result_callback,
    wallet_handle,pool_handle,did,message.buffer,message.length,signature.buffer,signature.length,
  )
}
export function encrypt(
  wallet_handle:number,
  pool_handle:number,
  my_did:string,
  did:string,
  message:Buffer) : Promise<void> {
  return call(
    ffi.indy_encrypt,
    build_default_callback,
    wallet_handle,pool_handle,my_did,did,message.buffer,message.length,
  )
}
export function decrypt(
  wallet_handle:number,
  myDid:string,
  did:string,
  encrypted:Buffer,
  nonce:Buffer)  : Promise<void> {
  return call(
    ffi.indy_decrypt,
    build_default_callback,
    wallet_handle,myDid,did,encrypted.buffer,encrypted.length,nonce.buffer,nonce.length,
  )
}

// anoncreds.rs
export function issuer_create_and_store_claim_def(
  wallet_handle:number,
  issuer_did:string,
  schema_json:any,
  signature_type:string,
  create_non_revoc:boolean)  : Promise<void> {
  return call(
    ffi.indy_issuer_create_and_store_claim_def,
    build_default_callback,
    wallet_handle,issuer_did,this.stringify_for_rust(schema_json),signature_type,create_non_revoc,
  )
}
export function issuer_create_and_store_revoc_reg(
  wallet_handle:number,
  issuer_did:string,
  schema_seq_no:number,
  max_claim_num:number) : Promise<void> {
  return call(
    ffi.indy_issuer_create_and_store_revoc_reg,
    build_default_callback,
    wallet_handle,issuer_did,schema_seq_no,max_claim_num,
  )
}
export function issuer_create_claim(
  wallet_handle:number,
  claim_req_json:number,
  claim_json:number,
  revoc_reg_seq_no:number,
  user_revoc_index:number) : Promise<void> {
  return call(
    ffi.indy_issuer_create_claim,
    build_default_callback,
    wallet_handle,this.stringify_for_rust(claim_req_json),this.stringify_for_rust(claim_json),revoc_reg_seq_no,user_revoc_index,
  )
}
export function issuer_revoke_claim(
  wallet_handle:number,
  revoc_reg_seq_no:number,
  user_revoc_index:number) : Promise<void> {
  return call(
    ffi.indy_issuer_revoke_claim,
    build_default_callback,
    wallet_handle,revoc_reg_seq_no,user_revoc_index,
  )
}
export function prover_store_claim_offer(
  wallet_handle:number,
  claim_offer_json:any) : Promise<void> {
  return call(
    ffi.indy_prover_store_claim_offer,
    build_default_callback,
    wallet_handle,this.stringify_for_rust(claim_offer_json),
  )
}
export function prover_get_claim_offers(
  wallet_handle:number,
  filter_json:any) : Promise<void> {
  return call(
    ffi.indy_prover_get_claim_offers,
    build_default_callback,
    wallet_handle,this.stringify_for_rust(filter_json),
  )
}
export function prover_create_master_secret(
  wallet_handle:number,
  master_secret_name:string) : Promise<void> {
  return call(
    ffi.indy_prover_create_master_secret,
    build_default_callback,
    wallet_handle,master_secret_name,
  )
}
export function prover_create_and_store_claim_req(
  wallet_handle:number,
  prover_did:string,
  claim_offer_json:any,
  claim_def_json:any,
  master_secret_name:string) : Promise<void> {
  return call(
    ffi.indy_prover_create_and_store_claim_req,
    build_default_callback,
    wallet_handle,prover_did,this.stringify_for_rust(claim_offer_json),this.stringify_for_rust(claim_def_json),master_secret_name,
  )
}
export function prover_store_claim(
  wallet_handle:number,
  claims_json:any) : Promise<void> {
  return call(
    ffi.indy_prover_store_claim,
    build_default_callback,
    wallet_handle,this.stringify_for_rust(claims_json),
  )
}
export function prover_get_claims(
  wallet_handle:number,
  filter_json:any) : Promise<void> {
  return call(
    ffi.indy_prover_get_claims,
    build_default_callback,
    wallet_handle,this.stringify_for_rust(filter_json),
  )
}
export function prover_get_claims_for_proof_req(
  wallet_handle:number,
  proof_request_json:any) : Promise<void> {
  return call(
    ffi.indy_prover_get_claims_for_proof_req,
    build_default_callback,
    wallet_handle,this.stringify_for_rust(proof_request_json),
  )
}
export function prover_create_proof(
  wallet_handle:number,
  proof_req_json:any,
  requested_claims_json:any,
  schemas_json:any,
  master_secret_name:string,
  claim_defs_json:any,
  revoc_regs_json:any) : Promise<void> {
  return call(
    ffi.indy_prover_create_proof,
    build_default_callback,
    wallet_handle,this.stringify_for_rust(proof_req_json),this.stringify_for_rust(requested_claims_json),this.stringify_for_rust(schemas_json),master_secret_name,this.stringify_for_rust(claim_defs_json),this.stringify_for_rust(revoc_regs_json),
  )
}
export function verifier_verify_proof(
  proof_request_json:any,
  proof_json:any,
  schemas_json:any,
  claim_defs_jsons:any,
  revoc_regs_json:any) : Promise<void> {
  return call(
    ffi.indy_verifier_verify_proof,
    build_default_callback,
    this.stringify_for_rust(proof_request_json),this.stringify_for_rust(proof_json),this.stringify_for_rust(schemas_json),this.stringify_for_rust(claim_defs_jsons),this.stringify_for_rust(revoc_regs_json),
  )
}

// agent.rs
export function agent_connect(
  pool_handle:number,
  wallet_handle:number,
  sender_did:string,
  receiver_did:string,
  message_cb:() => any) : Promise<number> {

  return new Promise<number>((resolve,reject) => {

    // call through the FFI
    const result = ffi.indy_agent_connect(0,
      pool_handle,wallet_handle,sender_did,receiver_did,
      build_object_handle_callback(resolve,reject),
      build_message_callback(message_cb)
    )
    // these values will be returned by target
    // w/o calling the callback, so we must explicitly check for them
    // and reject the promise
    if(result != ErrorCodes.Success)
      reject(result)

  })
}

export function agent_listen(endpoint:string,connection_cb:() => any,message_cb:() => any) : Promise<number> {

  return new Promise<number>((resolve,reject) => {

    // call through the FFI
    const result = ffi.indy_agent_listen(0,
      endpoint,
      build_object_handle_callback(resolve,reject),
      build_connection_callback(connection_cb),
      build_message_callback(message_cb)
    )
    // these values will be returned by target
    // w/o calling the callback, so we must explicitly check for them
    // and reject the promise
    if(result != ErrorCodes.Success)
      reject(result)

  })
}
export function agent_add_identity(listener_handle:number,pool_handle:number,wallet_handle:number,did:string) : Promise<void> {
  return call(
    ffi.indy_agent_add_identity,
    build_default_callback,
    listener_handle,pool_handle,wallet_handle,did
  )
}

export function agent_remove_identity(listener_handle:number,wallet_handle:number,did:string) : Promise<void> {
  return call(
    ffi.indy_agent_remove_identity,
    build_default_callback,
    listener_handle,wallet_handle,did
  )
}
export function agent_send(connection_handle:number,message:string) : Promise<void> {
  return call(
    ffi.indy_agent_send,
    build_default_callback,
    connection_handle,message
  )
}
export function agent_close_connection(connection_handle:number) : Promise<void> {
  return call(
    ffi.indy_agent_close_connection,
    build_default_callback,
    connection_handle
  )
}
export function agent_close_listener(listener_handle:number) : Promise<void> {
  return call(
    ffi.indy_agent_close_listener,
    build_default_callback,
    listener_handle
  )
}
