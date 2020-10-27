/*
 * benchmark.js
 */

const fzy = require('..')

const isEqual = require('lodash.isequal')
const fs = require('fs')
const files = fs.readFileSync(`${__dirname}/files.txt`).toString().split('\n')

run()

function run() {
  const r2 = runTest('loop-c',  () => fzy.matchPositionsMulti('f', files))
  const r1 = runTest('loop-js', () => fzy.matchPositions('f', files))
  // const r2 = runTest('one-by-one-for', () => fzy.matchPositionsFor('f', files))

  console.log(
    'Results are equal:',
    isEqual(r1, r2)
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
