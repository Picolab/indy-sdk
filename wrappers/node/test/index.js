
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

  this.timeout(60 * 1000)

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

  it('concurrency', function(done) {
    var calls = 2
    var returned = 0
    
    var a = indy.create_pool_ledger_config('foo', 'foo', function(err) {
      returned += 1
      console.log('====================== calling from', returned, errors[err])
      if (returned == calls) return done()
    })
    if (a > 0) return done(new Error('create_pool_ledger_config failed'))
    
      var b = indy.open_pool_ledger('foo', 'foo', function(err, res) {
      returned += 1
      console.log('====================== calling from', returned, errors[err], res)
      if (returned == calls) return done()
    })
    if (b > 0) return done(new Error('open_pool_ledger failed'))
  })
})