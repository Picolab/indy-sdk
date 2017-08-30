
# Indy SDK for Node.js

This is a Node.js wrapper of the  [Indy](https://www.hyperledger.org/projects/indy) Rust library.

* [Getting Started](#Getting Started).
* [Runtime configuration options](#Runtime Configuration Options).
* [Architecture and Design](#Architecture and Design)
	- Design Considerations
	- Layered Architecture
	- Use Example
* [Technical Details](#Implementation Details)
	- Language Issues
	- Foreign Function Interface
	- Bridge (Promise & Async)
		* [Configuration Wrappers and JSON Strings](#Configuration Wrappers and JSON Strings)
		* [Middleware](#Middleware)
	- Service Provider Interface
* [Test Environment](#Test Environment)
* [Notes and Issues](#Notes and Issues)

The library was designed in appreciation of [The Guidelines](https://docs.google.com/document/d/15P6JOEKxbNC892DWReBStJIXrObVoaBDxbKJFOpAdjI).


Example Typescript Use:
```ts
import { LibIndy,LibIndyRuntime } from 'indy-sdk'

const libindy : LibIndy = new LibIndyRuntime({...})

// libindy.ffi.<any-rustlib-function>(...)

// libindy.bridge.<any-rustlib-fucntion>(...)
// .then(...)
// .catch(...)

//
// await libindy.async.<any-rustlib-function>(...)

// Object Model for other node.js Services - Service Provider Interface
// const ledger : Ledger = libindy.newLedger({...})
```

Example Javascript Use:
```javascript
var LibIndy = require('indy-sdk')

var libindy  = new LibIndy.LibIndyRuntime({...})

// libindy.ffi.<any-rustlib-function>(...)

// libindy.bridge.<any-rustlib-fucntion>(...)
// .then(...)
// .catch(...)

// await not supported

// Object Model for other node.js Services - Service Provider Interface
// var ledger = libindy.newLedger({...})
```

# Getting Started

1. The Gold Standard - it should be this easy
	```
	git clone https://github.com/korsimoro/indy-sdk
	cd indy-sdk/libindy
	cargo build
	cargo build --release
	cd ../wrappers/ts
	npm run setup
	```

2. When it is not that easy
	- Check the Rust [installation instructions](../../README.md)
	- Make sure you have the right npm, node, and yarn - see [Technical Details](#Technical Details)


3. and if it wasn't easily fixed, help us by
	- fixing the problem and generating a pull request
	- [raising a support request](WHAT-LINK-GOES-HERE?)


# Runtime Configuration Options

* LibIndyRuntimeConfig
	```ts
	export interface LibIndyRuntimeConfig {
	  basepath?:string
	  reset?:boolean
	  winston?:any
	  ffi?:FFIInterfaceConfig
	  bridge?:BridgeInterfaceConfig
	  spi?:ServiceProviderInterfaceConfig
	}
	```
* FFIInterfaceConfig
	```ts
	export interface FFIInterfaceConfig {
	  libraryPath?:string
	}
	```

* BridgeInterfaceConfig
	```ts
	export interface BridgeInterfaceConfig {
	  increment_command_handle?:boolean
	  validate_serialized_json_string_parameters?:boolean,
	}
	```

* Service Provider Interface
	```ts
	export interface ServiceProviderInterfaceConfig {
	  loadGensisConfigTypes?:boolean,
	}
	```

# Architecture and Design

## Design Considerations

The following is a list of considerations which drove the design of this
package.

* **Focus on Use**
	The library exposes a set of Node.JS/Rust interfaces.  Each interface is
	suitable for a different pattern of use common to the node.js ecosystem.

	For example, express application authors will find the API.use(middleware)
	pattern familiar and powerful, while those working on low level
	server components might prefer to simply use the Rust methods directly.

	We hope that the wrapper can be used naturally, and without cumbersome
	adaptation, regardless of what sort of node.js application or package
	is being developed.

* **Single Source Base**
	The library starts with a typescript code base, and uses compilers and
	other language processors to make the APIs systematically in other
	execution environments.  The entire	API is always available in each
	typing environment.
	* **GOAL: Add Automatic Code Generation**
		- must consume the ffi interface as the authority of symbols
		- may consume additional information
		- must be integrated into the npm/yarn build chain


* **Perfect Parity**
	Perfect parity must be mainted with the Rust implementation. The module
	supports an [FFI (Foreign Function Interface)]() api which is a direct
	1:1 mapping of symbols and signatures exported by the rust library.  All
	other abilities are built upon this FFI.

* **Node.js restriction**
	Execution on node.js is supported, but browser execution is not.

* **Middleware Enhancement Pattern**  
	The bridge layer, which is wrapped around the FFI, is augmented with
	middleware capabilities, allowing API consumers to augment and extend
	the functionality of the core API as they see fit.


## Layered Architecture

The library is implemented in 3 layers:
1. [src/ffi/api.ts](#ffi/api.ts) - Call Oriented Foreign Function Interface
2. [src/bridge/api.ts](#bridge.ts) - Call Oriented Typescript Translation (Sync + Async)
3. [src/spi/api.ts](#spi/api.ts) - Object Oriented Service Provider Interface

Details:

1. [FFI](#ffi.ts)
	is a foreign function interface (FFI) to a native library written
	in Rust.  Node FFI is provided by [this npm package](https://www.npmjs.com/package/ffi).
	The FFI module supports direct, 1:1 access to libindy as follows:

	```ts
	libindy.ffi.<rust_method>(<rust-args>)
	```

	Key Points:
	* All argument type management and callback execution are handled by the caller
	* This namespace is the basis where the V8 machine connects with the rust library.
	*	The rest of the API is built upon this foundation.


2. [Bridge](#bridge.ts)
	is a bridge layer which adapts the FFI to environment constructs
 	like promises, async/await, implicit event loop, guaranteed thread saftey,
	JSON conversions, static type analysis, and the many, many other benefits of the
	typescript/node.js environment

	* [Promise](#bridge/promise.ts)
	  is a complete reflection of the FFI entry points in item #1 above, but
		returning only Promises

		```ts
		libindy.bridge.promise.<rust_method>(<rust-args>)
		.then(()=>{ /*...*/})
		.catch((err)=>{ /*...*/})
		```

		TODO:
		* enable automatic generation of this code

	* [Async](#bridge/async.ts)
		iis a complete wrapper around the promise library, adding async keywords
		around the invoking functions to facilitate use in await constructs.

		```ts
		try {
			await libindy.bridge.async.<rust_method>(<rust-args>)
		} catch(err) {
			/*...*/
		}
		```

		TODO:
		* enable automatic generation of this code

3. [spi](#spi/api.ts) an object oriented API intended for internal use
	* extracted from the bridge by argument-signature reduction
	* currently working on react and redux bindings to the SPI


#### Use Example
```ts
import { LibIndyRuntime } from 'libindy'

// create a default instance of the wrapper, and get the
// path to libindy from the LIBINDY_PATH environment variable.
const libindy = new LibIndyRuntime({})

// access the librust functions directly, with 1:1 symbol mapping
libindy.ffi.create_pool_ledger_config(...)

// access the librust functions taking advantage of static type
// analysis via the typescript bridge... the bridge provides two
// expressions - one returning Promises, one enabling async/await.
//
// the 'bridge' creates a contract, which can be syntactically generated
// from libindy.  TODO - migrate to automatic generation of promise
//
// bridge provides two models:
//    promise -> synchronously returns Promise objects
//    async -> asynchronously evaluates Promises

// you can use await with the async interface, which returns either
// result objects or throws and an IndyError exception with the
// appropraite ErrorCode (enumeration from Rust library)
await libindy.async.create_pool_ledger_config(...)

// when you need Promise's, you do this
libindy.bridge.
create_pool_ledger_config(...).
then(()=>{...}).
catch(()=>{...})

// and if you want to wrap all API calls, you can use middleware
// such as the activity tracer, that generates a call log by
// intercepting all calls, promise resolutions, and promise rejections.
import { DebugTrace} from 'libindy/middleware/traceactivity'
libindy.use(new DebugTrace({}))

// when you are in a native typescript environment, you can use a
// typed object model.
const ledger : Ledger = libindy.api.createNewTestLedger()
```


# Technical Details

Current configuration working with
* node 8.8.1
* typescript 2.3



## Language Issues

* Typescript

	TODO -
	* Current typescript level
	* tslint config
	* document tsconfig.json

* JavaScript / (ES5/ES6)

	TODO - create applicable ES5 & ES6

* JavaScript / Modules

	TODO - obligatory notes about module support

* Package Management

	Currently I support NPM
	Yarn support under consideration (interest?)

## Detailed Technical Docs

### [Foreign Function Interface](../tree/master/src/ffi/api.ts)

This is the ffi (Foreign Function Interface) boundary with the libindy rust
implementation.  The [ffi](https://www.npmjs.com/package/ffi)
npm package is used to access the compiled library.

You can use the ffi library directly, bypassing the rest
of the wrapper, as follows

```ts
import {FFIConfiguration} from 'indy-sdk'
import * as ffi from 'ffi'
const libindy = ffi.Library('/path/to/library',FFIConfiguration)
libindy.indy_<rust-method>(rust-args)
```

or, via the wrapper, as
```ts
import { LibIndyRuntime } from 'indy-sdk'
const libindy = new LibIndyRuntime({})
libindy.ffi.indy_<rust-method>(rust-args)
```

This interface addresses items \#2,\#3 and \#4 of
https://docs.google.com/document/d/15P6JOEKxbNC892DWReBStJIXrObVoaBDxbKJFOpAdjI/edit
as follows:

* \#2 - there is a 1:1 relationship between the rust methods and this api.

	- ffi_\* types are defined to map the api specification to ffi type strings
    without losing information about the actual parameter types represented
    by the primitive type. For example, arguments which represent did's are
    indicated by ffi_did, making it type-wise distinct from parameters which
    represent serialized json objects, represented as ffi_json_data_string,
    both of which map to the same ffi type identifier : 'string' which
    is less precise than ffi_did or ffi_json_data_string.

	- FFIConfiguration - this is the declaration of the UI provided by the
    Rust library, using the ffi_* type mapping constants.  this maps
    the Rust library at the symbol level, and preserves 100% parity
    with the core library.

* \#3 - this interface maintains 1:1 mapping between the ffi object and the symbols
  exported by the libindy object file, including the indy_ prefix.  There are
	no additions or subtractions from the api.

* \#4 - this api is bound to the version of libindy in the associated commit.
// TODO - how should we track the library to meet:

    The wrapper should document the earliest and latest version of libindy that it knows
    to be compatible. Likewise, it should document what platforms it targets, what use
    cases it's built for, etc.

  This file is silent on  this requirement:
    A wrapper should be able to find libindy using default
    OS methods (e.g., in the system PATH), but should also provide a way for a specific
    path to libindy to be specified, such that the wrapper can work either from an OS-wide
    install of libindy or a version in a particular directory.

  These considerations are dealt with in runtime.ts, which actually
  initializes the ffi object.

#### Pseudo-Types

FFI signatures look like this - which is the standard completion callback:
```ts
methodName:['void',['int','int','int']]
```
and lack significant information about the actual information represented
by the FFI type.

For this reason, pseudo-types were introduced for the purposes of generating
the FFIConfiguration object.

For Example:
```ts
const ffi_did = 'string'
const ffi_wallet_type_name = 'string'
const ffi_command_handle = 'int'
const ffi_error_code = 'int'
const ffi_wallet_name = 'string'
```

Which is matched, where required, by actual types, indicated by the ```rust_``` prefix

For example:
```ts
export type rust_did = string;
export type rust_error_code = number;
export type rust_command_handle = number;
export type rust_object_handle = number;
```

#### Callbacks

The Rust library callback mechanism does not mesh simply with the
asynchronous operations of node, as well as the async/await and promise
support native to the node.js languages

For example, to use FFI interfaces directly, you must use a lot of heavy
boilerplate code.

You need also need to support the command_handle argument
which can be ignored in the context of node.js.

```ts
import * as ffi from './ffi'
const command_handle : number = 0
(new Promise<void>((resolve,reject) => {
  	const result = libindy.ffi.indy_delete_pool_ledger_config(command_handle,
    	configuration_name,JSON.stringify(configuration_options),
			ffi.Callback('void', ['int', 'int'],
				(command_handle:number, error_code:number) => {
					if(error_code === 0) {
						resolve()
					}
					else {
						reject(new IndyError(error_code))
					}
				});
			)
		})
		// for some functions, the result will be returned without invoking
		// the callback.
		if(result !== 0) {
			reject(new IndyError(result))
		}
	}
)
.then((command_handle) => {
	// do something on success
})
.catch((error) => {
	// handle the IndyError exception
})
```

The ffi/callback.ts file contains some standard callback definitions
based on the ffi_* and rust_* types, which reduces some of the overhead.
For example, with this
```ts
export function default_callback(resolve:any,reject:any) {
  return ffi.Callback(ffi_void, [ffi_command_handle, ffi_errorcode],
    (command_handle:rust_command_handle, error_code:rust_error_code) => {
      if(error_code == 0) {
        resolve()
      }
      else {
        reject(new IndyError(error_code))
      }
    });
}
```
and ignoring command_handle, the standard promise call simplifies to this:
```ts
(new Promise<void>((resolve,reject) => {
  	const result = libindy.ffi.indy_delete_pool_ledger_config(0,
    	configuration_name,JSON.stringify(configuration_options),
			default_callback(resolve,reject))
		})
		if(result !== 0) {
			reject(new IndyError(result))
		}
	}
)
.then((command_handle) => {
	// do something on success
})
.catch((error) => {
	// handle the IndyError exception
})
```

In the next section we will see how we can use the bridge to simplify even
further.

### [Bridge (Promise & Async)](../tree/master/src/bridge/api.ts)

The bridge layer provides 4 features
1. supports static type optimizations
1. supports argument conversion where useful (auto stringification)
2. reduces boilerplate code
3. supports optional async/await as well as promise mode

For example, using the signature of create_pool_ledger_config changes from
```ts
'indy_create_pool_ledger_config': [ffi_errorcode, [ffi_command_handle,ffi_name,ffi_json_data_string,ffi_callback]]
```
to
```ts
create_pool_ledger_config(configuration_name:string,
	config_data?:json_object_or_serialized<create_pool_ledger_config_options>) : Promise<void>
```
and can be called as follows:
```ts
libindy.bridge.create_pool_ledger_config(configuration_name,config_data)
.then((command_handle) => {
	// do something on success
})
.catch((error) => {
	// handle the IndyError exception
})
```
or
```ts
try {
	await libindy.async.create_pool_ledger_config(configuration_name,config_data)
	// do something on success
} catch(error) {
	// handle the IndyError exception
}
```

#### Configuration Wrappers and JSON Strings

The rust library works with JSON configuration data as strings.  The node.js
bridge library defines an appropriate interface for each of the associated
JSON configurations.

For example, the optional config_data above is actually this type

```ts
export interface create_pool_ledger_config_options {
  ///     "refreshOnOpen": bool (optional), Forces pool ledger to be refreshed immediately after opening.
  ///                      Defaults to true.
  ///     "autoRefreshTime": int (optional), After this time in minutes pool ledger will be automatically refreshed.
  ///                        Use 0 to disable automatic refresh. Defaults to 24*60.
  ///     "networkTimeout": int (optional), Network timeout for communication with nodes in milliseconds.
  ///                       Defaults to 20000.  refreshOnOpen?:boolean
  refreshOnOpen?:boolean
  autoRefreshTime?:number
  networkTimeout?:number
}
```

but it in this signature
```ts
create_pool_ledger_config(configuration_name:string,
	config_data?:json_object_or_serialized<create_pool_ledger_config_options>) : Promise<void>
```
it also wrapped by ```json_object_or_serialized``` and config_data has the
optional marker (the ?).

This tells the API that you can use either a serialized json object, or
an instance of create_pool_ledger_config_options, which will then be
serialized using ```JSON.stringify``` before handing to the rust library.

In addition, if you wish to validate your json strings to make sure they
contain valid json, you can pass the ```validate_serialized_json_string_parameters```
flag to the bridge when creating libindy, like this:
```ts
const libindy = new LibIndyRuntime({
	bridge:{
		validate_serialized_json_string_parameters:true
		}
	})
```
which will cause any ```json_object_or_serialized``` strings to be verified
before invoking the libindy call.  This is expected to be useful in debugging
but not so much during production.


### [constants.ts](../tree/master/src/constants.ts)


```ts
import {
  LibIndyRuntime,
  defaultLocalNetworkConfigurationName,
  defaultLocalNetworkGenesisTransactions
} from './runtime'

const libindy = new LibIndyRuntime({
  reset:false
})

async function execute_example() : Promise<void> {
  // create pool ledger with given configuration
  await libindy.registerLedgerGenesisConfiguration({
    name:defaultLocalNetworkConfigurationName,
    genesis_txn:defaultLocalNetworkGenesisTransactions
    });

}

try {
    await execute_example()
}
catch(error) {
  console.log("Got error",error)
}


```
### Middleware

The bridge API supports middleware as follows:
```ts
const libindy = new LibIndyRuntime({
  reset:false
})
libindy.use(middleware)
```


# Test Environment

Tests have been stubbed out
- specific testing packages
	* mocha
	* chai
	* chai-as-promised
- normalized coniguration via 'harness.ts'
- symbolic links to libindy

## Fixtures

This is mapped by the environment.ts file in the harness.

## Harness

### ffi/harness.ts
### bridge/harness.ts
### index.ts

Exposes mocha primitives and exports symbols from all other harness files.

### logging.ts

Establishes a super simple logger, used as follows:

```
import { logger } from '../harness'
logger.debug("Write standard winston log messages here");
```

### network.ts

For interacting with a local docker sovrin environment.

### chai.ts
// configure to support sync/async functions - this requires import of
// assert,expect from this file.
TODO - tell the story of how expect.to.throw becomes expect.to.be.rejectedWith
and the various caveats around that.

### environment.ts

Provide support for tests needing to directly query or use the local test
environment.  These are links relative to the local repository.

Filesystem Requirements:
* test/fixtures/relative/rustlib -> ../../libindy/target
* test/fixtures/relative/env-var-test.dylib -> ../../libindy/target/release/libindy.dylib

Initial Use Case:
  - figure out if the local libindy has been built

### bridge.ts

# Notes and Issues

Agent api was excluded mostly, just because of the heavy call signatures - it will be
placed back shortly.

	1. yarn support
	2. adding winston logging

Concerned about building:
The wrapper should document the earliest and latest version of libindy that it knows to be compatible. Likewise, it should document what platforms it targets, what use cases it's built for, etc. A wrapper should be able to find libindy using default OS methods (e.g., in the system PATH), but should also provide a way for a specific path to libindy to be specified, such that the wrapper can work either from an OS-wide install of libindy or a version in a particular directory.

we need a solid way to build and tag.... help? ;)

## Addons

I am test consuming the library in two addon modules that are currently excluded from
the library - one is for express, the other is for redux integration.
