import { ErrorCode, IndyError } from '../error'
import {
  JSON_Datum,
  FilesystemPath
} from '../bridge'
import {
  DID,
  A_DID_Utils,
  A_DID_and_Me,
  LedgerGenesisConfigName,
  LedgerGenesisConfiguration,
  LedgerLocalRuntimeConfiguration,
  Ledger,
  LedgerBuilder,
  Wallet
} from '../spi'
import {
  C_LedgerBuilder
} from './util'

/*

export function open_pool_ledger(configuration_name:string,config_data_string:open_pool_ledger_options) : Promise<void> {
  return new Promise<void>((resolve,reject) => {
    RustLibrary.indy_open_pool_ledger(command_handle,
      configuration_name,config_data_string,
      open_pool_callback(resolve,reject))
  })
}

export function refresh_pool_ledger(pool_handle:number) : Promise<void> {
  return new Promise<void>((resolve,reject) => {
    RustLibrary.indy_refresh_pool_ledger(command_handle,
      pool_handle,
      default_callback(resolve,reject))
  })
}

export function close_pool_ledger(pool_handle:number) : Promise<void> {
  return new Promise<void>((resolve,reject) => {
    RustLibrary.indy_close_pool_ledger(command_handle,
      pool_handle,
      default_callback(resolve,reject))
  })
}
*/

export class C_Ledger implements Ledger {

  private closed: boolean
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
  constructor(runtime_config:LedgerLocalRuntimeConfiguration) {
    this.closed = false

  }

  /// Refreshes a local copy of a pool ledger and updates pool nodes connections.
  ///
  /// #Params
  /// handle: pool handle returned by indy_open_pool_ledger
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Ledger*
  async refresh() : Promise<void> {
  }

  /// Closes opened pool ledger, opened nodes connections and frees allocated resources.
  ///
  /// #Params
  /// handle: pool handle returned by indy_open_pool_ledger.
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Ledger*
  async close() : Promise<void> {
  }

  async sign_and_submit_request(wallet:Wallet,submitter:DID,request:JSON_Datum) {
  }

  async submit_request(request:JSON_Datum) : Promise<void> {
  }

  async sign_request(wallet:Wallet,submitter:DID,request:JSON_Datum) : Promise<void> {
  }

  builder_for(submitter:DID) : LedgerBuilder {
    return new C_LedgerBuilder(this,submitter)
  }

  create_wallet(config? : {
    wallet_name:string
    wallet_type_name?:string
    wallet_type_config?:any,
    wallet_type_credentials?:any
  }) : Promise<Wallet> {
    throw 'nyi'
  }


}
