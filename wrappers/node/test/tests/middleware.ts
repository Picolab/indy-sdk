import {
  describe,it,before,after,beforeEach,afterEach, // mocha
  expect,assert,//should, from chai + chai-as-promised
  getLibIndy
} from '../harness'

import {
  ErrorCode,IndyError,
  LibIndyRuntime,
} from '../../src'

import { DebugTrace } from '../../src/middleware/traceactivity'
import { CollectMetrics } from '../../src/middleware/metrics'
import { ValidateParameters,ValidationError } from '../../src/middleware/validate'

describe('Middleware', function() {

  let libindy

  before(function() {
    libindy = getLibIndy({
      reset:true
    })

  });

  after(function() {
    // runs after all tests in this block
  });

  beforeEach(function() {
    // runs before each test in this block
  });

  afterEach(function() {
    // runs after each test in this block
  });

  describe('DebugTrace', function() {

    it('should initialize ok',function() {
      // this will log the entrances and exits from all
      libindy.use(new DebugTrace())
    });

/*
    describe('#newLedger()', function() {

      it('should throw a ValidationError when given an undefined name', async function() {

        expect(libindy.newLedger({
            name:undefined,
            genesis_txn:defaultLocalNetworkGenesisTransactions
          },
          {

          })
          //).to.be.rejectedWith(new ValidationError("create_pool_ledger_config","configuration_name can not be undefined"))
        ).to.be.rejectedWith(ValidationError)
      });


      it('should be able to create a ledger', async function() {
        const ledger : Ledger = await libindy.newLedger({
          name:defaultLocalNetworkConfigurationName,
          genesis_txn:defaultLocalNetworkGenesisTransactions
        },
        {

        });

        console.log("ledger:",ledger);
      });
*/

  });
});
