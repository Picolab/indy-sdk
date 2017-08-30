import {
  rust_pool_handle,
  open_pool_ledger_options,
  FilesystemPath
} from '../bridge/api'
import {
  Pool,
  Ledger,
  LedgerGenesisConfiguration,
  LedgerLocalRuntimeConfiguration,
  ServiceProviderInterface,
  LedgerGenesisTransaction
} from './api'
import {
  LibIndy
} from '..'

export class C_Pool implements Pool {
  private pool_handle:rust_pool_handle
  readonly name:string
  readonly genesis_config:LedgerGenesisConfiguration
  readonly path:FilesystemPath

  private _open_config:LedgerLocalRuntimeConfiguration
  get open_config():LedgerLocalRuntimeConfiguration {
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
  get isDefault() : boolean {
    return this.genesis_config === undefined
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
  open(config?:LedgerLocalRuntimeConfiguration) : Promise<Ledger> {
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
    return this.libindy.async.refresh_pool_ledger(this.pool_handle)
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
    return this.libindy.async.close_pool_ledger(this.pool_handle)
  }

}
