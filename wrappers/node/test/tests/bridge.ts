import {
  describe,it,before,after,beforeEach,afterEach, // mocha
  expect,assert,//should, from chai + chai-as-promised
  logger, // winston logger
  getLibIndy
} from '../harness'
import {
  ErrorCode,IndyError
} from '../../src'

import * as winston from 'winston'


describe('The Bridge,', function() {
  let promise_bridge
  let async_bridge

  before(function() {
    const libindy = getLibIndy({
      reset:true
    })
    promise_bridge = libindy.bridge
    async_bridge = libindy.async
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

  describe('Promise Interface,', function() {

    describe('pool.rs support,', function() {
      describe('#create_pool_ledger_config', function() {

        it('should....', async function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('ledger.rs support,', function() {
      describe('#<func>', function() {

        it('should....', async function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('wallet.rs support,', function() {
      describe('#<func>', function() {

        it('should....', async function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('signus.rs support,', function() {
      describe('#<func>', function() {

        it('should....', async function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('anoncreds.rs support,', function() {
      describe('#<func>', function() {

        it('should....', async function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('agent.rs support,', function() {
      describe('#<func>', function() {

        it('should....', async function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('mod.rs support,', function() {
      describe('#<func>', function() {

        it('should....', async function() {
          assert.fail("not yet implemented")
        });
      });
    });

  });
});
