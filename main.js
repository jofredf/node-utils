#!/usr/bin/node

const NUtils = require('./build/Release/nutils');

console.log(NUtils.ClockGetTime(0, false));

function test(a, b, c)
{
	console.log('OK');
	console.log(a);
	console.log(b);
	console.log(c);
}

NUtils.SetInterval(test, 1000, 69, true, {id:'OK'});
NUtils.SetTimeout(test, 1000);

