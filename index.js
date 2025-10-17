const binding = require('./binding')

module.exports = function open(app, argument = null) {
  if (argument !== null) {
    binding.open(app, argument)
  } else {
    binding.open(app)
  }
}
