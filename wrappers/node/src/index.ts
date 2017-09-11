export * from './error'

// import access APIs
import { FFIEntryPoint,FFIConfiguration,FFIInterfaceConfig } from './rustlib'
export { FFIEntryPoint,FFIConfiguration,FFIInterfaceConfig } from './rustlib'


import { BridgeEntryPoint,BridgeInterfaceConfig,libindy_middleware } from './bridge'
export * from './bridge/api'


import { ServiceProviderInterface,ServiceProviderInterfaceConfig,ServiceImplementation } from './spi'
export * from './spi/api'

// this is libindy bridge itself.  Any attempt to instantiate an instance of
// LibIndy that can not resolve and bind the FFI should fail.  All other
// properties are completely.
//
// QUESTION - is it valuable to make these bridge?, async?, spi? triggered
// by the configuration handed to the LibIndy runtime factory?
export interface LibIndy {
  readonly ffi : FFIEntryPoint
  readonly bridge : BridgeEntryPoint
  readonly spi : ServiceProviderInterface
}

// export LibIndyRuntime so folks can get started with just the top level
// import - import { LibIndy,LibIndyRuntime } from 'indy-sdk'

export interface LibIndyRuntimeConfig {
  basepath?:string
  reset?:boolean
  ffi?:FFIInterfaceConfig
  bridge?:BridgeInterfaceConfig
  spi?:ServiceProviderInterfaceConfig
}


import * as fs from 'fs-extra'
import * as ffi from 'ffi'
export class LibIndyRuntime implements LibIndy {

  readonly basepath : string
  readonly pooldir : string
  readonly ffi : FFIEntryPoint
  readonly bridge : BridgeEntryPoint
  readonly spi : ServiceProviderInterface

  use(middleware:libindy_middleware): void {
    this.bridge.use(middleware)
  }

  constructor(config?:LibIndyRuntimeConfig) {

    // allow optional, empty config
    config = config || {}

    function _initialize_basepath() : string {
      // this needs additional logic
      let basepath = config.basepath

      if(basepath === undefined) {
        basepath = process.env.HOME + "/.indy"
      }

      return basepath
    }

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

    this.spi = new ServiceImplementation(this,config.spi || {})
  }



}
// support no-config, default only, automatic use via require for
// old style javascript
export default function() : BridgeEntryPoint {
  return new LibIndyRuntime().bridge
}
