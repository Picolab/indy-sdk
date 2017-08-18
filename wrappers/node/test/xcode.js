
var indy = require('..')

var foo = 0
var bar = setInterval(function() {
  // if (foo === 1) process.exit()
  console.log('---------------------------------- JS TIMER', foo++)
}, 5)

var res = indy.create_pool_ledger_config('foo', 'foo', function(err) {
  console.log('====================== calling back', indy.errors[err])
})

console.log('========================= JS', indy.errors[res])
