
#include <napi.h>

#include <indy_types.h>
#include <indy_core.h>

#include "napi_macros.h"

void register_wallet_type_on_created(
  const char* name,
  const char* config,
  const char* credentials
) {
  printf("register_wallet_type_on_created\n");
  printf("name %s, config %s, credentials %s\n", name, config, credentials);

  // TODO napi_make_callback
}

void register_wallet_type_on_opened(
  const char* name,
  const char* config,
  const char* runtime_config,
  const char* credentials,
  indy_handle_t* handle
) {
  printf("register_wallet_type_on_opened\n");
  printf(
    "name %s, config %s, runtime config %s, credentials %s, handle %d\n",
    name, config, runtime_config, credentials, *(handle)
  );

  // TODO napi_make_callback
}

void register_wallet_type_on_set(
  indy_handle_t handle,
  const char* key,
  const char* value
) {
  printf("register_wallet_type_on_set\n");
  printf("handle %d, key %s, value %s\n", handle, key, value);

  // TODO napi_make_callback
}

void register_wallet_type_on_get(
  indy_handle_t handle,
  const char* key,
  const char* const *value_ptr
) {
  printf("register_wallet_type_on_get\n");
  printf("handle %d, key %s, value %s\n", handle, key, *(value_ptr));

  // TODO napi_make_callback
}

void register_wallet_type_on_got_not_expired(
  indy_handle_t handle,
  const char* key,
  const char *const *value_ptr
) {
  printf("register_wallet_type_on_got_not_expired\n");
  printf("handle %d, key %s, value %s\n", handle, key, *(value_ptr));
  
  // TODO napi_make_callback
}

void register_wallet_type_on_listed(
  indy_handle_t handle,
  const char* key,
  const char *const *values_json_ptr
) {
  printf("register_wallet_type_on_listed\n");
  printf("handle %d, key %s, values json %s\n", handle, key, *(values_json_ptr));

  // TODO napi_make_callback
}

void register_wallet_type_on_closed(
  indy_handle_t handle
) {
  printf("register_wallet_type_on_closed\n");
  printf("handle %d\n", handle);

  // TODO napi_make_callback
}

void register_wallet_type_on_deleted(
  const char* name,
  const char* config,
  const char* credentials
) {
  printf("register_wallet_type_on_deleted\n");
  printf("name %s, config %s, credentials %s\n", name, config, credentials);

  // TODO napi_make_callback
}

void register_wallet_type_on_freed(
  indy_handle_t handle,
  const char* str
) {
  printf("register_wallet_type_on_freed\n");
  printf("handle %d, str %s\n", handle, str);

  // TODO napi_make_callback
}

void create_wallet_on_wallet_created(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("create_wallet_on_wallet_created\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void open_wallet_on_wallet_opened(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t wallet_handle
) {
  printf("open_wallet_on_wallet_opened\n");
  printf("command handle %d, error %d, wallet handle %d\n", command_handle, error, wallet_handle);

  // TODO napi_make_callback
}

void close_wallet_on_wallet_closed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("close_wallet_on_wallet_closed\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void delete_wallet_on_wallet_deleted(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("delete_wallet_on_wallet_deleted\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

napi_value register_wallet_type(napi_env env, napi_callback_info info) {
  /// Registers custom wallet implementation.
  ///
  /// It allows library user to provide custom wallet implementation.
  ///
  /// #Params
  /// command_handle: Command handle to map callback to caller context.
  /// xtype: Wallet type name.
  /// create: WalletType create operation handler
  /// open: WalletType open operation handler
  /// set: Wallet set operation handler
  /// get: Wallet get operation handler
  /// get_not_expired: Wallet get_not_expired operation handler
  /// list: Wallet list operation handler
  /// close: Wallet close operation handler
  /// delete: WalletType delete operation handler
  /// free: Handler that allows to de-allocate strings allocated in caller code
  ///
  /// #Returns
  /// Error code
  printf("register_wallet_type\n");
  return NULL;
}

napi_value create_wallet(napi_env env, napi_callback_info info) {
  /// Creates a new secure wallet with the given unique name.
  ///
  /// #Params
  /// pool_name: Name of the pool that corresponds to this wallet.
  /// name: Name of the wallet.
  /// xtype(optional): Type of the wallet. Defaults to 'default'.
  ///                  Custom types can be registered with indy_register_wallet_type call.
  /// config(optional): Wallet configuration json. List of supported keys are defined by wallet type.
  ///                    if NULL, then default config will be used.
  /// credentials(optional): Wallet credentials json. List of supported keys are defined by wallet type.
  ///                    if NULL, then default config will be used.
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  printf("create_wallet\n");
  return NULL;
}

napi_value open_wallet(napi_env env, napi_callback_info info) {
  /// Opens the wallet with specific name.
  ///
  /// Wallet with corresponded name must be previously created with indy_create_wallet method.
  /// It is impossible to open wallet with the same name more than once.
  ///
  /// #Params
  /// name: Name of the wallet.
  /// runtime_config (optional): Runtime wallet configuration json. if NULL, then default runtime_config will be used. Example:
  /// {
  ///     "freshnessTime": string (optional), Amount of minutes to consider wallet value as fresh. Defaults to 24*60.
  ///     ... List of additional supported keys are defined by wallet type.
  /// }
  /// credentials(optional): Wallet credentials json. List of supported keys are defined by wallet type.
  ///                    if NULL, then default credentials will be used.
  ///
  /// #Returns
  /// Handle to opened wallet to use in methods that require wallet access.
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  printf("open_wallet\n");
  return NULL;
}

napi_value close_wallet(napi_env env, napi_callback_info info) {
  /// Closes opened wallet and frees allocated resources.
  ///
  /// #Params
  /// handle: wallet handle returned by indy_open_wallet.
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  printf("close_wallet\n");
  return NULL;
}

napi_value delete_wallet(napi_env env, napi_callback_info info) {
  /// Deletes created wallet.
  ///
  /// #Params
  /// name: Name of the wallet to delete.
  /// credentials(optional): Wallet credentials json. List of supported keys are defined by wallet type.
  ///                    if NULL, then default credentials will be used.
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  printf("delete_wallet\n");
  return NULL;
}