export {
  ErrorCode,IndyError,errname
} from '../../src'
import {
  ErrorCode,IndyError,errname
} from '../../src'
export { describe,it,before,after,beforeEach,afterEach } from 'mocha'
export * from './chai'
export * from './environment'

export function assert_indy_error(promise:any,error_code:ErrorCode) : Promise<any> {
  return promise.should.be.rejectedWith(IndyError).and.eventually.have.property('label',errname(error_code))
}
