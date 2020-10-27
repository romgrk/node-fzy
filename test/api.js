/*
 * api.js
 */
/* global describe, it, expect */

const fzy = require('..')

describe('.hasMatch', () => {
  it('respects case sensitivity', () => {
    expect(fzy.hasMatch('fi', '_f__i_')).toBe(true)
    expect(fzy.hasMatch('fi', '_F__i_')).toBe(true)
    expect(fzy.hasMatch('Fi', '_F__i_')).toBe(true)
    expect(fzy.hasMatch('Fi', '_f__i_')).toBe(false)

    expect(fzy.hasMatch('a', '___a')).toBe(true)
    expect(fzy.hasMatch('a', '___A')).toBe(true)
    expect(fzy.hasMatch('A', '___A')).toBe(true)
    expect(fzy.hasMatch('A', '___a')).toBe(false)
  })
})

describe('.match', () => {
  it('respects case sensitivity', () => {
    expect(fzy.match('fi', '_f__i_')).toBeGreaterThan(0)
    expect(fzy.match('fi', '_F__i_')).toBeGreaterThan(0)
    expect(fzy.match('Fi', '_F__i_')).toBeGreaterThan(0)
    expect(fzy.match('Fi', '_f__i_')).toBe(-Infinity)
  })
})

describe('.matchPositions', () => {
  it('respects case sensitivity', () => {
    expect(fzy.matchPositions('fi', '_f__i_')[1]).toEqual([1, 4])
    expect(fzy.matchPositions('fi', '_F__i_')[1]).toEqual([1, 4])
    expect(fzy.matchPositions('Fi', '_F__i_')[1]).toEqual([1, 4])
    expect(fzy.matchPositions('Fi', '_f__i_')[0]).toEqual(-Infinity)
  })
})

// Multi

describe('.hasMatchMulti', () => {
  it('respects case sensitivity', () => {
    expect(fzy.hasMatchMulti('fi', ['_f__i_'])[0]).toBe(true)
    expect(fzy.hasMatchMulti('fi', ['_F__i_'])[0]).toBe(true)
    expect(fzy.hasMatchMulti('Fi', ['_F__i_'])[0]).toBe(true)
    expect(fzy.hasMatchMulti('Fi', ['_f__i_'])[0]).toBe(false)

    expect(fzy.hasMatchMulti('a', ['___a'])[0]).toBe(true)
    expect(fzy.hasMatchMulti('a', ['___A'])[0]).toBe(true)
    expect(fzy.hasMatchMulti('A', ['___A'])[0]).toBe(true)
    expect(fzy.hasMatchMulti('A', ['___a'])[0]).toBe(false)
  })
})

describe('.matchMulti', () => {
  it('respects case sensitivity', () => {
    expect(fzy.matchMulti('fi', ['_f__i_'])[0]).toBeGreaterThan(0)
    expect(fzy.matchMulti('fi', ['_F__i_'])[0]).toBeGreaterThan(0)
    expect(fzy.matchMulti('Fi', ['_F__i_'])[0]).toBeGreaterThan(0)
    expect(fzy.matchMulti('Fi', ['_f__i_'])[0]).toBe(-Infinity)
  })
})

describe('.matchPositionsMulti', () => {
  it('respects case sensitivity', () => {
    expect(fzy.matchPositionsMulti('fi', ['_f__i_'])[0][1]).toEqual([1, 4])
    expect(fzy.matchPositionsMulti('fi', ['_F__i_'])[0][1]).toEqual([1, 4])
    expect(fzy.matchPositionsMulti('Fi', ['_F__i_'])[0][1]).toEqual([1, 4])
    expect(fzy.matchPositionsMulti('Fi', ['_f__i_'])[0][0]).toEqual(-Infinity)
  })
})
