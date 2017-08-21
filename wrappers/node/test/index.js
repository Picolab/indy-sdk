
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
}, {threshold: 40})

var foo = 0
var bar = setInterval(function() {
  // if (foo === 1) process.exit()
  console.log('---------------------------------- JS TIMER', foo++)
}, 5)

describe('libindy', function() {

  this.timeout(60 * 1000)

  after(function() {
    clearInterval(block_timer)
    clearInterval(foo)
  })

  // describe('bindings', function() {
  //   var funcs = Object.keys(indy)
  //   funcs.splice(funcs.indexOf('errors'), 1)

  //   funcs.forEach(function(func) {
  //     describe(func, function() {
  //       it('should throw if given no arguments', function(done) {
  //         try {
  //           indy[func]()
  //         } catch (e) {
  //           return done()
  //         }
  //         return done(new Error(`${func_name} did not throw`))
  //       })
  //     })
  //   })
  // })

  // it('create wallet', function(done) {
  //   var res = indy.create_wallet('default', 'default', null, null, null, function(err) {
  //     console.log('create_wallet callback', err)
  //   })
  //   console.log('error?', res, errors[res])
  // })

  // it('open wallet', function(done) {
  //   var res = indy.open_wallet('foo', 'foo', 'foo', function(err, handle) {
  //     console.log('open_wallet callback', err, handle)
  //   })
  //   console.log('error?', res, errors[res])
  // })

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

  // it('open pool ledger', function(done) {
  //   var res = indy.open_pool_ledger('foo', null, function(err, res) {
  //     console.log('open_pool_ledger callback', errors[err], res)
  //     done()
  //   })
  //   if (res != 0) {
  //     console.log(errors[res])
  //     return done(new Error('should not be called'))
  //   }
  // })

  // it('n pool ledger calls', function(done) {
  //   var calls = 8, responses = 0
  //   var res1 = indy.create_pool_ledger_config('foo', 'foo', function(err) {
  //     responses += 1
  //     console.log('responses', responses)
  //     if (responses === calls) return done()
  //   })
  //   var res2 = indy.open_pool_ledger('foo', 'foo', function(err, res) {
  //     responses += 1
  //     console.log('responses', responses)
  //     if (responses === calls) return done()
  //   })
  //   var res3 = indy.create_pool_ledger_config('foo', 'foo', function(err) {
  //     responses += 1
  //     console.log('responses', responses)
  //     if (responses === calls) return done()
  //   })
  //   var res4 = indy.open_pool_ledger('foo', 'foo', function(err, res) {
  //     responses += 1
  //     console.log('responses', responses)
  //     if (responses === calls) return done()
  //   })
  //   var res5 = indy.create_pool_ledger_config('foo', 'foo', function(err) {
  //     responses += 1
  //     console.log('responses', responses)
  //     if (responses === calls) return done()
  //   })
  //   var res6 = indy.open_pool_ledger('foo', 'foo', function(err, res) {
  //     responses += 1
  //     console.log('responses', responses)
  //     if (responses === calls) return done()
  //   })
  //   var res7 = indy.create_pool_ledger_config('foo', 'foo', function(err) {
  //     responses += 1
  //     console.log('responses', responses)
  //     if (responses === calls) return done()
  //   })
  //   var res8 = indy.open_pool_ledger('foo', 'foo', function(err, res) {
  //     responses += 1
  //     console.log('responses', responses)
  //     if (responses === calls) return done()
  //   })
    
  //   console.log('res1', res1, errors[res1])
  //   console.log('res2', res2, errors[res2])
  //   console.log('res3', res3, errors[res3])
  //   console.log('res4', res4, errors[res4])
  //   console.log('res5', res5, errors[res5])
  //   console.log('res6', res6, errors[res6])
  //   console.log('res7', res7, errors[res7])
  //   console.log('res8', res8, errors[res8])
  // })
})