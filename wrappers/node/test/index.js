
var assert = require('assert')

var blocked = require('blocked')

var indy = require('..')
var errors = indy.errors

// remove errors to avoid iterating over the key
delete indy.errors

var block_timer = blocked(function(ms) {
  if (ms) {
    assert.fail(null, null, `event loop was blocked for ${ms} ms`)
    process.exit(1)
  }
}, {threshold: 60})

describe('libindy', function() {

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
})