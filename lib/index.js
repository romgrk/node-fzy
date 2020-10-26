/*
 * index.js
 */

const native = require('./native')

console.log(native)

function hasMatch(needle, haystack) {
  if (Array.isArray(haystack))
    return haystack.map(h => native.hasMatch(needle, h))
  return native.hasMatch(needle, haystack)
}

function match(needle, haystack) {
  if (Array.isArray(haystack))
    return haystack.map(h => native.match(needle, h))
  return native.match(needle, haystack)
}

function matchPositions(needle, haystack) {
  if (Array.isArray(haystack))
    return haystack.map(h => native.matchPositions(needle, h))
  return native.matchPositions(needle, haystack)
}

module.exports = { hasMatch, match, matchPositions }
