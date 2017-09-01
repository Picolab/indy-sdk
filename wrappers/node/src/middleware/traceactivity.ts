
import {
  libindy_middleware,
  libindy_middleware_context,
  create_pool_ledger_config_options,
  open_pool_ledger_options,
  wallet_type_definition,
  rust_connection_handle,
  rust_listener_handle,
  rust_command_handle,
  rust_wallet_handle,
  rust_pool_handle,
  rust_did,
  agent_message_callback_type,
  agent_connection_callback_type
} from '../bridge'

import { NotYetImplemented } from './util'

export class DebugTrace extends NotYetImplemented implements libindy_middleware {
  readonly logger:any
  constructor(config?:any) {
    super()
    this.logger = config.logger
  }

  private trace(...args) : void {
    this.logger.debug(...args)
  }

  // pool.rs
  create_pool_ledger_config(ctx:libindy_middleware_context,configuration_name:string,config_data:create_pool_ledger_config_options) : Promise<void> {
    this.trace("create_pool_ledger_config",configuration_name,config_data);
    const resolve = (...args) => {
      this.trace("create_pool_ledger_config - resolved",...args)
    }
    const reject = (...args) => {
      this.trace("create_pool_ledger_config - rejected",...args)
    }
    return ctx.advance(resolve,reject).create_pool_ledger_config(ctx,configuration_name,config_data)
    }


}
