// QUESTION - this dependency seems out of place in this file, but is
// required if we want to share a module wide logging config via libindy.
// still - it seems like this can be factored out.
import * as winston from 'winston'

// give the entire module a common namespace - this just flattens the structure
// of the inside library.  Note that we are not exporting the information from
// the subcomponents - but only from the APIs.
//
// This includes all 'helper types' as well as the access APIs listed below.
export * from './error'
export * from './ffi/api'
export * from './bridge/api'
export * from './spi/api'

// import access APIs
import { FFIEntryPoint } from './ffi/api'
import { BridgeEntryPoint } from './bridge/api'
import { ServiceProviderInterface } from './spi/api'

// this is libindy bridge itself.  Any attempt to instantiate an instance of
// LibIndy that can not resolve and bind the FFI should fail.  All other
// properties are completely.
//
// QUESTION - is it valuable to make these bridge?, async?, spi? triggered
// by the configuration handed to the LibIndy runtime factory?
export interface LibIndy {
  readonly logger: winston.Logger
  readonly ffi : FFIEntryPoint
  readonly bridge : BridgeEntryPoint
  readonly spi : ServiceProviderInterface
}

// export LibIndyRuntime so folks can get started with just the top level
// import - import { LibIndy,LibIndyRuntime } from 'indy-sdk'
export * from './runtime'

// support no-config, default only, automatic use via require for
// old style javascript
import { LibIndyRuntime } from './runtime'
export default function() : BridgeEntryPoint {
  return new LibIndyRuntime().bridge
}
