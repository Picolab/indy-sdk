import {
  describe,it,before,after,beforeEach,afterEach, // mocha
  expect,assert,//should, from chai + chai-as-promised
  getLibIndy,
  assert_indy_error,
  ErrorCode
} from '../harness'
import * as tmp from 'tmp'
import * as fs from 'fs-extra'

const single_genesis_txn = { data:{
  alias:"Node1",
  client_ip:"127.0.0.1",
  client_port:9701,
  node_ip:"127.0.0.1",
  node_port:9702,
  services:["VALIDATOR"],
  dest:"Gw6pDLhcBcoQesN72qfotTgFa7cbuqZpkX3Xo6pLhPhv",
  identifier:"Th7MpTaRZVRYnPiabds81Y",
  txnId:"fea82e10e894419fe2bea7d96296a6d46f50f93f9eeda954ec461b2ed2950b62",
  type:"0"
} }

function setup_config_file(payload:any) :string{
  const tempfile = tmp.fileSync();
  const path = tempfile.name
  fs.writeFileSync(path,JSON.stringify(payload))
  fs.appendFileSync(path,"\n")
  return path
}

async function create_reference_pool(libindy:any,config_name:string) {
  const path = setup_config_file(single_genesis_txn)
  await libindy.bridge.create_pool_ledger_config(config_name,{
    genesis_txn:path
  })
}


describe('The Bridge,', function() {
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

  describe('Promise Interface,', function() {

    describe('pool.rs support,', function() {
      const default_config_name = "test-config-name"

      after(() => {
        fs.removeSync(default_config_name + ".txn")
      })
      describe('#create_pool_ledger_config', function() {

        it('should work for null configuration with file in local directory, suffixed by txn and having same name as the config', function() {
          fs.appendFileSync(default_config_name + ".txn","")

          const promise = libindy.bridge.create_pool_ledger_config(default_config_name, null)
          return promise.should.be.fulfilled
        });

        it('should fail with PoolLedgerConfigAlreadyExistsError config names as pathnames', function() {
          const tempfile = tmp.fileSync();
          const path = tempfile.name
          fs.appendFileSync(path,"")

          const promise = libindy.bridge.create_pool_ledger_config(path, null)
          return assert_indy_error(promise,ErrorCode.PoolLedgerConfigAlreadyExistsError)
        });

        it('should fail for null configuration', function() {
          const promise = libindy.bridge.create_pool_ledger_config("bridge_test_01", null)
          // NOTE: sometimes I get this - depends on the above two
          // return assert_indy_error(promise,ErrorCode.CommonInvalidStructure)
          return assert_indy_error(promise,ErrorCode.CommonIOError)
        });

        it('should pass for zero byte configuration', function() {
          const tempfile = tmp.fileSync();
          const path = tempfile.name
          fs.appendFileSync(path,"")

          const promise = libindy.bridge.create_pool_ledger_config("bridge_test_02",{
            genesis_txn:path
          })

          return promise.should.be.fulfilled
        });

        it('should pass on whitespace only', function() {
          const tempfile = tmp.fileSync();
          const path = tempfile.name
          fs.appendFileSync(path,"\n")

          const promise = libindy.bridge.create_pool_ledger_config("bridge_test_03",{
            genesis_txn:tempfile.name
          })
          return promise.should.be.fulfilled
        });


        it('should be ok for single well formed genesis txn', function() {
          const path = setup_config_file(single_genesis_txn)
          console.log(path)
          console.log(JSON.stringify(single_genesis_txn))
          const promise = libindy.bridge.create_pool_ledger_config("bridge_test_04",{
            genesis_txn:path
          })
          return promise.should.be.fulfilled
        });

      });

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

        it('should fail when deleting a non-existant config', function() {
          const config_name = "bridge_test_06"
          const promise = libindy.bridge.delete_pool_ledger_config(config_name);
          return assert_indy_error(promise,ErrorCode.CommonIOError)
        });

        it('need to test deleting an opened ledger?', function() {
        });

      })


      describe('#indy_open_pool_ledger', function() {
        it('should fail with missing config', async function() {
          const config_name = "bridge_test_07"
          const result = await libindy.bridge.open_pool_ledger(config_name, null)
          expect(result).to.equal(undefined)
        });
        it('should pass with null config for pool and null open options', async function() {
          const config_name = "bridge_test_08"
          await libindy.bridge.create_pool_ledger_config(config_name,null)
          const result = await libindy.bridge.open_pool_ledger(config_name, null)
          expect(result).to.equal(undefined)
        });
        it('should pass with reference config and null open options', async function() {
          const config_name = "bridge_test_09"
          await create_reference_pool(libindy,config_name)
          const result = await libindy.bridge.open_pool_ledger(config_name, null)
          expect(result).to.equal(undefined)
        });

      })
    });

    describe('ledger.rs support,', function() {
      describe('#<func>', function() {

        it('should....',function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('wallet.rs support,', function() {
      describe('#<func>', function() {

        it('should....',function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('signus.rs support,', function() {
      describe('#<func>', function() {

        it('should....',function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('anoncreds.rs support,', function() {
      describe('#<func>', function() {

        it('should....',function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('agent.rs support,', function() {
      describe('#<func>', function() {

        it('should....',function() {
          assert.fail("not yet implemented")
        });
      });
    });

    describe('mod.rs support,', function() {
      describe('#<func>', function() {

        it('should....',function() {
          assert.fail("not yet implemented")
        });
      });
    });

  });
});
