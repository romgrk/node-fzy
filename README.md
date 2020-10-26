
# node-fzy

Node.js binding to the original C fzy.

### Install

Requires a compiler.

```
npm install node-fzy
```

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
