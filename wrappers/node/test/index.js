
var assert = require('assert')

var blocked = require('blocked')

var indy = require('..')
var errors = indy.errors

var block_timer = blocked(function(ms) {
  if (ms) {
    assert.fail(null, null, `event loop was blocked for ${ms} ms`)
    process.exit(1)
  }
}, {threshold: 100})

describe('libindy', function() {

  // a lot of the test cases do i/o
  this.timeout(10 * 1000)

  after(function() {
    clearInterval(block_timer)
  })

  describe('bindings', function() {
    var funcs = Object.keys(indy)
    funcs.splice(funcs.indexOf('errors'), 1)

    funcs.forEach(function(func) {
      describe(func, function() {
        it('should throw if given no arguments', function(done) {
          try {
            indy[func]()
          } catch (e) {
            return done()
          }
          return done(new Error(`${func_name} did not throw`))
        })
      })
    })
  })

  describe('agent', function() {

    describe('agent_add_identity', function() {
      it('should call back without error', function(done) {
        var listener_handle = null // TODO
        var pool_handle = null // TODO
        var wallet_handle = null // TODO
        var did = null // TODO
        var res = indy.agent_add_identity(listener_handle, pool_handle, wallet_handle, did, function(err) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('agent_close_connection', function() {
      it('should call back without error', function(done) {
        var connection_handle = null // TODO
        var res = indy.agent_close_connection(connection_handle, function(err) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('agent_close_listener', function() {
      it('should call back without error', function(done) {
        var listener_handle = null // TODO
        var res = indy.agent_close_listener(listener_handle, function(err) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('agent_connect', function() {
      it('should call back without err', function(done) {
        // test case control variables
        var calls = 2
        var resp = 0

        var pool_handle = null // TODO
        var wallet_handle = null // TODO
        var sender_did = null // TODO
        var receiver_did = null // TODO
        var res = indy.agent_connect(
          pool_handle,
          wallet_handle,
          sender_did,
          receiver_did,
          function(err, connection_handle) {
            if (err !== 0) return done(new Error(errors[err]))
            resp += 1
            if (resp == calls) return done()
          },
          function(err, connection_handle, message) {
            if (err !== 0) return done(new Error(errors[err]))
            resp += 1
            if (resp == calls) return done()
          }
        )
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('agent_listen', function() {
      it('should call back without error', function() {
        // test case control variables
        var calls = 3
        var resp = 0

        var endpoint = null // TODO
        var res = indy.agent_listen(
          endpoint,
          function(err, listener_handle) {
            if (err !== 0) return done(new Error(errors[err]))
            resp += 1
            if (resp == calls) return done()
          },
          function(err, listener_handle, connection_handle, sender_did, receiver_did) {
            if (err !== 0) return done(new Error(errors[err]))
            resp += 1
            if (resp == calls) return done()
          },
          function(err, connection_handle, message) {
            if (err !== 0) return done(new Error(errors[err]))
            resp += 1
            if (resp == calls) return done()
          }
        )
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('agent_remove_identity', function() {
      it('should call back without error', function(done) {
        var listener_handle = null // TODO
        var wallet_handle = null // TODO
        var did = null // TODO
        var res = indy.agent_remove_identity(listener_handle, wallet_handle, did, function(err) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('agent_send', function() {
      it('should call back without error', function(done) {
        var connection_handle = null // TODO
        var message = null // TODO
        var res = indy.agent_send(connection_handle, message, function(err) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })
  })

  describe('anoncreds', function() {

    describe('verifier_verify_proof', function() {

      it('should call back without error', function(done) {
        var proof_request_json = null // TODO
        var proof_json = null // TODO
        var schemas_json = null // TODO
        var claim_defs_jsons = null // TODO
        var revoc_regs_json = null // TODO
        var res = indy.verifier_verify_proof(
          proof_request_json,
          proof_json,
          schemas_json,
          claim_defs_jsons,
          revoc_regs_json,
          function(err, verified) {
            if (err !== 0) return done(new Error(errors[err]))
            return done()
          }
        )
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('prover_create_proof', function() {
      it('should call back without error', function(done) {
        var wallet_handle = null // TODO
        var proof_req_json = null // TODO
        var requested_cliams_json = null // TODO
        var schemas_json = null // TODO
        var master_secret_name = null // TODO
        var claim_defs_json = null // TODO
        var revoc_regs_json = null // TODO
        var res = indy.prover_create_proof(
          wallet_handle,
          proof_req_json,
          requested_claims_json,
          schemas_json,
          master_secret_name,
          claim_defs_json,
          revoc_regs_json,
          function(err, proof_json) {
            if (err !== 0) return done(new Error(errors[err]))
            return done()
          }
        )
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('prover_get_claims_for_proof_req', function() {
      it('should call back without error', function(done) {
        var wallet_handle = null // TODO
        var proof_request_json = null // TODO
        var res = indy.prover_get_claims_for_proof_req(
          wallet_handle,
          proof_request_json,
          function(err, claims_json) {
            if (err !== 0) return done(new Error(errors[err]))
            return done()
          }
        )
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('prover_get_claims', function() {

      it('should call back without error', function(done) {
        var wallet_handle = null // TODO
        var filter_json = null // TODO
        var res = indy.prover_get_claims(wallet_handle, filter_json, function(err, claims_json) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })
  })

  describe('ledger', function() {})

  describe('pool', function() {

    describe('create_pool_ledger_config', function() {
      
      it('should call back without error', function(done) {
        var config_name = null // TODO
        var config_json = null // TODO
        var res = indy.create_pool_ledger_config(config_name, config_json, function(err) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res != 0) return done(new Error('should not have been called'))
      })
    })

    describe('open_pool_ledger', function() {

      it('should call back without error', function(done) {
        var config_name = null // TODO
        var config_json = null // TODO
        var res = indy.open_pool_ledger(config_name, config_json, function(err, pool_handle) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('refresh_pool_ledger', function() {

      it('should call back without error', function(done) {
        var pool_handle = null // TODO
        var res = indy.refresh_pool_ledger(pool_handle, function(err) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('close_pool_ledger', function() {
      it('should call back without error', function(done) {
        var pool_handle = null // TODO
        var res = indy.close_pool_ledger(pool_handle, function(err) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })

    describe('delete_pool_ledger_config', function() {

      it('should call back without error', function(done) {
        var config_name = null // TODO
        var res = indy.delete_pool_ledger_config(config_name, function(err) {
          if (err !== 0) return done(new Error(errors[err]))
          return done()
        })
        if (res !== 0) return done(new Error(errors[err]))
      })
    })
  })

  describe('signus', function() {})

  describe('wallet', function() {})
})