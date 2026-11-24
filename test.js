const test = require('brittle')
const open = require('.')

test('app or argument with a NUL', (t) => {
  t.exception.all(() => open('bare-open-missing\0x'), TypeError)
  t.exception.all(() => open('bare-open-missing', 'x\0y'), TypeError)
})
