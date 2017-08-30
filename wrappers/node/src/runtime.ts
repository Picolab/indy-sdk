import { ErrorCode, IndyError } from './error'
import {
  JSON_Datum,
  FilesystemPath,
  BridgeEntryPoint,
  BridgeInterfaceConfig,
  AsyncBridgeEntryPoint,
  libindy_middleware
} from './bridge'
import {
  ServiceProviderInterface,
  ServiceProviderInterfaceConfig
} from './spi'
import {
  ServiceImplementation
} from './spi/service'
import {
  FFIConfiguration,
  FFIEntryPoint,
  FFIInterfaceConfig
} from './ffi/api'
import { LibIndy } from '.'

import * as tmp from 'tmp'
import * as fs from 'fs-extra'
import * as ffi from 'ffi'
import * as winston from 'winston'


export interface LibIndyRuntimeConfig {
  basepath?:string
  reset?:boolean
  winston?:any
  ffi?:FFIInterfaceConfig
  bridge?:BridgeInterfaceConfig
  spi?:ServiceProviderInterfaceConfig
}


export class LibIndyRuntime implements LibIndy {

  readonly basepath : string
  readonly pooldir : string
  readonly ffi : FFIEntryPoint
  readonly bridge : BridgeEntryPoint
  readonly async : AsyncBridgeEntryPoint
  readonly spi : ServiceProviderInterface
  readonly logger : winston.Logger

  use(middleware:libindy_middleware): void {
    this.bridge.use(middleware)
  }

  constructor(config:LibIndyRuntimeConfig) {

    function _initialize_basepath() : string {
      // this needs additional logic
      let basepath = config.basepath

      if(basepath === undefined) {
        basepath = process.env.HOME + "/.indy"
      }

      return basepath
    }

    const winston_config = config.winston || {}
    this.logger = new winston.Logger(config)

    this.basepath = _initialize_basepath()
    if(config.reset)
      fs.removeSync(this.basepath)

    // initialize FFI
    const ffi_config = config.ffi || {}
    const libraryPath = ffi_config.libraryPath || (process.env.LIBINDY_PATH || 'libindy')
    this.ffi = ffi.Library(libraryPath, FFIConfiguration)

    // initialize bridge
    const bridge_config = config.bridge || {
      increment_command_handle:false,
      validate_serialized_json_string_parameters:false
    }
    this.bridge = new BridgeEntryPoint(this.ffi,bridge_config)
    this.async = new AsyncBridgeEntryPoint(this.bridge)


    this.spi = new ServiceImplementation(this,config.spi || {})
  }

}
