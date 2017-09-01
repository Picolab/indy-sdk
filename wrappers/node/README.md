
# Indy SDK for Node.js

This is a Node.js wrapper of the  [Indy](https://www.hyperledger.org/projects/indy) Rust library.

* [Getting Started](#Getting Started).
* [Runtime configuration options](#Runtime Configuration Options).
* [Architecture and Design](#Architecture and Design)
	- Design Considerations
	- Layered Architecture
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


Example Typescript/Newer JavaScript Use:
```ts
import { LibIndy,LibIndyRuntime } from 'indy-sdk'

const libindy : LibIndy = new LibIndyRuntime({...})

// libindy.ffi.<any-rustlib-function>(...)

// libindy.bridge.<any-rustlib-fucntion>(...)
// .then(...)
// .catch(...) // process an IndyError, wrapping the integer rust error code


// try {
//   await libindy.bridge.<any-rustlib-fucntion>(...)
// catch(error) {
//   // process an IndyError, wrapping the integer rust error code
// }

// Object Model for other node.js Services - Service Provider Interface
// const ledger : Ledger = libindy.newLedger({...})
```

Classic Javascript Use:
```javascript
var libindy = require('indy-sdk')

libindy.<any-rustlib-fucntion>(...)
.then(...)
.catch(...) // process and IndyError that wraps the error_code
```

In the classic javascript, all configuation abilities are removed, and the
only interface exported is the promise interface.

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

Configuration is entirely optional.

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
	You can optionally override the path to the DLL.  If libraryPath is not
	provided, it will use the value of LIBINDY_PATH from the env, unless
	that is absent.  It will fallback to ffi.dlopen('libindy'), which will
	use standard LD_LIBRARY_PATH
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

The library is implemented in 3 layers - each one wrapping the lower level.
1. [src/ffi/api.ts](#ffi/api.ts) - Call Oriented Native Foreign Function Interface
2. [src/bridge/api.ts](#bridge.ts) - Promise Oriented Typescript Interface
3. [src/spi/api.ts](#spi/api.ts) - Object Oriented Service Provider Interface

The package user is free to choose which style they prefer.

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
	*	The rest of the API is built upon this foundation.
	* Callbacks must be generated by the ffi.Callback() method, and will handle
	  native types exactly as specified in the rust library
	* command_handle argument is visible for programmer use
	* there is no type conversion
	* JSON objects must be passed as strings
	* the caller must handle the case where the function returns a non-zero
	  error_code but does not call the callback - typical of invalid parameters
	* Open Issues
	  - how to handle mutable types for return-parameters in wallet type definitions
		- how to handle memory management of returned allocated strings


2. [Bridge](#bridge.ts)
	is a bridge layer which adapts the FFI to environment constructs
 	like promises, async/await, implicit event loop, guaranteed thread safety,
	JSON conversions, static type analysis, and the many, many other benefits of the
	typescript/node.js environment.

  is a complete reflection of the FFI entry points in item #1 above, but
	returning only Promises

	```ts
	libindy.bridge.<rust_method>(<rust-args>)
	.then(()=>{ /*...*/})
	.catch((err)=>{ /*...*/})
	```
	Key Points:
	* All methods return a Promise, which resolves on success and provides
	  a return value if one is available
	* All non-zero error codes generate a promise Rejection and are returned
	  as IndyErrors, which wrap the rust integer error code
	* Callbacks for wallet types and agent connections use native node.js
	  types.
	* Optional middleware can be added to wrap all method calls
	* No command_handles are visible
	* JSON configuration objects may be given as either strings or objects
	  which are serialized for you
	* All methods and arguments have static type definitions

3. [spi](#spi/api.ts) an object oriented API
	* extracted from the bridge by argument-signature reduction
	* no handles are visible
	* currently working on react and redux bindings to the SPI


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

## Rust Logging

See https://doc.rust-lang.org/log/env_logger/ for information about configuring
the RUST_LOG output

```
export RUST_LOG=trace
```

will generate the most output.
```
export RUST_LOG=error
```
will suppress most of the output.

## INDY-SDK Debugging Output

The indy-sdk library uses [debug](https://github.com/visionmedia/debug) for
log level debug traces.  This debug output can be activated as follows:

```
export DEBUG="indy-sdx:*"
npm test
```

## FFI Debugging

The ffi library uses [debug](https://github.com/visionmedia/debug) to handle
debugging.  This debug output can be activated as follows:

```
export DEBUG="ffi:*"
npm test
```

with categories defined as follows

```
grep debug node_modules/ffi/lib/* | grep require
node_modules/ffi/lib/_foreign_function.js:  , debug = require('debug')('ffi:_ForeignFunction')
node_modules/ffi/lib/callback.js:  , debug = require('debug')('ffi:Callback')
node_modules/ffi/lib/cif.js:  , debug = require('debug')('ffi:cif')
node_modules/ffi/lib/cif_var.js:  , debug = require('debug')('ffi:cif_var')
node_modules/ffi/lib/dynamic_library.js:  , debug = require('debug')('ffi:DynamicLibrary')
node_modules/ffi/lib/ffi.js:var debug = require('debug')('ffi:ffi')
node_modules/ffi/lib/foreign_function.js:  , debug = require('debug')('ffi:ForeignFunction')
node_modules/ffi/lib/foreign_function_var.js:  , debug = require('debug')('ffi:VariadicForeignFunction')
node_modules/ffi/lib/function.js:  , debug = require('debug')('ffi:FunctionType')
node_modules/ffi/lib/library.js:  , debug = require('debug')('ffi:Library')
node_modules/ffi/lib/type.js:var debug = require('debug')('ffi:types')
```

## Mocha Examples using Chai-as-promised

Promise results can be tested using the following pattern and a sync function()
```ts
it('should be ok for single well formed genesis txn', function() {
	const path = setup_config_file(single_genesis_txn)
	console.log(path)
	console.log(JSON.stringify(single_genesis_txn))
	const promise = libindy.bridge.create_pool_ledger_config("bridge_test_04",{
		genesis_txn:path
	})
	return promise.should.be.fulfilled
});
```

Sequences with multiple promises can be used with an async function, by changing from
promise.should to expect.to
```ts
describe('#delete_pool_ledger_config', function() {
it('should be ok for deleting a configuration created from a single well formed genesis txn', async function() {
	const path = setup_config_file(single_genesis_txn)
	const config_name = "bridge_test_05"
	await libindy.bridge.create_pool_ledger_config(config_name,{
		genesis_txn:path
	})
	const result = await libindy.bridge.delete_pool_ledger_config(config_name);
	expect(result).to.equal(undefined);
	});
})
```


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

## Casing and Capitalization

The official spec is here - https://github.com/Microsoft/TypeScript/wiki/Coding-guidelines
but I think we should use ```_``` for at least the ffi methods.  Personally I find camelcase
very difficult to read - so I tend to use ```_``` until forced to do otherwise.

We can just open up a task/todo to track getting this (and other coding guidelines)
right - there is a tslint config I've left out....  that will provide another source
of conformance.

## Addons

I am test consuming the library in two addon modules that are currently excluded from
the library - one is for express, the other is for redux integration.
