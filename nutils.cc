#include <node.h>

#include <time.h>

#include "nutils.h"

using namespace v8;

//{{{ timespecToDouble()
inline double timespecToDouble(struct timespec *ts)
{
	return double(ts->tv_sec)+double(ts->tv_nsec)/double(1E9);
}
//}}}

void Method(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Local<Object> exports)
{
	NODE_SET_METHOD(exports, "ClockGetTimeRealTime", NMClockGetTimeRealTime);
	NODE_SET_METHOD(exports, "ClockGetTimeRealTimeObject", 
			NMClockGetTimeRealTimeObject);
	NODE_SET_METHOD(exports, "ClockGetTimeMonotonicRaw", 
			NMClockGetTimeMonotonicRaw);
	NODE_SET_METHOD(exports, "ClockGetTimeMonotonicRawObject", 
			NMClockGetTimeMonotonicRawObject);
}

//{{{ NMClockGetTimeRealTime()
void NMClockGetTimeRealTime(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	args.GetReturnValue().Set(Number::New(isolate, timespecToDouble(&ts)));
}
//}}}

//{{{ NMClockGetTimeRealTimeObject()
void NMClockGetTimeRealTimeObject(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	Local<Array> result = Array::New(isolate);
	result->Set(0, Number::New(isolate, ts.tv_sec));
	result->Set(1, Number::New(isolate, ts.tv_nsec));
	args.GetReturnValue().Set(result);
}
//}}}

//{{{ NMClockGetTimeMonotonicRaw()
void NMClockGetTimeMonotonicRaw(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
	args.GetReturnValue().Set(Number::New(isolate, timespecToDouble(&ts)));
}
//}}}

//{{{ NMClockGetTimeMonotonicRawObject()
void NMClockGetTimeMonotonicRawObject(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
	Local<Array> result = Array::New(isolate);
	result->Set(0, Number::New(isolate, ts.tv_sec));
	result->Set(1, Number::New(isolate, ts.tv_nsec));
	args.GetReturnValue().Set(result);
}
//}}}

NODE_MODULE(nutils, init)

