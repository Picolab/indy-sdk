import {
  describe,it,before,after,beforeEach,afterEach, // mocha
  expect,assert,//should, from chai + chai-as-promised
  DEBUG_LIBRARY,RELEASE_LIBRARY,RELATIVE_LIBRARY_BASE,
  canFindRelativeDebugLibrary,
  canFindRelativeReleaseLibrary
} from '../harness'

import {
  ErrorCode,IndyError,
  LibIndyRuntime
} from '../../src'



describe('The Foreign Function Interface, ', function() {

  before(async function() {
    //}
    // runs before all tests in this block
    if(!await canFindRelativeDebugLibrary()) {
      throw new Error("UNEXPECTED TEST ENVIRONMENT - ABORTING TESTING"+
                      "\nCan not locate debug library,"+
                      "\ncheck the test/fixtures/relative/rustlib"+
                      "\nsymbolic link."+
                      "\nThe current value is :" + DEBUG_LIBRARY +
                      "\nFurther tests have been halted."
                    )
    }

    if(!await canFindRelativeReleaseLibrary()) {
      throw new Error("UNEXPECTED TEST ENVIRONMENT - ABORTING TESTING"+
                      "\nCan not locate debug library,"+
                      "\ncheck the test/fixtures/relative/rustlib"+
                      "\nsymbolic link."+
                      "\nThe current value is :" + RELEASE_LIBRARY +
                      "\nFurther tests have been halted."
                    )
    }

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

  describe('LibIndyRuntime', function() {

    describe('creation process', function() {
      it('should be able to find a standard library by default', function() {
        const libindy = new LibIndyRuntime({
          reset:true
        })
      });

      it('should not error when creating a runtime against DEBUG_LIBRARY', function() {
        const libindy = new LibIndyRuntime({
          reset:true,
          ffi: {
            libraryPath:DEBUG_LIBRARY
          }
        })
      });
      it('should not error when creating a runtime against RELEASE_LIBRARY', function() {
        const libindy = new LibIndyRuntime({
          reset:true,
          ffi: {
            libraryPath:RELEASE_LIBRARY
          }
        })
      });

      it('should be able to find a custom library specified by LIBINDY_PATH env var', function() {
        process.env.LIBINDY_PATH = RELATIVE_LIBRARY_BASE + "/env-var-test"
        const libindy = new LibIndyRuntime({
        })
      });

    }); /* loading */

    describe('configuration options', function() {
      before(function() {
        process.env.LIBINDY_PATH=RELEASE_LIBRARY
      })

      it('should honor reset = true', function() {
        const libindy = new LibIndyRuntime({
          reset:true
        })
      });

      it('should not reset unless requested', function() {
        const libindy = new LibIndyRuntime({
          reset:false
        })
      });
      it('should default to reset = false', function() {
        const libindy = new LibIndyRuntime({
        })
      });
    }); /* configuration */

  }); /* runtime */


/*
  describe('Pool Functions', function() {
    it('indy_create_pool_ledger_config', function() {
      assert.fail()
    });
    it('indy_open_pool_ledger', function() {
      assert.fail()
    });
    it('indy_refresh_pool_ledger', function() {
      assert.fail()
    });
    it('indy_close_pool_ledger', function() {
      assert.fail()
    });
    it('indy_delete_pool_ledger_config', function() {
      assert.fail()
    });

  });

  describe('Wallet Functions', function() {
  });
*/
});
