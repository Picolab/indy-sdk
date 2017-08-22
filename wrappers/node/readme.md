
# libindy for node.js

this addon is still experimental, expect some parts of it to function incorrectly or not at all. it uses [n-api](https://npmjs.org/package/node-addon-api) to call into node from c++.

## prerequisites

* [nvm](https://nvm.sh)

## building

* build `libindy` by following [platform-specific instructions](https://github.com/hyperledger/indy-sdk/tree/master/doc)
* copy the resulting static library from `../libindy/target/$target_name` to `./include/`
* copy the header files from `../libindy/include` to `./include`
* run `npm install` from `.`

## supporting shell scripts

* `install`: reinstall node-gyp (and other dependencies) and recompile all native sources
* `build`: compile all native sources (accepts `--debug` flag to compile with debug symbols)
* `test`: run javascript test suite
* `libindy-symbols`: list exported symbols from libindy
* `libindy`: build libindy
* `xcode`: generate a xcode project to run sources against lldb
* `test-loop`: run test suite until a failure occurs

## debugging

* `nvm use || nvm install`
* `npm install --debug`
* `npm run xcode`
* import project scheme from `test/libindy.xcscheme`
* run

## todos

* find a better way to allocate and schedule new callbacks from callbacks that return handle results (due to limitations in n-api, the way it's been implemented is quite leaky. modifying libindy to know about n-api would help loads here.)
* test with gcc
* javascript tests
* tests against a sovrin node
* ci with travis and appveyor
* fully redistributable package
* `register_wallet_type`
* it ought to be possible to (mostly) automate the generation of bindings from the output of `npm run libindy-symbols`