
import { IndyError,ErrorCode } from '../error'
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

export class ValidationError extends IndyError {
  private readonly method:string
  private readonly detail:string
  constructor(method:string,detail:string) {
    super(ErrorCode.CommonInvalidStructure)
    this.detail = detail
    this.method = method
    this.message = "Parameter Validation Error : method=" + this.method + ", desc=" + this.detail
  }

}

export class ValidateParameters extends NotYetImplemented implements libindy_middleware {
  constructor(config?:any) {
    super()
  }

  // pool.rs
  create_pool_ledger_config(ctx:libindy_middleware_context,configuration_name:string,config_data:create_pool_ledger_config_options) : Promise<void> {
    if(configuration_name === undefined) {
      return Promise.reject(new ValidationError("create_pool_ledger_config","configuration_name can not be undefined"))
    }
    return ctx.advance().create_pool_ledger_config(ctx,configuration_name,config_data)
    }


}
