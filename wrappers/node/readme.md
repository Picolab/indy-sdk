
# indy-sdk for node

this addon has been authored using [n-api](https://npmjs.org/package/node-addon-api). as a result, it only works on node `>=8.0.0`.

## prerequisites

* [nvm](https://nvm.sh)

## building

* build `libindy` by following [platform specific instructions](/tree/master/doc)
* copy the resulting static library contained in `../libindy/target/$target_name` to `./include/`
* copy the header files contained in `../libindy/include` to `./include`
* run `npm install` from `.`
* copy the resulting addon (`indy.node`) from `./build/Release` into your project