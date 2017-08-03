
var assert = require('assert')

var blocked = require('blocked')

var indy = require('..')

var block_timer = blocked(function(ms) {
  if (ms) {
    assert.fail(null, null, 'event loop was blocked for ' + ms + ' ms')
    process.exit(1)
  }
}, {threshold: 60})