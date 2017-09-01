import { ErrorCode, IndyError } from '../error'
import {
  LibIndy
} from '..'
import {
  DID,
  A_DID_Utils,
  A_DID_and_Me,
  LedgerGenesisConfiguration,
  LedgerLocalRuntimeConfiguration,
  Target,
  Pool,
  Ledger,
  LedgerBuilder,
  Wallet,
  WalletType,
  WalletTypeConfig,
  WalletCredentials,
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

  async createLedger (runtime_config:LedgerLocalRuntimeConfiguration) : Promise<Ledger> {
    //return Promise.resolve(new C_Ledger(this,runtime_config))
    throw 'nyi'
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


  async newLedger (
    ledger_name:string,
    genesis_config:LedgerGenesisConfiguration,
    runtime_config:LedgerLocalRuntimeConfiguration
  ) : Promise<Ledger> {
    throw 'nyi'
    /*
    const gc_name = genesis_config.name || ledger_name
    const rc_name = runtime_config.configurationName || ledger_name


    if(( rc_name != gc_name ) |= (rc_name != ledger_name) || (gc_name != ledger_name)) {
      throw new Error("ledger_name,genesis_config.name,and runtime_config.configurationName must all be the same")
    }

    await this.registerLedgerGenesisConfiguration({
      name:ledger_name,
      genesis_txn:genesis_config.genesis_txn
    })

    return await this.createLedger (runtime_config)
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
