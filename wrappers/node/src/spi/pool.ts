import {
  rust_pool_handle,
  open_pool_ledger_options,
  FilesystemPath
} from '../bridge/api'
import {
  Pool,
  PoolState,
  Ledger,
  LedgerGenesisConfiguration,
  LedgerRuntimeConfiguration,
  ServiceProviderInterface,
  LedgerGenesisTransaction,
  IP_Port,
  IP_Addr,
  TXN_DEST,
  TXN_IDENTIFIER,
  TXN_ID,
  TXN_Type

} from './api'
import {
  LibIndy
} from '..'

export class SimpleLedgerGenesisTransaction implements LedgerGenesisTransaction {

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

  as_wrapped_json_string() : string {
    return JSON.stringify({ data:this })
  }

  constructor(template:any) {
    Object.assign(this,template)
  }
}

export class SimpleLedgerGenesisConfiguration implements LedgerGenesisConfiguration {
  private _name:string
  private _transactions?:LedgerGenesisTransaction[]
  private _txn_file_path?:FilesystemPath

  get name():string {
    return this._name
  }
  get transactions():LedgerGenesisTransaction[] | undefined {
    return this._transactions
  }
  get txn_file_path():FilesystemPath | undefined {
    return this._txn_file_path
  }

  static createFromFile(name:string,path:FilesystemPath) : LedgerGenesisConfiguration {
    throw "Implement reading pseudo-JSON of txn record from file"
  }

  constructor(values?:any) {
    if(values) {
      this._name = values.name
      this._transactions = values.transactions
      this._txn_file_path = values.txn_file_path
    }
  }

  static createFromTransactions(name:string,txns:LedgerGenesisTransaction[]) : LedgerGenesisConfiguration {
    return new SimpleLedgerGenesisConfiguration({
      name:name,
      transactions:txns,
      txn_file_path:undefined
    })
  }

}

export class SimplePoolState implements PoolState {
  readonly config : LedgerGenesisConfiguration
  private _ledger?:Ledger
  get ledger() : Ledger | undefined {
    if(this._ledger)
      return this._ledger
    return undefined
  }
  get isReady():boolean {
    return false;
  }
  get isDefault():boolean {
    return false;
  }
  get isOpen():boolean {
    return false;
  }
  get hadTemporaryGenesisFile():boolean {
    return false;
  }

  constructor(config:LedgerGenesisConfiguration) {
    this.config = config
    this._ledger = undefined
  }

}

export class C_Pool implements Pool {
  private pool_handle:rust_pool_handle
  readonly state:PoolState
  get name() : string {
    return this.state.config.name
  }

  private _open_config:LedgerRuntimeConfiguration
  get open_config():LedgerRuntimeConfiguration {
    return this._open_config
  }

  private readonly libindy:LibIndy

  constructor(libindy:LibIndy,config:LedgerGenesisConfiguration) {
    this.libindy = libindy
    throw 'nyi'
  }

  get ledger() : Ledger {
    return this.ledger
  }

  get handle() : rust_pool_handle {
    return this.pool_handle
  }

  get isReady() : boolean {
    return this.pool_handle !== undefined
  }
  // this is only the default configuration if we passed in no transactions
  // or paths to transactions, and are relying on the libindy default
  get isDefault() : boolean {
    return this.state.config.transactions === undefined
  }
  get isOpen() : boolean {
    return this.open_config !== undefined
  }
  get hadTemporaryGenesisFile() : boolean {
    throw 'nyi'
  }


  delete() : Promise<void> {
    if(!this.isReady) {
      return Promise.reject(new Error("Attempt to delete already deleted pool"))
    }
    this.pool_handle = undefined
  }

  // obtain access to this pool via the Ledger object
  open(config?:LedgerRuntimeConfiguration) : Promise<Ledger> {
    throw 'nyi'
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
    return this.libindy.bridge.refresh_pool_ledger(this.pool_handle)
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
    return this.libindy.bridge.close_pool_ledger(this.pool_handle)
  }

}
