
#include <napi.h>

#include <indy_types.h>
#include <indy_core.h>

#include "napi_macros.h"

void agent_connect_on_connect(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t connection_handle
) {
  // invoke user callback mapped to command_handle
  printf("agent_connect_on_connect\n");
  printf(
    "command handle %d, error %d, connection handle %d\n",
    command_handle,
    error,
    connection_handle
  );

  // TODO napi_make_callback
}

void agent_connect_on_message(
  indy_handle_t connection_handle,
  indy_error_t error,
  const char* message
) {
  printf("agent_connect_on_message\n");
  printf(
    "connection handle %d, error %d, message %s\n",
    connection_handle,
    error,
    message
  );
  
  // TODO napi_make_callback
}

void agent_listen_on_listening(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_handle_t listener_handle
) {
  printf("agent_listen_on_listening\n");
  printf(
    "command handle %d, error %d, listener handle %d\n",
    command_handle,
    error,
    listener_handle
  );

  // TODO napi_make_callback
}

void agent_listen_on_connection(
  indy_handle_t listener_handle,
  indy_error_t error,
  indy_handle_t connection_handle,
  const char* sender_did,
  const char* receiver_did
) {
  printf("agent_listen_on_connection\n");
  printf(
    "listener handle %d, error %d, connection handle %d, sender did %s, receiver did %s\n",
    listener_handle,
    error,
    connection_handle,
    sender_did,
    receiver_did
  );
  
  // TODO napi_make_callback
}

void agent_listen_on_message(
  indy_handle_t connection_handle,
  indy_error_t error,
  const char* message
) {
  printf("agent_listen_on_message\n");
  printf("connection handle %d, error %d, message %s\n", connection_handle, error, message);

  // TODO napi_make_callback
}

void agent_add_identity_on_identity_added(indy_handle_t command_handle, indy_error_t error) {
  printf("agent_add_identity_on_identity_added\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void agent_remove_identity_on_identity_removed(indy_handle_t command_handle, indy_error_t error) {
  printf("agent_remove_identity_on_identity_removed\n");
  printf("command handle %d, error %d\n", command_handle, error);
  
  // TODO napi_make_callback
}

void agent_send_on_message_sent(indy_handle_t command_handle, indy_error_t error) {
  printf("agent_send_on_message_sent\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

napi_value agent_add_identity(napi_env env, napi_callback_info info) {
  printf("agent_add_identity\n");

  NAPI_EXPECTING_ARGS(6);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_NUMBER(argv[1]);
  NAPI_ENSURE_NUMBER(argv[2]);
  NAPI_ENSURE_NUMBER(argv[3]);
  NAPI_ENSURE_STRING(argv[4]);
  NAPI_ENSURE_FUNCTION(argv[5]);

  indy_handle_t command_handle, listener_handle, pool_handle, wallet_handle;
  size_t string_length, written;
  char* did = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], listener_handle);
  NAPI_NUMBER_TO_INT32(argv[2], pool_handle);
  NAPI_NUMBER_TO_INT32(argv[3], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[4], did);

  // TODO store ref to user callback(s) and heap allocate a data context

  double res = indy_agent_add_identity(
    command_handle,
    listener_handle,
    pool_handle,
    wallet_handle,
    did,
    agent_add_identity_on_identity_added
  );

  napi_value result;
  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value agent_close_connection(napi_env env, napi_callback_info info) {
  printf("agent_close_connection\n");
  return NULL;
}

napi_value agent_close_listener(napi_env env, napi_callback_info info) {
  printf("agent_close_listener\n");
  return NULL;
}

napi_value agent_connect(napi_env env, napi_callback_info info) {
  printf("agent_connect\n");
  
  NAPI_EXPECTING_ARGS(7);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_NUMBER(argv[1]);
  NAPI_ENSURE_NUMBER(argv[2]);
  NAPI_ENSURE_STRING(argv[3]);
  NAPI_ENSURE_STRING(argv[4]);
  NAPI_ENSURE_FUNCTION(argv[5]);
  NAPI_ENSURE_FUNCTION(argv[6]);

  indy_handle_t command_handle, pool_handle, wallet_handle;
  size_t string_length, written;
  char* sender_did = 0;
  char* receiver_did = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], pool_handle);
  NAPI_NUMBER_TO_INT32(argv[2], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[3], sender_did);
  NAPI_STRING_TO_UTF8(argv[4], receiver_did);

  // TODO store ref to user callback(s) and heap allocate a data context

  double res = indy_agent_connect(
    command_handle,
    pool_handle,
    wallet_handle,
    sender_did,
    receiver_did,
    agent_connect_on_connect,
    agent_connect_on_message
  );
  napi_value result;
  NAPI_DOUBLE_TO_NUMBER(res, result);
  // double to_convert = res;
  // status = napi_create_number(env, to_convert, &result);
  // NAPI_CHECK_STATUS("napi_create_number");
  return result;
}

napi_value agent_listen(napi_env env, napi_callback_info info) {
  printf("agent_listen\n");

  NAPI_EXPECTING_ARGS(5);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_STRING(argv[1]);
  NAPI_ENSURE_FUNCTION(argv[2]);
  NAPI_ENSURE_FUNCTION(argv[3]);
  NAPI_ENSURE_FUNCTION(argv[4]);

  indy_handle_t command_handle;
  size_t string_length, written;
  char* endpoint = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_STRING_TO_UTF8(argv[1], endpoint);

  // TODO store ref to user callback(s) and heap allocate a data context

  double res = indy_agent_listen(
    command_handle,
    endpoint,
    agent_listen_on_listening,
    agent_listen_on_connection,
    agent_listen_on_message
  );
  
  napi_value result;
  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value agent_remove_identity(napi_env env, napi_callback_info info) {
  printf("agent_remove_identity\n");

  NAPI_EXPECTING_ARGS(5);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_NUMBER(argv[1]);
  NAPI_ENSURE_NUMBER(argv[2]);
  NAPI_ENSURE_STRING(argv[3]);
  NAPI_ENSURE_FUNCTION(argv[4]);

  indy_handle_t command_handle, listener_handle, wallet_handle;
  size_t string_length, written;
  char* did = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], listener_handle);
  NAPI_NUMBER_TO_INT32(argv[2], wallet_handle);
  NAPI_STRING_TO_UTF8(argv[3], did);

  double res = indy_agent_remove_identity(
    command_handle,
    listener_handle,
    wallet_handle,
    did,
    agent_remove_identity_on_identity_removed
  );

  napi_value result;
  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}

napi_value agent_send(napi_env env, napi_callback_info info) {
  printf("agent_send\n");
  /// Sends message to connected agent.
  ///
  /// Note that this call works for both incoming and outgoing connections.
  /// Note that messages encryption/decryption will be performed automatically.
  ///
  /// #Params
  /// command_handle: command handle to map callback to caller context.
  /// connection_handle: Connection handle returned by indy_agent_connect or indy_agent_listen calls.
  /// message: Message to send.
  /// cb: Callback that will be called after message sent or on error. Will be called exactly once.
  ///
  /// #Returns
  /// err: Error code
  /// cb:
  /// - xcommand_handle: Command handle to map callback to caller context.
  /// - err: Error code
  ///
  /// #Errors

  NAPI_EXPECTING_ARGS(4);

  NAPI_ENSURE_NUMBER(argv[0]);
  NAPI_ENSURE_NUMBER(argv[1]);
  NAPI_ENSURE_STRING(argv[2]);
  NAPI_ENSURE_FUNCTION(argv[3]);

  indy_handle_t command_handle, connection_handle;
  size_t string_length, written;
  char* message = 0;

  NAPI_NUMBER_TO_INT32(argv[0], command_handle);
  NAPI_NUMBER_TO_INT32(argv[1], connection_handle);
  NAPI_STRING_TO_UTF8(argv[2], message);

  double res = indy_agent_send(
    command_handle,
    connection_handle,
    message,
    agent_send_on_message_sent
  );

  napi_value result;
  NAPI_DOUBLE_TO_NUMBER(res, result);

  return result;
}