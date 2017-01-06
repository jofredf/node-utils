#!/usr/bin/node

const NUtils = require('./build/Release/nutils');

console.log(NUtils.ClockGetTimeRealTimeObject());
console.log(NUtils.ClockGetTimeRealTime());

