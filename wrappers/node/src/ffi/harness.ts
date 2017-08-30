import * as fs from 'fs-extra'
import { logger } from '../../test/harness/logging'

export const RELATIVE_LIBRARY_BASE="test/fixtures/relative"
export const RELEASE_LIBRARY      =RELATIVE_LIBRARY_BASE + "/rustlib/release/libindy.dylib"
export const DEBUG_LIBRARY        =RELATIVE_LIBRARY_BASE + "/rustlib/debug/libindy.dylib"

export async function canFindRelativeDebugLibrary() {
  try {
    return await fs.pathExistsSync(DEBUG_LIBRARY)
  }
  catch(error) {
    logger.error("Failed to locate debug library, path=",DEBUG_LIBRARY,error)
    return false;
  }
}

export async function canFindRelativeReleaseLibrary() {
  try {
    return await fs.pathExistsSync(RELEASE_LIBRARY)
  }
  catch(error) {
    logger.error("Failed to locate release library, path=",RELEASE_LIBRARY,error)
    return false;
  }
}
