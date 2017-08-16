

var indy = require('bindings')('indy')

// we don't need this...
delete indy.path

// command handle to map to caller context
var max = Math.pow(2, 31) - 1
var min = Math.pow(-2, 31)
var handle = min - 1
Object.keys(indy).forEach(function(key) {
  var func = indy[key]
  indy[key] = function() {
    if (handle == max) {
      console.log('WARNING handle rollover')
      handle = min
    } else {
      handle += 1
    }
    console.log('HANDLE', handle)
    return func.call(indy, handle, ...arguments)
  }
})

// merge the error codes and export
module.exports = Object.assign(indy, {
  errors: {
    0: 'Success',
    100: 'CommonInvalidParam1',
    101: 'CommonInvalidParam2',
    102: 'CommonInvalidParam3',
    103: 'CommonInvalidParam4',
    104: 'CommonInvalidParam5',
    105: 'CommonInvalidParam6',
    106: 'CommonInvalidParam7',
    107: 'CommonInvalidParam8',
    108: 'CommonInvalidParam9',
    109: 'CommonInvalidParam10',
    110: 'CommonInvalidParam11',
    111: 'CommonInvalidParam12',
    112: 'CommonInvalidState',
    113: 'CommonInvalidStructure',
    114: 'CommonIOError',
    200: 'WalletInvalidHandle',
    201: 'WalletUnknownTypeError',
    202: 'WalletTypeAlreadyRegisteredError',
    203: 'WalletAlreadyExistsError',
    204: 'WalletNotFoundError',
    205: 'WalletIncompatiblePoolError',
    206: 'WalletAlreadyOpenedError',
    300: 'PoolLedgerNotCreatedError',
    301: 'PoolLedgerInvalidPoolHandle',
    302: 'PoolLedgerTerminated',
    303: 'LedgerNoConsensusError',
    304: 'LedgerInvalidTransaction',
    305: 'LedgerSecurityError',
    306: 'PoolLedgerConfigAlreadyExistsError',
    400: 'AnoncredsRevocationRegistryFullError',
    401: 'AnoncredsInvalidUserRevocIndex',
    402: 'AnoncredsAccumulatorIsFull',
    403: 'AnoncredsNotIssuedError',
    404: 'AnoncredsMasterSecretDuplicateNameError',
    405: 'AnoncredsProofRejected',
    500: 'SignusUnknownCryptoError'
  }
})