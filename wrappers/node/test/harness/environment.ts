import * as fs from 'fs-extra'
export * from '../../src/ffi/harness'
export * from '../../src/spi/harness'

import { LibIndy,LibIndyRuntime } from '../../src'
import {
  DEBUG_LIBRARY,RELEASE_LIBRARY,RELATIVE_LIBRARY_BASE,
  canFindRelativeDebugLibrary,
  canFindRelativeReleaseLibrary
} from '../../src/ffi/harness'

export function getLibIndy(config?:any) {
  config = config || {}
  config.ffi = config.ffi || {}
  config.ffi.libraryPath = DEBUG_LIBRARY
  if(!canFindRelativeDebugLibrary) {
    throw "test/harness/environment.ts Failed to find debug library for testing, was looking for "+DEBUG_LIBRARY
  }
  return new LibIndyRuntime(config)
}
