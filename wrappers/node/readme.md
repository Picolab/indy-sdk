
# node bindings to libindy

this addon is being authored using [n-api](https://npmjs.org/package/node-addon-api). as a result, it will only work on node `>=8.0.0`.

## prerequisites

* [nvm](https://nvm.sh)

## building

* build `libindy` by following [platform-specific instructions](https://github.com/hyperledger/indy-sdk/tree/master/doc)
* copy the resulting static library contained in `../libindy/target/$target_name` to `./include/`
* copy the header files contained in `../libindy/include` to `./include`
* run `npm install` from `.`
* finally, either:
  - copy the resulting addon (`indy.node`) from `./build/Release` into your project
  - or copy this directory into your project's `node_modules` directory and `require` as `indy-sdk`