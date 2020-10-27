
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
function fzy.hasMatch(needle: String, haystack: String|String[]): Boolean;
// Returns the score
function fzy.match(needle: String, haystack: String|String[]): Number;
// Returns the score and positions
function fzy.matchPositions(needle: String, haystack: String|String[]): [Number, Number[]];

// Returns if there is a match
function fzy.hasMatchMulti(needle: String, haystack: String[]): Boolean;
// Returns the score
function fzy.matchMulti(needle: String, haystack: String[]): Number;
// Returns the score and positions
function fzy.matchPositionsMulti(needle: String, haystack: String[]): [Number, Number[]];
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

#### Speed

To increase speed when searching for results, here are 2 things you can do:
 - When you're ranking matches, dont score all of them! You need to eliminate bad
     matches with `fzy.hasMatch` first. Those who pass may be scored.
 - When you're search query is simply the previous query plus some new character,
     don't search again on the whole set. Cache the last set of matches for the
     previous query and re-use that subset to do the current search.

#### Note

`.matchPositions*` returns the score and the positions. The positions are invalid if it
doesn't match, which can be verified previously with `.hasMatch` or by checking if the
score is `-Infinity`.

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

### Differences with the original fzy

1. If the `needle` contains uppercase letters, the search is case-sensitive
2. Perfect matches are returned with the highest score
