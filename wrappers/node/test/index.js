
var assert = require('assert')

var blocked = require('blocked')

var indy = require('..')
var errors = indy.errors

var block_timer = blocked(function(ms) {
  if (ms) {
    assert.fail(null, null, 'event loop was blocked for ' + ms + ' ms')
    process.exit(1)
  }
}, {threshold: 60})

var noop = function() {}
var did = '00000000000000000000000'

console.log(errors[indy.agent_remove_identity(0, 0, 0, did, noop)])