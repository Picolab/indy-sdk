import {
  describe,it,before,after,beforeEach,afterEach, // mocha
  expect,assert,//should, from chai + chai-as-promised
  DEBUG_LIBRARY,RELEASE_LIBRARY,RELATIVE_LIBRARY_BASE,
  canFindRelativeDebugLibrary,
  canFindRelativeReleaseLibrary,
  defaultLocalNetworkConfigurationName,
  defaultLocalNetworkGenesisTransactions,
  getLibIndy
} from '../harness'

import {
  ErrorCode,IndyError,
  LibIndy,LibIndyRuntime,
  Ledger
} from '../../src'
import * as util from 'util'


describe('SPI - Runtime', function() {

  describe('Initialization', function() {
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

    describe('#newLedger()', function() {

      it('should be able to create a default ledger',async function() {
        const ledger : Ledger = await libindy.spi.newLedger(
          // pool configuration
          {
            name:"spi_test_001",
            genesis_txn:defaultLocalNetworkGenesisTransactions
          },
          //
          {
            configurationName:"spi_test_001",
          });
        console.log("ledger:",ledger);
      });


    });
  });

  describe('Ledger', function() {

    before(function() {
      // runs before all tests in this block
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

    describe('AttribRequestsTest', function() {
      let pool;
      let wallet;
      const walletName : string= "ledgerWallet";
      const identifier : string = "Th7MpTaRZVRYnPiabds81Y";
      const dest : string = "FYmoFw55GeQH7SRFa37dkx1d2dZ3zUF8ckg7wmL7ofN4";
      const endpoint : string = "{\"endpoint\":{\"ha\":\"127.0.0.1:5555\"}}";

      before(function() {
        // runs before all tests in this block

        //String poolName = PoolUtils.createPoolLedgerConfig();
        //pool = Pool.openPoolLedger(poolName, null).get();

        //Wallet.createWallet(poolName, walletName, "default", null, null).get();
        //wallet = Wallet.openWallet(walletName, null, null).get();
      });

      after(function() {
        // runs after all tests in this block
        //pool.closePoolLedger().get();
        //wallet.closeWallet().get();
        //Wallet.deleteWallet(walletName, null).get();
      });

      beforeEach(function() {
        // runs before each test in this block
      });

      afterEach(function() {
        // runs after each test in this block
      });

      it('testBuildAttribRequestWorksForRawData',function () {
        const expectedResult = util.format("\"identifier\":\"%s\"," +
                        "\"operation\":{" +
                        "\"type\":\"100\"," +
                        "\"dest\":\"%s\"," +
                        "\"raw\":\"%s\"" +
                        "}", identifier, dest, endpoint);

        // attribRequest = Ledger.buildAttribRequest(identifier, dest, null, endpoint, null).get();

        // assert.equals(true,attribRequest.replace("\\", "").contains(expectedResult));});
      });
      it('testBuildAttribRequestWorksForMissedAttribute',function () {
        assert.fail()
      });

      it('testBuildGetAttribRequestWorks',function () {
        assert.fail()
      });

      it('testSendAttribRequestWorksWithoutSignature',function () {
        assert.fail()
      });

      it('testAttribRequestsWorks',function () {
        assert.fail()
      });

      it('testBuildAttribRequestWorksForInvalidIdentifier',function () {
        assert.fail()
      });

      it('testBuildAttribRequestWorksForRawData',function () {
        assert.fail()
      });
    });

    describe('ClaimDefRequestsTest', function() {
      it('testBuildClaimDefRequestWorks',function () {
        assert.fail()
      });

      it('testBuildGetClaimDefRequestWorks',function () {
        assert.fail()
      });

      it('testBuildClaimDefRequestWorksForInvalidJson',function () {
        assert.fail()
      });

      it('testClaimDefRequestsWorks',function () {
        assert.fail()
      });

      it('testClaimDefRequestWorksWithoutSignature',function () {
        assert.fail()
      });

    });

    describe('GetTxnRequestTest', function() {
      it('testBuildGetTxnRequestWorks',function () {
        assert.fail()
      });

      it('testGetTxnRequestWorks',function () {
        assert.fail()
      });

      it('testGetTxnRequestWorksForInvalidSeqNo',function () {
        assert.fail()
      });

    });

    describe('NodeRequestsTest', function() {
      it('testBuildNodeRequestWorks',function () {
        assert.fail()
      });

      it('testSendNodeRequestWorksWithoutSignature',function () {
        assert.fail()
      });

      it('testBuildNodeRequestWorksForWrongServiceType',function () {
        assert.fail()
      });

      it('testBuildNodeRequestWorksForMissedField',function () {
        assert.fail()
      });

      it('testSendNodeRequestWorksForWrongRole',function () {
        assert.fail()
      });

      it('testSendNodeRequestWorksForNewSteward',function () {
        assert.fail()
      });

    });

    describe('NymRequestsTest', function() {
      it('testBuildNymRequestWorksForOnlyRequiredFields',function () {
        assert.fail()
      });

      it('testBuildNymRequestWorksForOnlyOptionalFields',function () {
        assert.fail()
      });

      it('testBuildGetNymRequestWorks',function () {
        assert.fail()
      });

      it('testNymRequestWorksWithoutSignature',function () {
        assert.fail()
      });

      it('testSendNymRequestsWorksForOptionalFields',function () {
        assert.fail()
      });

      it('testGetNymRequestWorks',function () {
        assert.fail()
      });

      it('testSendNymRequestsWorksForWrongSignerRole',function () {
        assert.fail()
      });

      it('testSendNymRequestsWorksForUnknownSigner',function () {
        assert.fail()
      });

      it('testNymRequestsWorks',function () {
        assert.fail()
      });

      it('testSendNymRequestsWorksForWrongRole',function () {
        assert.fail()
      });

    });

    describe('RequestsTest', function() {
      it('testSubmitRequestWorks',function () {
        assert.fail()
      });

      it('testSignAndSubmitRequestWorks',function () {
        assert.fail()
      });

      it('testSignAndSubmitRequestWorksForNotFoundSigner',function () {
        assert.fail()
      });

      it('testSignAndSubmitRequestWorksForIncompatibleWalletAndPool',function () {
        assert.fail()
      });

    });

    describe('SchemaRequestsTest', function() {
      it('testBuildSchemaRequestWorks',function () {
        assert.fail()
      });

      it('testBuildGetSchemaRequestWorks',function () {
        assert.fail()
      });

      it('testSchemaRequestWorksWithoutSignature',function () {
        assert.fail()
      });

      it('testSchemaRequestsWorks',function () {
        assert.fail()
      });

      it('testGetSchemaRequestsWorksForUnknownSchema',function () {
        assert.fail()
      });

      it('testBuildSchemaRequestWorksForMissedFields',function () {
        assert.fail()
      });

    });

    describe('SignRequestTest', function() {
      it('testSignWorks',function () {
        assert.fail()
      });

      it('testSignWorksForUnknowDid',function () {
        assert.fail()
      });

      it('testSignWorksForInvalidMessageFormat',function () {
        assert.fail()
      });

    });

  });

  describe('Pool', function() {

    describe('ClosePoolTest', function() {

      it('testClosePoolWorks',function () {
        assert.fail();
      });

      it('testClosePoolWorksForTwice',function () {
        assert.fail();
      });

      it('testClosePoolWorksForReopenAfterClose',function () {
        assert.fail();
      });
    });


    describe('CreatePoolTest', function() {
      it('testCreatePoolWorksForNullConfig',function () {
        assert.fail();
      });

      it('testCreatePoolWorksForConfigJSON',function () {
        assert.fail();
      });

      it('testCreatePoolWorksForEmptyName',function () {
        assert.fail();
      });

      it('testCreatePoolWorksForNullConfig',function () {
        assert.fail();
      });

      it('testCreatePoolWorksForTwice',function () {
        assert.fail();
      });

    });

    describe('DeletePoolTest', function() {
      it('testDeletePoolWorks',function () {
        assert.fail();
      });

      it('testDeletePoolWorksForOpened',function () {
        assert.fail();
      });
    });

    describe('OpenPoolTest', function() {
      it('testOpenPoolWorksForNullConfig',function () {
        assert.fail();
      });

      it('testOpenPoolWorksForConfig',function () {
        assert.fail();
      });

      it('testOpenPoolWorksForTwice',function () {
        assert.fail();
      });

      it('testOpenPoolWorksForTwoNodes',function () {
        assert.fail();
      });

      it('testOpenPoolWorksForThreeNodes',function () {
        assert.fail();
      });

    });

    describe('RefreshPoolTest', function() {
      it('testRefreshPoolWorks',function () {
        assert.fail();
      });

    });


  });

  describe('Anoncreds', function() {
    describe('IssuerCreateAndStoreClaimDefinitionTest', function() {
      it('testIssuerCreateAndStoreClaimDefWorks',function () {
        assert.fail();
      });

      it('testIssuerCreateAndStoreClaimDefWorksForInvalidSchemaJson',function () {
        assert.fail();
      });

      it('testIssuerCreateAndStoreClaimDefWorksForEmptyKeys',function () {
        assert.fail();
      });

      it('testIssuerCreateAndStoreClaimDefWorksForCorrectCryptoType',function () {
        assert.fail();
      });

      it('testIssuerCreateAndStoreClaimDefWorksForInvalidCryptoType',function () {
        assert.fail();
      });
    });

    describe('IssuerCreateClaimTest', function() {
      it('testIssuerCreateClaimWorks',function () {
        assert.fail();
      });

      it('testIssuerCreateClaimWorksForClaimDoesNotCorrespondToClaimRequest',function () {
        assert.fail();
      });

      it('testIssuerCreateClaimWorksForInvalidClaim',function () {
        assert.fail();
      });
    });

    describe('ProverCreateAndStoreClaimReqTest', function() {
      it('testProverCreateAndStoreClaimReqWorks',function () {
        assert.fail();
      });

      it('testProverCreateAndStoreClaimReqWorksForClaimDefDoesNotCorrespondToClaimOfferDifferentIssuer',function () {
        assert.fail();
      });

      it('testProverCreateAndStoreClaimReqWorksForClaimDefDoesNotCorrespondToClaimOfferDifferentSchema',function () {
        assert.fail();
      });

      it('testProverCreateAndStoreClaimReqWorksForInvalidClaimOffer',function () {
        assert.fail();
      });

      it('testProverCreateAndStoreClaimReqWorksForInvalidMasterSecret',function () {
        assert.fail();
      });
    });

    describe('ProverCreateMasterSecretTest', function() {
      it('testProverCreateMasterSecretWorks',function () {
        assert.fail();
      });

      it('testProverCreateMasterSecretWorksForDuplicate',function () {
        assert.fail();
      });

      it('testProverCreateMasterSecretWorksForEmptyName',function () {
        assert.fail();
      });
    });

    describe('ProverCreateProofTest', function() {
      it('testProverCreateProofWorks',function () {
        assert.fail();
      });

      it('testProverCreateProofWorksForInvalidRequestedClaimsJson',function () {
        assert.fail();
      });

      it('testProverCreateProofWorksForInvalidMasterSecret',function () {
        assert.fail();
      });

      it('testProverCreateProofWorksForInvalidSchemas',function () {
        assert.fail();
      });

      it('testProverCreateProofWorksForInvalidRequestedClaimsJson',function () {
        assert.fail();
      });
    });

    describe('ProverGetClaimOfferTest', function() {
      it('testsProverGetClaimOffersWorksForEmptyFilter',function () {
        assert.fail();
      });

      it('testsProverGetClaimOffersWorksForFilterByIssuer',function () {
        assert.fail();
      });

      it('testsProverGetClaimOffersWorksForFilterBySchema',function () {
        assert.fail();
      });

      it('testsProverGetClaimOffersWorksForFilterByIssuerAndSchema',function () {
        assert.fail();
      });

      it('testsProverGetClaimOffersWorksForNoResult',function () {
        assert.fail();
      });

      it('testsProverGetClaimOffersWorksForInvalidFilterJson',function () {
        assert.fail();
      });

      it('testOpenWalletWorksForPlugged',function () {
        assert.fail();
      });
    });

    describe('ProverGetClaimsForProofRequestTest', function() {
      it('testProverGetClaimsForProofRequestWorksForRevealedAttribute',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForNotFoundAttribute',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForSatisfyPredicate',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForNotSatisfyPredicate',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForMultiplyAttributesAndPredicates',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForEmptyRequest',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForRevealedAttributeWithOtherSchema',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForRevealedAttributeBySpecificIssuer',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForSatisfyPredicateByIssuerAndSchema',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForInvalidProofRequest',function () {
        assert.fail();
      });

      it('testProverGetClaimsForProofRequestWorksForInvalidPredicateType',function () {
        assert.fail();
      });
    });

    describe('ProverGetClaimsTest', function() {
      it('testProverGetClaimsWorksForEmptyFilter',function () {
        assert.fail();
      });

      it('testProverGetClaimsWorksForFilterByIssuer',function () {
        assert.fail();
      });

      it('testProverGetClaimsWorksForFilterByIssuerAndSchema',function () {
        assert.fail();
      });

      it('testProverGetClaimsWorksForEmptyResult',function () {
        assert.fail();
      });

      it('testProverGetClaimsWorksForInvalidFilterJson',function () {
        assert.fail();
      });
    });

    describe('ProverStoreClaimOfferTest', function() {
      it('testProverStoreClaimOfferWorks',function () {
        assert.fail();
      });

      it('testProverStoreClaimOfferWorksForInvalidJson',function () {
        assert.fail();
      });

      it('testProverStoreClaimOfferWorksForInvalidIssuerDid',function () {
        assert.fail();
      });
    });

    describe('ProverStoreClaimTest', function() {
      it('testProverStoreClaimWorks',function () {
        assert.fail();
      });

      it('testProverStoreClaimWorksWithoutClaimReq',function () {
        assert.fail();
      });

      it('testProverStoreClaimWorksForInvalidClaimJson',function () {
        assert.fail();
      });
    });

    describe('VerifierVerifyProofTest', function() {
      it('testVerifierVerifyProofWorksForCorrectProof',function () {
        assert.fail();
      });

      it('testVerifierVerifyProofWorksForProofDoesNotCorrespondToRequested',function () {
        assert.fail();
      });

      it('testVerifierVerifyProofWorksForWrongProof',function () {
        assert.fail();
      });

      it('testVerifierVerifyProofWorksForInvalidProofJson',function () {
        assert.fail();
      });
    });

  });

  describe('Agent', function() {
    describe('AgentAddIdentityTest', function() {
      it('testAgentAddIdentityWorks',function () {
        assert.fail();
      });

      it('testAgentAddIdentityWorksForMultiplyKeys',function () {
        assert.fail();
      });
    });

    describe('AgentCloseConnectionTest', function() {
      it('testAgentCloseConnectionWorksForOutgoing',function () {
        assert.fail();
      });

      it('testAgentCloseConnectionWorksForIncoming',function () {
        assert.fail();
      });
    });

    describe('AgentCloseListenerTest', function() {
      it('testAgentCloseConnectionWorksForOutgoing',function () {
        assert.fail();
      });
    });

    describe('AgentConnectTest', function() {
      it('testAgentConnectWorksForRemoteData',function () {
        assert.fail();
      });

      it('testAgentConnectWorksForAllDataInWalletPresent',function () {
        assert.fail();
      });
    });

    describe('AgentListenTest', function() {
      it('testAgentListenWorksForAllDataInWalletPresent',function () {
        assert.fail();
      });
    });

    describe('AgentRemoveIdentityTest', function() {
      it('testAgentRemoveIdentityWorks',function () {
        assert.fail();
      });
    });

    describe('AgentSendTest', function() {
      it('testAgentSendWorksForAllDataInWalletPresent',function () {
        assert.fail();
      });
    });
  });

  describe('Signus', function() {

    describe('CreateMyDidTest', function() {
      it('testCreateMyDidWorksForEmptyJson',function () {
        assert.fail();
      });

      it('testCreateMyDidWorksForSeed',function () {
        assert.fail();
      });

      it('testCreateMyDidWorksAsCid',function () {
        assert.fail();
      });

      it('testCreateMyDidWorksForPassedDid',function () {
        assert.fail();
      });

      it('testCreateMyDidWorksForCorrectCryptoType',function () {
        assert.fail();
      });

      it('testCreateMyDidWorksForInvalidSeed',function () {
        assert.fail();
      });

      it('testCreateMyDidWorksForInvalidCryptoType',function () {
        assert.fail();
      });

      it('testCreateMyDidWorksForAllParams',function () {
        assert.fail();
      });

    });

    describe('DecryptTest', function() {
      it('testDecryptWorks',function () {
        assert.fail();
      });

      it('testDecryptWorksForOtherCoder',function () {
        assert.fail();
      });

      it('testDecryptWorksForNonceNotCorrespondMessage',function () {
        assert.fail();
      });

      it('testDecryptWorksForUnknownMyDid',function () {
        assert.fail();
      });
    });

    describe('EncryptTest', function() {
      it('testRegisterWalletTypeWorks',function () {
        assert.fail();
      });

      it('testRegisterWalletTypeDoesNotWorkForTwiceWithSameName',function () {
        assert.fail();
      });

      it('testEncryptWorksForGetPkFromLedger',function () {
        assert.fail();
      });

      it('testEncryptWorksForGetNymFromLedger',function () {
        assert.fail();
      });

      it('testEncryptWorksForUnknownMyDid',function () {
        assert.fail();
      });

      it('testEncryptWorksForNotFoundNym',function () {
        assert.fail();
      });
    });

    describe('ReplaceKeysTest', function() {
      it('testReplaceKeysWorksForEmptyJson',function () {
        assert.fail();
      });

      it('testReplaceKeysWorksForInvalidDid',function () {
        assert.fail();
      });

      it('testReplaceKeysWorksForNotExistsDid',function () {
        assert.fail();
      });

      it('testReplaceKeysWorksForSeed',function () {
        assert.fail();
      });
    });

    describe('SignTest', function() {
      it('testSignWorks',function () {
        assert.fail();
      });

      it('testSignWorksForUnknowDid',function () {
        assert.fail();
      });
    });

    describe('StoreTheirDidTest', function() {
      it('testStoreTheirDidWorks',function () {
        assert.fail();
      });

      it('testCreateMyDidWorksForInvalidIdentityJson',function () {
        assert.fail();
      });

      it('testStoreTheirDidWorksWithVerkey',function () {
        assert.fail();
      });

      it('testStoreTheirDidWorksWithoutDid',function () {
        assert.fail();
      });

      it('testStoreTheirDidWorksForCorrectCryptoType',function () {
        assert.fail();
      });

      it('testStoreTheirDidWorksForInvalidCryptoType',function () {
        assert.fail();
      });
    });

    describe('VerifyTest', function() {
      it('testVerifyWorksForVerkeyCachedInWallet',function () {
        assert.fail();
      });

      it('testVerifyWorksForGetVerkeyFromLedger',function () {
        assert.fail();
      });

      it('testVerifyWorksForGetNymFromLedger',function () {
        assert.fail();
      });

      it('testVerifyWorksForOtherSigner',function () {
        assert.fail();
      });
    });
  });

  describe('Wallet', function() {
    describe('CloseWalletTest', function() {
      it('testCloseWalletWorks',function () {
        assert.fail();
      });

      it('testCloseWalletWorksForTwice',function () {
        assert.fail();
      });

      it('testCloseWalletWorksForPlugged',function () {
        assert.fail();
      });
    });

    describe('CreateWalletTest', function() {
      it('testCreateWalletWorks',function () {
        assert.fail();
      });

      it('testCreateWalletWorksForPlugged',function () {
        assert.fail();
      });

      it('testCreateWalletWorksForEmptyType',function () {
        assert.fail();
      });

      it('testCreateWalletWorksForConfigJson',function () {
        assert.fail();
      });

      it('testCreateWalletWorksForUnknowType',function () {
        assert.fail();
      });

      it('testCreateWalletWorksForEmptyName',function () {
        assert.fail();
      });

      it('testCreateWalletWorksForDuplicateName',function () {
        assert.fail();
      });
    });

    describe('DeleteWalletTest', function() {
      it('testDeleteWalletWorks',function () {
        assert.fail();
      });

      it('testDeleteWalletWorksForClosed',function () {
        assert.fail();
      });

      it('testDeleteWalletWorksForOpened',function () {
        assert.fail();
      });

        //it('@Ignore//TODO THERE IS BUG IN INDY
      it('testDeleteWalletWorksForTwice',function () {
        assert.fail();
      });

      it('testDeleteWalletWorksForPlugged',function () {
        assert.fail();
      });

      it('testDeleteWalletWorksForNotCreated',function () {
        assert.fail();
      });
    });

    describe('OpenWalletTest', function() {
      it('testOpenWalletWorks',function () {
        assert.fail();
      });

      it('testOpenWalletWorksForConfig',function () {
        assert.fail();
      });

      it('testOpenWalletWorksForPlugged',function () {
        assert.fail();
      });

      it('testOpenWalletWorksForNotCreatedWallet',function () {
        assert.fail();
      });

      it('testOpenWalletWorksForTwice',function () {
        assert.fail();
      });
    });

    describe('RegisterWalletTypeTest', function() {
      it('testRegisterWalletTypeWorks',function () {
        assert.fail();
      });

      it('testRegisterWalletTypeDoesNotWorkForTwiceWithSameName',function () {
        assert.fail();
      });

      it('customWalletWorkoutTest',function () {
        assert.fail();
      });
    });

  });

});
