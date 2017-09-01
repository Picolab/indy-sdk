import { ErrorCode, IndyError } from '../error'

import {
  JSON_Datum,
  FilesystemPath,
  IP_Port,
  IP_Addr,
  TXN_DEST,
  TXN_IDENTIFIER,
  TXN_ID,
  TXN_Type,
  BridgeEntryPoint,
  open_pool_ledger_options,
  rust_pool_handle
} from '../bridge/api';

export type DID = string

export interface ServiceProviderInterfaceConfig {
  loadGensisConfigTypes?:boolean,
}

export interface LedgerGenesisTransaction {

  readonly alias : string
  readonly client_ip : IP_Addr
  readonly client_port: IP_Port
  readonly node_ip:IP_Addr
  readonly node_port: IP_Port
  readonly services:string[]
  readonly dest:TXN_DEST
  readonly identifier:TXN_IDENTIFIER
  readonly txnId:TXN_ID
  readonly type:TXN_Type

  as_wrapped_json_string():string
}

export interface LedgerGenesisConfiguration {
  name:string,
  ///     "genesis_txn": string (optional), A path to genesis transaction file. If NULL, then a default one will be used.
  ///                    If file doesn't exists default one will be created.  refreshOnOpen?:boolean
  genesis_txn?:LedgerGenesisTransaction[] | FilesystemPath
}


/*
///     "refreshOnOpen": bool (optional), Forces pool ledger to be refreshed immediately after opening.
///                      Defaults to true.
///     "autoRefreshTime": int (optional), After this time in minutes pool ledger will be automatically refreshed.
///                        Use 0 to disable automatic refresh. Defaults to 24*60.
///     "networkTimeout": int (optional), Network timeout for communication with nodes in milliseconds.
///                       Defaults to 20000.  refreshOnOpen?:boolean
refreshOnOpen?:boolean
autoRefreshTime?:number
networkTimeout?:number
*/
export type LedgerLocalRuntimeConfiguration = open_pool_ledger_options


// with an eye towards redux
export const POOL_CREATION_EVENT = 'POOL_CREATION_EVENT'
export const POOL_DELETION_EVENT = 'POOL_DELETION_EVENT'
export const POOL_ERROR_EVENT = 'POOL_ERROR_EVENT'


export interface Pool {
  readonly name:string
  readonly genesis_config:LedgerGenesisConfiguration
  readonly open_config:LedgerLocalRuntimeConfiguration
  readonly path:FilesystemPath
  readonly ledger:Ledger

  readonly isReady:boolean
  readonly isDefault:boolean
  readonly isOpen:boolean
  readonly hadTemporaryGenesisFile:boolean

  // this will delete the Pool configuration, and
  // QUESTION - does this actually blow away any storage?
  // QUESTION - should we close open ledgers and wallets?
  // QUESTION - notifications?  Event Listener
  delete() : Promise<void>

  // get all the genesis transactions, as objects, for this pool
  // TODO - put the async iterator / iterator support back
  // genesisTransactions() : Promise<LedgerGenesisTransaction>

  // what does it mean to "Refresh" a pool?
  /// Refreshes a local copy of a pool ledger and updates pool nodes connections.
  refresh() : Promise<void>

  // obtain access to this pool via the Ledger object
  open(config?:LedgerLocalRuntimeConfiguration) : Promise<Ledger>

  // close this
  close() : Promise<void>

}



export interface Ledger {
  readonly pool : Pool

  /// Closes opened pool ledger, opened nodes connections and frees allocated resources.
  close() : Promise<void>

  /// Closes opened pool ledger, opened nodes connections and frees allocated resources.
  refresh() : Promise<void>

  // close and re-open Ledger with new run-time open options to open_pool-Ledger
  updateConfig(new_config?:open_pool_ledger_options) : Promise<void>

  sign_and_submit_request(wallet:Wallet,submitter:DID,request:JSON_Datum) : Promise<void>

  submit_request(request:JSON_Datum) : Promise<void>

  sign_request(wallet:Wallet,submitter:DID,request:JSON_Datum) : Promise<void>

  builder_for(submitter:DID) : LedgerBuilder

  /// Creates a new secure wallet with the given unique name.
  ///
  /// #Params
  /// pool_name: Name of the pool that corresponds to this wallet.
  /// name: Name of the wallet.
  /// xtype(optional): Type of the wallet. Defaults to 'default'.
  ///                  Custom types can be registered with indy_register_wallet_type call.
  /// config(optional): Wallet configuration json. List of supported keys are defined by wallet type.
  ///                    if NULL, then default config will be used.
  /// credentials(optional): Wallet credentials json. List of supported keys are defined by wallet type.
  ///                    if NULL, then default config will be used.
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  create_wallet(config? : {
    wallet_name:string
    wallet_type_name?:string
    wallet_type_config?:any,
    wallet_type_credentials?:any
  }) : Promise<Wallet>



}

export interface Target {
  readonly builder:LedgerBuilder
  readonly target:DID

  node_request( data:string ) : Promise<void>
  get_ddo_request() : Promise<void>

  nym_request(verkey:string, alias:string, role:string ) : Promise<void>
  get_nym_request( ) : Promise<void>

  attrib_request(hash:string, raw:string,  enc:string ) : Promise<void>
  get_attrib_request(data:string ) : Promise<void>

}

export interface LedgerBuilder {

  readonly submitter:DID
  readonly ledger:Ledger

  target(target:DID) : Target
  schema_request(data:string ) : Promise<void>
  get_schema_request(dest:string, data:string ) : Promise<void>
  claim_def_txn( xref:number,  signature_type:string,  data:string ) : Promise<void>
  get_claim_def_txn( xref:number,  signature_type:string,  origin:string ) : Promise<void>
  get_txn_request(data:number ) : Promise<void>

}


export interface WalletTypeConfig {
}
export interface WalletCredentials {
}


export interface WalletType {
  readonly name:string

  create(config:WalletTypeConfig,credentials:WalletCredentials) : Promise<void>
/*
open: Option<extern fn(name: *const c_char,
                       config: *const c_char,
                       runtime_config: *const c_char,
                       credentials: *const c_char,
                       handle: *mut i32) -> ErrorCode>,
set: Option<extern fn(handle: i32,
                      key: *const c_char,
                      value: *const c_char) -> ErrorCode>,
get: Option<extern fn(handle: i32,
                      key: *const c_char,
                      value_ptr: *mut *const c_char) -> ErrorCode>,
get_not_expired: Option<extern fn(handle: i32,
                                  key: *const c_char,
                                  value_ptr: *mut *const c_char) -> ErrorCode>,
list: Option<extern fn(handle: i32,
                       key_prefix: *const c_char,
                       values_json_ptr: *mut *const c_char) -> ErrorCode>,
close: Option<extern fn(handle: i32) -> ErrorCode>,
delete: Option<extern fn(name: *const c_char,
                         config: *const c_char,
                         credentials: *const c_char) -> ErrorCode>,
free: Option<extern fn(wallet_handle: i32,
                       value: *const c_char) -> ErrorCode>,
cb: Option<extern fn(xcommand_handle: i32,
                     err: ErrorCode)>) -> ErrorCode {
                     */
}


export interface WalletRuntimeConfig {
  /// {
  ///     "freshnessTime": string (optional), Amount of minutes to consider wallet value as fresh. Defaults to 24*60.
  ///     ... List of additional supported keys are defined by wallet type.
  /// }
  freshnessTime?:string
}


export interface Verifier {
  verify_proof(proof_request_json:string,proof_json:string,schemas_json:string,claim_defs_jsons:string,revoc_regs_json:string);
}

export interface Issuer {
  create_and_store_claim_def(issuer:DID,schema_json:string,signature_type:string,create_non_revoc:boolean);
  create_and_store_revoc_reg(issuer:DID,schema_seq_no:number,max_claim_num:number);
  create_claim(claim_req_json:string,claim_json:string,revoc_reg_seq_no:number,user_revoc_index:number);
  revoke_claim(revoc_reg_seq_no:number,user_revoc_index:number);
}

export interface Prover {
  store_claim_offer(claim_offer_json:string);
  get_claim_offers(filter_json:string);
  create_master_secret(master_secret_name:string);
  create_and_store_claim_req(prover:DID,claim_offer_json:string,claim_def_json:string,master_secret_name:string);
  store_claim(claims_json:string);
  get_claims(filter_json:string);
  get_claims_for_proof_req(proof_request_json:string);
  create_proof(proof_req_json:string,requested_claims_json:string,schemas_json:string,master_secret_name:string,claim_defs_json:string,revoc_regs_json:string);
}

// signus.rs
export interface Signus {
  create_and_store_my_did(did_json:string);
  replace_keys(a_did:DID,identity_json:string);
  store_their_did(identity_json:string);
  sign(a_did:DID,message_raw:Buffer);
  verify_signature(pool_ledger:Ledger, a_did:DID,  message_raw:Buffer, signature_raw:Buffer);
  encrypt(pool_ledger:Ledger, me:DID, a_did:DID, message_raw:Buffer);
  decrypt(me:DID, a_did:DID,encrypted_msg_raw:Buffer, nonce_raw:Buffer);
}

export interface A_DID_Utils {
  readonly a_did:DID

  replace_keys(identity_json:string);
  sign(message_raw:Buffer);
  verify_signature(pool_ledger:Ledger, message_raw:Buffer, signature_raw:Buffer);

  and_me(me:DID) : A_DID_and_Me
}

export interface A_DID_and_Me {
  readonly a_did:DID
  readonly me:DID
  encrypt(pool_ledger:Ledger, message_raw:Buffer);
  decrypt(encrypted_msg_raw:Buffer, nonce_raw:Buffer);
}


export interface Wallet extends Issuer, Verifier, Prover, Signus {
  /// Creates a new secure wallet with the given unique name.
  ///
  /// #Params
  /// pool_name: Name of the pool that corresponds to this wallet.
  /// name: Name of the wallet.
  /// xtype(optional): Type of the wallet. Defaults to 'default'.
  ///                  Custom types can be registered with indy_register_wallet_type call.
  /// config(optional): Wallet configuration json. List of supported keys are defined by wallet type.
  ///                    if NULL, then default config will be used.
  /// credentials(optional): Wallet credentials json. List of supported keys are defined by wallet type.
  ///                    if NULL, then default config will be used.
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  constructor(
    pool_ledger:Ledger,
    config? : {
    wallet_name:string
    wallet_type_name?:string
    wallet_type_config?:any,
    wallet_type_credentials?:any
  })


  /// Opens the wallet with specific name.
  ///
  /// Wallet with corresponded name must be previously created with indy_create_wallet method.
  /// It is impossible to open wallet with the same name more than once.
  ///
  /// #Params
  /// name: Name of the wallet.
  /// runtime_config (optional): Runtime wallet configuration json. if NULL, then default runtime_config will be used. Example:
  /// {
  ///     "freshnessTime": string (optional), Amount of minutes to consider wallet value as fresh. Defaults to 24*60.
  ///     ... List of additional supported keys are defined by wallet type.
  /// }
  /// credentials(optional): Wallet credentials json. List of supported keys are defined by wallet type.
  ///                    if NULL, then default credentials will be used.
  ///
  /// #Returns
  /// Handle to opened wallet to use in methods that require wallet access.
  ///
  /// #Errors - IndyError exception thrown with ErrorCode set in case of error
  /// Common*
  /// Wallet*
  open(config? : {
    wallet_name:string
    runtime_config?:WalletRuntimeConfig
  }) : Promise<void>

  /// Closes opened wallet and frees allocated resources.
  ///
  /// #Params
  /// handle: wallet handle returned by indy_open_wallet.
  ///
  /// #Returns
  /// void
  ///
  /// #Errors - IndyError exception thrown with ErrorCode set in case of error
  /// Common*
  /// Wallet*
  close() : Promise<void>

}

export type AddIdentityCallback = (err:ErrorCode) => void
export type RemoveIdentityCallback = (err:ErrorCode) => void

export interface AgentListener {
  add_identity( wal:WalletAndLedger, a_did:DID, add_identity_cb:AddIdentityCallback);
  remove_identity( wallet:Wallet, a_did:DID, rm_identity_cb:RemoveIdentityCallback);
  close() : Promise<void>
}

export interface AgentConnection {
  send(message:string) : Promise<void>
  close() : Promise<void>
}

export type ConnectionCallback = (err:ErrorCode,connection:AgentConnection) => void
export type ListenerCallback = (err:ErrorCode,listener:AgentListener) => void
export type MessageCallback = (err:ErrorCode,message:Buffer) => void
export class WalletAndLedger {
  readonly wallet:Wallet
  readonly ledger:Ledger
  constructor(wallet:Wallet,ledger:Ledger) {
    this.wallet = wallet
    this.ledger = ledger
  }
}

export interface Agent {
  connect(wal:WalletAndLedger,
    sender:DID,
    receiver:DID,
    connection_cb:ConnectionCallback,
    message_cb:MessageCallback
  ) : Promise<AgentConnection>
  listen(endpoint:string,
    listener_cb:ListenerCallback,
    connection_cb:ConnectionCallback,
    message_cb:MessageCallback
  ) : Promise<AgentListener>
}



export interface ServiceProviderInterface {


  // genesis configuration management.
  deleteLedgerGenesisConfiguration(configuration_name:string) : Promise<void>
  registerLedgerGenesisConfiguration (config?:LedgerGenesisConfiguration) : Promise<void>
  getLedgerGenesisConfiguration(configuration_name:string) : Promise<void>
  registeredLedgerGenesisConfigurations() : Promise<LedgerGenesisConfiguration>

  /// Opens pool ledger and performs connecting to pool nodes.
  ///
  /// Pool ledger configuration with corresponded name must be previously created
  /// with indy_create_pool_ledger_config method.
  /// It is impossible to open pool with the same name more than once.
  ///
  /// config : Runtime pool configuration json.
  ///                         if NULL, then default config will be used. Example:
  /// {
  ///     "configurationName": string
  ///
  ///     "refreshOnOpen": bool (optional), Forces pool ledger to be refreshed immediately after opening.
  ///                      Defaults to true.
  ///     "autoRefreshTime": int (optional), After this time in minutes pool ledger will be automatically refreshed.
  ///                        Use 0 to disable automatic refresh. Defaults to 24*60.
  ///     "networkTimeout": int (optional), Network timeout for communication with nodes in milliseconds.
  ///                       Defaults to 20000.
  /// }
  ///
  /// #Errors
  /// Common*
  /// Ledger*
  createLedger (config:LedgerLocalRuntimeConfiguration) : Promise<Ledger>

  /// creates a new pool configuration, and a ledger with the same name
  newLedger (
    ledger_name:string,
    genesis_config:LedgerGenesisConfiguration,
    runtime_config:LedgerLocalRuntimeConfiguration,
  ) : Promise<Ledger>


  // --------------------------------------------------------------------

  // or is this a better API for the above?
  createPool(config:LedgerGenesisConfiguration) : Promise<Pool>
  pool(configuration_name:string) : Promise<Pool | undefined>
  pools() : Promise<Pool>

  // or is this a better API for the above?
  registerWalletType(walletDriver:WalletType) : Promise<void>
  walletType(wallet_type_name:string): Promise<WalletType | undefined>
  walletTypes() : Promise<WalletType>

  // create a wallet
  // note - the name is global to
  createWallet(nodeGlobalName:string,pool:Pool | Ledger,walletType?:WalletType,config?:WalletTypeConfig,credentials?:WalletCredentials) : Promise<Wallet>
  wallets() : Promise<Wallet>
}
