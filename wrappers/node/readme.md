
# node bindings to libindy

this addon is still experimental, expect some parts of it to function incorrectly.

[n-api](https://npmjs.org/package/node-addon-api) is being used to call into c++, which means only node v8.0.0 and above will work (at least, until n-api has been backported to older node versions)

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

## debugging

* ensure you're running the correct node version with `nvm use || nvm install`
* build in debug mode `npm install --debug`
* create and open an xcode project `npm run xcode`
* edit the project to use the scheme file located at `test/libindy.xcscheme`
* run