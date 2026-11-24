const binding = require('./binding')

module.exports = function open(app, argument = null) {
  validateNoNullBytes(app, 'app')

  if (argument !== null) {
    validateNoNullBytes(argument, 'argument')

    binding.open(app, argument)
  } else {
    binding.open(app)
  }
}

// The arguments are passed on as C strings, so a NUL would cut them short.
function validateNoNullBytes(value, name) {
  if (value.includes('\0')) {
    throw new TypeError(`The "${name}" argument must not contain null bytes`)
  }
}
