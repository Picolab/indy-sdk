import { ErrorCode, IndyError } from '../error'
import {
  LibIndy
} from '..'
import {
  DID,
  A_DID_Utils,
  A_DID_and_Me,
  LedgerGenesisConfigName,
  LedgerGenesisConfiguration,
  LedgerLocalRuntimeConfiguration,
  Target,
  Ledger,
  LedgerBuilder,
  Wallet,
  ServiceProviderInterface,
  ServiceProviderInterfaceConfig
} from './api'
import {
  C_Target,
  C_LedgerBuilder,
  C_A_DID_and_Me,
  C_A_DID_Utils
} from './util'
import {
  C_Ledger
} from './ledger'
import * as tmp from 'tmp'
import * as fs from 'fs-extra'
import * as winston from 'winston'

export class ServiceImplementation implements ServiceProviderInterface {
  private pool_ledger_genesis_configuration:any = {}
  readonly libindy:LibIndy
  readonly logger : winston.Logger

  constructor(libindy:LibIndy,config:ServiceProviderInterfaceConfig) {

    this.libindy = libindy
    this.logger = libindy.logger

    function _initialize_pool_ledger_genesis_configurations() {
      // TODO - iterate over basepath/pool/<name> and load configurations
      console.log("Ledger genesis configurations registered")
    }

    if(config.loadGensisConfigTypes)
      _initialize_pool_ledger_genesis_configurations()

  }

  async createLedger (runtime_config:LedgerLocalRuntimeConfiguration) : Promise<Ledger> {
    return new C_Ledger(runtime_config)
  }


  // registeredGenesisConfigurations

  async deleteLedgerGenesisConfiguration(configuration_name:string) : Promise<void> {
    const config_check = this.pool_ledger_genesis_configuration[configuration_name]
    if(config_check === undefined) {
      throw "Pool Ledger "+configuration_name+" Is Not Defined"
    }
    await this.libindy.async.delete_pool_ledger_config(configuration_name)
    this.pool_ledger_genesis_configuration[configuration_name] = undefined
  }

  async registerLedgerGenesisConfiguration (config:LedgerGenesisConfiguration) : Promise<void> {
    const configuration_name = config.name

    const config_check = this.pool_ledger_genesis_configuration[configuration_name]
    if(config_check === undefined) {
      const tempfile = tmp.fileSync();
      const path = tempfile.name

      for(const line of config.genesis_txn) {
        fs.appendFileSync(path,line.as_wrapped_json_string())
        fs.appendFileSync(path,"\n")
      }
      await this.libindy.async.create_pool_ledger_config(configuration_name,{
        genesis_txn:path
      })
      const new_genesis_configuration = {
        name:configuration_name,
        genesis_txn : config.genesis_txn
      }
      this.pool_ledger_genesis_configuration[configuration_name] = new_genesis_configuration
    }

  }


  async newLedger (
    genesis_config:LedgerGenesisConfiguration,
    runtime_config:LedgerLocalRuntimeConfiguration
  ) : Promise<Ledger> {

    await this.registerLedgerGenesisConfiguration({
      name:genesis_config.name,
      genesis_txn:genesis_config.genesis_txn
    })

    return await this.createLedger (runtime_config)

  }

}
