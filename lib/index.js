/*
 * index.js
 */

const native = require('./native')

function hasMatch(needle, haystack) {
  const isCaseSensitive = hasUppercase(needle)
  if (Array.isArray(haystack))
    return haystack.map(h => native.hasMatch(needle, h, isCaseSensitive))
  return native.hasMatch(needle, haystack, isCaseSensitive)
}

function match(needle, haystack) {
  const isCaseSensitive = hasUppercase(needle)
  if (Array.isArray(haystack))
    return haystack.map(h => native.match(needle, h, isCaseSensitive))
  return native.match(needle, haystack, isCaseSensitive)
}

function matchPositions(needle, haystack) {
  const isCaseSensitive = hasUppercase(needle)
  console.log('sens', isCaseSensitive)
  if (Array.isArray(haystack))
    return haystack.map(h => native.matchPositions(needle, h, isCaseSensitive))
  return native.matchPositions(needle, haystack, isCaseSensitive)
}

module.exports = {
  ...native,
  hasMatch,
  match,
  matchPositions,
}

// Helpers

function hasUppercase(s) {
  return s.toLowerCase() !== s
}

