import { ErrorCode, IndyError } from '../error'
import {
  LibIndy
} from '..'
import {
  DID,
  A_DID_Utils,
  A_DID_and_Me,
  LedgerGenesisConfiguration,
  Target,
  Pool,
  Ledger,
  SubmitterTools,
  Wallet,
  WalletType,
  WalletTypeConfig,
  WalletCredentials,
  ServiceProviderInterface,
  ServiceProviderInterfaceConfig
} from './api'
import {
  C_Target,
  C_SubmitterTools,
  C_A_DID_and_Me,
  C_A_DID_Utils
} from './util'
import {
  C_Ledger
} from './ledger'
import * as tmp from 'tmp'
import * as fs from 'fs-extra'

export class ServiceImplementation implements ServiceProviderInterface {
  private pool_ledger_genesis_configuration:any = {}
  private readonly libindy:LibIndy

  constructor(libindy:LibIndy,config:ServiceProviderInterfaceConfig) {

    this.libindy = libindy

    function _initialize_pool_ledger_genesis_configurations() {
      // TODO - iterate over basepath/pool/<name> and load configurations
      console.log("Ledger genesis configurations registered")
    }

    if(config.loadGensisConfigTypes)
      _initialize_pool_ledger_genesis_configurations()

  }



  // registeredGenesisConfigurations

  async deleteLedgerGenesisConfiguration(configuration_name:string) : Promise<void> {
    const config_check = this.pool_ledger_genesis_configuration[configuration_name]
    if(config_check === undefined) {
      throw "Pool Ledger "+configuration_name+" Is Not Defined"
    }
    await this.libindy.bridge.delete_pool_ledger_config(configuration_name)
    this.pool_ledger_genesis_configuration[configuration_name] = undefined
  }

  async registerLedgerGenesisConfiguration (config?:LedgerGenesisConfiguration) : Promise<void> {
    throw 'nyi'
/*
    // this establishes a minimal configuration
    config = config || {
      name:'default'
    }

    const config_check = this.pool_ledger_genesis_configuration[config.name]
    if(config_check === undefined) {
      const tempfile = tmp.fileSync();
      const path = tempfile.name

      for(const line of config.genesis_txn) {
        fs.appendFileSync(path,line.as_wrapped_json_string())
        fs.appendFileSync(path,"\n")
      }
      await this.libindy.async.create_pool_ledger_config(config.name,{
        genesis_txn:path
      })
      const new_genesis_configuration = {
        name:configuration_name,
        genesis_txn : config.genesis_txn
      }
      this.pool_ledger_genesis_configuration[config.name] = config
    }
*/

  }





  getLedgerGenesisConfiguration(configuration_name:string) : Promise<void> {
    throw 'nyi'
  }
  registeredLedgerGenesisConfigurations() : Promise<LedgerGenesisConfiguration> {
    throw 'nyi'
  }






    // or is this a better API for the above?
    createPool(config:LedgerGenesisConfiguration) : Promise<Pool> {
      throw 'nyi'

    }

    pool(configuration_name:string) : Promise<Pool | undefined> {
      throw 'nyi'

    }
    pools() : Promise<Pool> {
      throw 'nyi'

    }

    // or is this a better API for the above?
    registerWalletType(walletDriver:WalletType) : Promise<void> {
      throw 'nyi'

    }
    walletType(wallet_type_name:string): Promise<WalletType | undefined> {
      throw 'nyi'

    }
    walletTypes() : Promise<WalletType> {
      throw 'nyi'

    }

    // create a wallet
    // note - the name is global to
    createWallet(nodeGlobalName:string,pool:Pool | Ledger,walletType?:WalletType,config?:WalletTypeConfig,credentials?:WalletCredentials) : Promise<Wallet> {
      throw 'nyi'
    }
    wallets() : Promise<Wallet> {
      throw 'nyi'

    }
}
