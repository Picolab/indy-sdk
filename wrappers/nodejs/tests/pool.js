var test = require('ava')
var indy = require('../').promise
var makeTestPool = require('./helpers/makeTestPool')

test('pool', async function (t) {
  var err = await t.throws(indy.create_pool_ledger_config())
  t.is(err.message, 'Expected 3 arguments: create_pool_ledger_config(config_name, config, cb(err))')

  err = await t.throws(indy.create_pool_ledger_config('', ''))
  t.is(err + '', 'IndyError: CommonInvalidParam2')

  err = await t.throws(indy.create_pool_ledger_config('not_a_real_pool', JSON.stringify({
    'genesis_txn': '/not/a/real/file.txn'
  })))
  t.is(err + '', 'IndyError: CommonIOError')

  var pool = await makeTestPool()
  t.is(await indy.create_pool_ledger_config(pool.name, JSON.stringify({
    'genesis_txn': pool.file
  })), void 0)

  var poolH = await indy.open_pool_ledger(pool.name, 'null')
  t.truthy(poolH >= 0)

  err = await t.throws(indy.delete_pool_ledger_config(pool.name))
  t.is(err + '', 'IndyError: CommonInvalidState')

  await indy.close_pool_ledger(poolH)

  await indy.delete_pool_ledger_config(pool.name)

  pool.cleanup()
})