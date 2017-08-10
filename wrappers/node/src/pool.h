
#include <napi.h>

#include <indy_types.h>
#include <indy_core.h>

#include "napi_macros.h"

void create_pool_ledger_config_on_pool_ledger_config_created(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("create_pool_ledger_config_on_pool_ledger_config_created\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void open_pool_ledger_on_pool_ledger_opened(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t pool_handle
) {
  printf("open_pool_ledger_on_pool_ledger_opened\n");
  printf("command handle %d, error %d, pool handle %d\n", command_handle, error, pool_handle);

  // TODO napi_make_callback
}

void refresh_pool_ledger_on_pool_ledger_refreshed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("refresh_pool_ledger_on_pool_ledger_refreshed\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void close_pool_ledger_on_pool_ledger_closed(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("close_pool_ledger_on_pool_ledger_closed\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void delete_pool_ledger_config_on_pool_ledger_config_deleted(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("delete_pool_ledger_config_on_pool_ledger_config_deleted\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

napi_value create_pool_ledger_config(napi_env env, napi_callback_info info) {
  /// Creates a new local pool ledger configuration that can be used later to connect pool nodes.
  ///
  /// #Params
  /// config_name: Name of the pool ledger configuration.
  /// config (optional): Pool configuration json. if NULL, then default config will be used. Example:
  /// {
  ///     "genesis_txn": string (optional), A path to genesis transaction file. If NULL, then a default one will be used.
  ///                    If file doesn't exists default one will be created.
  /// }
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Ledger*
  printf("create_pool_ledger_config\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_STRING(argv[1]);
  NAPI_ENSURE_STRING(argv[2]);
  NAPI_ENSURE_FUNCTION(argv[3]);

  indy_handle_t command_handle;
  size_t string_length, written;
  char* config_name = 0;
  char* config = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], config_name);
  NAPI_STRING_TO_UTF8(argv[2], config);

  napi_value result;
  double res = indy_create_pool_ledger_config(
    command_handle,
    config_name,
    config,
    create_pool_ledger_config_on_pool_ledger_config_created
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value open_pool_ledger(napi_env env, napi_callback_info info) {
  /// Opens pool ledger and performs connecting to pool nodes.
  ///
  /// Pool ledger configuration with corresponded name must be previously created
  /// with indy_create_pool_ledger_config method.
  /// It is impossible to open pool with the same name more than once.
  ///
  /// config_name: Name of the pool ledger configuration.
  /// config (optional): Runtime pool configuration json.
  ///                         if NULL, then default config will be used. Example:
  /// {
  ///     "refreshOnOpen": bool (optional), Forces pool ledger to be refreshed immediately after opening.
  ///                      Defaults to true.
  ///     "autoRefreshTime": int (optional), After this time in minutes pool ledger will be automatically refreshed.
  ///                        Use 0 to disable automatic refresh. Defaults to 24*60.
  ///     "networkTimeout": int (optional), Network timeout for communication with nodes in milliseconds.
  ///                       Defaults to 20000.
  /// }
  ///
  /// #Returns
  /// Handle to opened pool to use in methods that require pool connection.
  ///
  /// #Errors
  /// Common*
  /// Ledger*
  printf("open_pool_ledger\n");

  NAPI_EXPECTING_ARGS(4);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_STRING(argv[1]);
  NAPI_ENSURE_STRING(argv[2]);
  NAPI_ENSURE_FUNCTION(argv[3]);

  indy_handle_t command_handle;
  size_t string_length, written;
  char* config_name = 0;
  char* config = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], config_name);
  NAPI_STRING_TO_UTF8(argv[2], config);

  napi_value result;
  double res = indy_open_pool_ledger(
    command_handle,
    config_name,
    config,
    open_pool_ledger_on_pool_ledger_opened
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value refresh_pool_ledger(napi_env env, napi_callback_info info) {
  /// Refreshes a local copy of a pool ledger and updates pool nodes connections.
  ///
  /// #Params
  /// handle: pool handle returned by indy_open_pool_ledger
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Ledger*
  printf("refresh_pool_ledger\n");

  NAPI_EXPECTING_ARGS(3);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_NUMBER(argv[1]);
  NAPI_ENSURE_FUNCTION(argv[2]);

  indy_handle_t command_handle, pool_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);

  napi_value result;
  
  double res = indy_refresh_pool_ledger(
    command_handle,
    pool_handle,
    refresh_pool_ledger_on_pool_ledger_refreshed
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value close_pool_ledger(napi_env env, napi_callback_info info) {
  /// Closes opened pool ledger, opened nodes connections and frees allocated resources.
  ///
  /// #Params
  /// handle: pool handle returned by indy_open_pool_ledger.
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Ledger*
  printf("close_pool_ledger\n");

  NAPI_EXPECTING_ARGS(3);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_NUMBER(argv[1]);
  NAPI_ENSURE_FUNCTION(argv[2]);

  indy_handle_t command_handle, pool_handle;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);

  napi_value result;
  
  double res = indy_close_pool_ledger(
    command_handle,
    pool_handle,
    close_pool_ledger_on_pool_ledger_closed
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}

napi_value delete_pool_ledger_config(napi_env env, napi_callback_info info) {
  /// Deletes created pool ledger configuration.
  ///
  /// #Params
  /// config_name: Name of the pool ledger configuration to delete.
  ///
  /// #Returns
  /// Error code
  ///
  /// #Errors
  /// Common*
  /// Ledger*
  printf("delete_pool_ledger_config\n");
  
  NAPI_EXPECTING_ARGS(3);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_STRING(argv[1]);
  NAPI_ENSURE_FUNCTION(argv[2]);

  indy_handle_t command_handle;
  size_t string_length, written;
  char* config_name = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], config_name);

  napi_value result;

  double res = indy_delete_pool_ledger_config(
    command_handle,
    config_name,
    delete_pool_ledger_config_on_pool_ledger_config_deleted
  );

  NAPI_DOUBLE_TO_NUMBER(res, result);
  return result;
}