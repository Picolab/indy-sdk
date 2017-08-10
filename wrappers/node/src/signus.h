
#include <napi.h>

#include <indy_types.h>
#include <indy_core.h>

#include "napi_macros.h"

void decrypt_on_decrypted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* decrypted
) {
  printf("decrypt_on_decrypted\n");
  printf("command handle %d, error %d, decrypted %s\n", command_handle, error, decrypted);

  // TODO napi_make_callback
}

void encrypt_on_encrypted(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* encrypted,
  const char* nonce
) {
  printf("encrypt_on_encrypted\n");
  printf("command handle %d, error %d, encrypted %s, nonce %s\n", command_handle, error, encrypted, nonce);

  // TODO napi_make_callback
}

void verify_signature_on_verified(
  indy_handle_t command_handle,
  indy_error_t error,
  indy_bool_t verified
) {
  printf("verify_signature_on_verified\n");
  printf("command handle %d, error %d, verified %d\n", command_handle, error, verified);

  // TODO napi_make_callback
}

void sign_on_signed(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* signature
) {
  printf("sign_on_signed\n");
  printf("command handle %d, error %d, signature %s\n", command_handle, error, signature);

  // TODO napi_make_callback
}

void store_their_did_on_their_did_stored(
  indy_handle_t command_handle,
  indy_error_t error
) {
  printf("store_their_did_on_their_did_stored\n");
  printf("command handle %d, error %d\n", command_handle, error);

  // TODO napi_make_callback
}

void replace_keys_on_keys_replaced(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* signing_key,
  const char* encryption_key
) {
  printf("replace_keys_on_keys_replaced\n");
  printf("command handle %d, error %d, signing key %s, encryption key %s\n", command_handle, error, signing_key, encryption_key);

  // TODO napi_make_callback
}

void create_and_store_my_did_on_my_did_created_and_stored(
  indy_handle_t command_handle,
  indy_error_t error,
  const char* did,
  const char* signing_key,
  const char* encryption_key
) {
  printf("create_and_store_my_did_on_my_did_created_and_stored\n");
  printf("command handle %d, error %d, did %s, signing key %s, encryption key %s\n", command_handle, error, did, signing_key, encryption_key);

  // TODO napi_make_callback
}

napi_value decrypt(napi_env env, napi_callback_info info) {
  /// Decrypts a message encrypted by a public key associated with my DID.
  /// The DID with a secret key must be already created and
  /// stored in a secured wallet (see wallet_create_and_store_my_identity)
  ///
  /// #Params
  /// wallet_handle: wallet handler (created by open_wallet).
  /// command_handle: command handle to map callback to user context.
  /// my_did: DID
  /// did: DID that signed the message
  /// encrypted_msg: encrypted message
  /// nonce: nonce that encrypted message
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// decrypted message
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  /// Crypto*
  printf("decrypt\n");
  return NULL;
}

napi_value encrypt(napi_env env, napi_callback_info info) {
  /// Encrypts a message by a public key associated with a DID.
  /// If a secure wallet doesn't contain a public key associated with the given DID,
  /// then the public key is read from the Ledger.
  /// Otherwise either an existing public key from wallet is used (see wallet_store_their_identity),
  /// or it checks the Ledger (according to freshness settings set during initialization)
  /// whether public key is still the same and updates public key for the DID if needed.
  ///
  /// #Params
  /// wallet_handle: wallet handler (created by open_wallet).
  /// command_handle: command handle to map callback to user context.
  /// my_did: encrypting DID
  /// did: encrypting DID
  /// msg: a message to be signed
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// an encrypted message and nonce
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  /// Ledger*
  /// Crypto*
  printf("encrypt\n");
  return NULL;
}

napi_value verify_signature(napi_env env, napi_callback_info info) {
  /// Verify a signature created by a key associated with a DID.
  /// If a secure wallet doesn't contain a verkey associated with the given DID,
  /// then verkey is read from the Ledger.
  /// Otherwise either an existing verkey from wallet is used (see wallet_store_their_identity),
  /// or it checks the Ledger (according to freshness settings set during initialization)
  /// whether verkey is still the same and updates verkey for the DID if needed.
  ///
  /// #Params
  /// wallet_handle: wallet handler (created by open_wallet).
  /// command_handle: command handle to map callback to user context.
  /// pool_handle: pool handle.
  /// did: DID that signed the message
  /// signature: a signature to be verified
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// valid: true - if signature is valid, false - otherwise
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  /// Ledger*
  /// Crypto*
  printf("verify_signature\n");
  return NULL;
}

napi_value sign(napi_env env, napi_callback_info info) {
  /// Signs a message by a signing key associated with my DID. The DID with a signing key
  /// must be already created and stored in a secured wallet (see create_and_store_my_identity)
  ///
  /// #Params
  /// wallet_handle: wallet handler (created by open_wallet).
  /// command_handle: command handle to map callback to user context.
  /// did: signing DID
  /// msg: a message to be signed
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// a signature string
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  /// Crypto*
  printf("sign\n");
  return NULL;
}

napi_value store_their_did(napi_env env, napi_callback_info info) {
  /// Saves their DID for a pairwise connection in a secured Wallet,
  /// so that it can be used to verify transaction.
  ///
  /// #Params
  /// wallet_handle: wallet handler (created by open_wallet).
  /// command_handle: command handle to map callback to user context.
  /// identity_json: Identity information as json. Example:
  ///     {
  ///        "did": string, (required)
  ///        "verkey": string (optional, if only pk is provided),
  ///        "pk": string (optional, if only verification key is provided),
  ///        "crypto_type": string, (optional; if not set then ed25519 curve is used;
  ///               currently only 'ed25519' value is supported for this field)
  ///     }
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// None
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  /// Crypto*
  printf("store_their_did\n");
  return NULL;
}

napi_value replace_keys(napi_env env, napi_callback_info info) {
  /// Generated new keys (signing and encryption keys) for an existing
  /// DID (owned by the caller of the library).
  ///
  /// #Params
  /// wallet_handle: wallet handler (created by open_wallet).
  /// command_handle: command handle to map callback to user context.
  /// identity_json: Identity information as json. Example:
  /// {
  ///     "seed": string, (optional; if not provide then a random one will be created)
  ///     "crypto_type": string, (optional; if not set then ed25519 curve is used;
  ///               currently only 'ed25519' value is supported for this field)
  /// }
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// verkey (for verification of signature) and public_key (for decryption)
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  /// Crypto*
  printf("replace_keys\n");
  return NULL;
}

napi_value create_and_store_my_did(napi_env env, napi_callback_info info) {
  /// Creates keys (signing and encryption keys) for a new
  /// DID (owned by the caller of the library).
  /// Identity's DID must be either explicitly provided, or taken as the first 16 bit of verkey.
  /// Saves the Identity DID with keys in a secured Wallet, so that it can be used to sign
  /// and encrypt transactions.
  ///
  /// #Params
  /// wallet_handle: wallet handler (created by open_wallet).
  /// command_handle: command handle to map callback to user context.
  /// did_json: Identity information as json. Example:
  /// {
  ///     "did": string, (optional; if not provided then the first 16 bit of the verkey will be used
  ///             as a new DID; if provided, then keys will be replaced - key rotation use case)
  ///     "seed": string, (optional; if not provide then a random one will be created)
  ///     "crypto_type": string, (optional; if not set then ed25519 curve is used;
  ///               currently only 'ed25519' value is supported for this field)
  /// }
  /// cb: Callback that takes command result as parameter.
  ///
  /// #Returns
  /// DID, verkey (for verification of signature) and public_key (for decryption)
  ///
  /// #Errors
  /// Common*
  /// Wallet*
  /// Crypto*
  printf("create_and_store_my_did\n");
  return NULL;
}