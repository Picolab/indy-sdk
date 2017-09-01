
import {
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
  agent_connection_callback_type,
  libindy_middleware,
  libindy_middleware_context,
} from '../bridge'

import { NotYetImplemented } from './util'

class Metrics {
}

export class CollectMetrics extends NotYetImplemented implements libindy_middleware {

  private metrics:any = {}

  constructor(config?:any) {
    super()
    this.metrics = {}
  }

  private trace(...args) : void {
    console.log(...args)
  }

  // pool.rs
  create_pool_ledger_config(ctx:libindy_middleware_context,configuration_name:string,config_data:create_pool_ledger_config_options) : Promise<void> {
    this.trace("METRICS:create_pool_ledger_config");
    const resolve = (...args) => {
      this.trace("METRICS:create_pool_ledger_config - resolved",...args)
    }
    const reject = (...args) => {
      this.trace("METRICS:create_pool_ledger_config - rejected",...args)
    }
    return ctx.advance(resolve,reject).create_pool_ledger_config(ctx,configuration_name,config_data)
    }


}
