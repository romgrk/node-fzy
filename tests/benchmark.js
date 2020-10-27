/*
 * benchmark.js
 */

const fzy = require('..')

const isEqual = require('lodash.isequal')
const fs = require('fs')
const files = fs.readFileSync(`${__dirname}/files.txt`).toString().split('\n')

run()

function run() {
  const r1 = runTest('one-by-one-map', () => fzy.matchPositions('f', files))
  const r2 = runTest('one-by-one-for', () => fzy.matchPositionsFor('f', files))
  const r3 = runTest('array',          () => fzy.matchPositionsMulti('f', files))

  console.log(
    'Results are equal:',
    isEqual(r1, r2) && isEqual(r1, r3)
  )
}

function runTest(name, fn) {
  // warmup
  for (let i = 0; i < 2; i++) {
    fn()
  }

  console.time(name)
  const result = fn()
  console.timeEnd(name)
  console.log([result.length])
  return result
}
