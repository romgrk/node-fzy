
# node-fzy

Node.js binding to the original C fzy.

### Install

Requires a compiler.

```
npm install node-fzy
```

### API

```typescript
// Returns if there is a match
fzy.hasMatch(needle: String, haystack: String|String[]): Boolean
// Returns the score
fzy.match(needle: String, haystack: String|String[]): Number
// Returns the score and positions
fzy.matchPositions(needle: String, haystack: String|String[]): [Number, Number[]]

// Returns if there is a match
fzy.hasMatchMulti(needle: String, haystack: String[]): Boolean
// Returns the score
fzy.matchMulti(needle: String, haystack: String[]): Number
// Returns the score and positions
fzy.matchPositionsMulti(needle: String, haystack: String[]): [Number, Number[]]
```

The `*Multi` variants run the loop over haystacks in C, as opposed to the non-`*Multi`
that run the loop over haystacks in javascript.

The non-`*Multi` variants accepts either one haystack or a list of haystacks.

The benchmarks in terms of performance for looping in javascript or in C are
inconclusive. Below is one example but do not take that to mean anything, sometimes
the javascript is faster consistently, other times it switches

| method  | Searching for 'f' in 85k entries |
| -----   | -----                            |
| loop-js | 138.214ms                        |
| loop-c  | 131.86ms                         |


### Example

```javascript
const fzy = require('..')

const files = [
  'binding.gyp',
  'build/Debug/node_fzy.node',
  'build/Debug/obj.target/action_after_build.stamp',
  'build/Debug/obj.target/node_fzy/src/main.o',
  'build/Debug/obj.target/node_fzy.node',
  'build/Makefile',
  'build/Release/module.node',
  'build/Release/obj.target/module/src/main.o',
  'build/Release/obj.target/module.node',
  'build/action_after_build.target.mk',
  'build/binding.Makefile',
  'build/config.gypi',
  'build/module.target.mk',
  'build/node_fzy.target.mk',
  'compile_commands.json',
  'lib/binding/node-v83-linux-x64/node_fzy.node',
  'lib/index.js',
  'lib/native.js',
  'package-lock.json',
  'package.json',
  'src/main.cc',
]

const results = fzy.matchPositions('umo', files)

results.forEach(([score, positions], i) => {
  console.log([score, files[i], positions])
})
```
