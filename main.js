#!/usr/bin/node

require('v8-profiler');
const NUtils = require('./build/Release/nutils');

console.log(NUtils.ClockGetTime(0, false));

function test(a, b, c)
{
	console.log('OK');
}

NUtils.SetInterval(test, 1000, 69, true, {id:'OK'});

function test2()
{
	for(var i=0; i<100000; i++)
	{
		//setTimeout(test, 0);
		NUtils.SetTimeout(test, 1000);
	}
}

setInterval(test2, 1000);

