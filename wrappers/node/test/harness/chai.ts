// configure to support sync/async functions - this requires import of
// assert,expect from this file.
//
// make sure that assert and expect are imported from test/harness as part
// of any test setup.
//
// this is accomplished by the convention of
//
// import { expect,assert } from '../harness' in the test/tests/**/*.ts files
//
import * as chai from 'chai'
import * as chaiAsPromised from 'chai-as-promised'
var chai = require('chai');
var chaiAsPromised = require('chai-as-promised');
chai.use(chaiAsPromised);

export const expect = chai.expect
export const assert = chai.assert
chai.should()
