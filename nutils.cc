#include <node.h>
#include <uv.h>
#include <unistd.h>
#include <time.h>

#include "nutils.h"

using namespace v8;

/*
void Method(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, "..."));
}
*/

//{{{ init()
void init(Local<Object> exports)
{
	NODE_SET_METHOD(exports, "ClockGetTime", NMClockGetTime);
	NODE_SET_METHOD(exports, "SetInterval", NMSetInterval);
	NODE_SET_METHOD(exports, "SetTimeout", NMSetTimeout);
}
//}}}

//{{{ NMClockGetTime()
/**
	NUtils.ClockGetTime(<Integer>clockId)
*/
void NMClockGetTime(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	//Check the number of arguments passed:
	if(args.Length() < 1)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, 
				"Wrong number of arguments")));
		return;
	}
	//Check arguments type:
	if(!args[0]->IsNumber() || 
			(args.Length()>1 && !args[1]->IsBoolean()))
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, 
				"Wrong arguments")));
		return;
	}
	bool returnArray = args.Length()>1 ? args[1]->BooleanValue() : false;
	struct timespec ts;
	int rc;
	int value = args[0]->NumberValue();
	clockid_t clockId = CLOCK_REALTIME;
	switch(value)
	{
		case 0: clockId = CLOCK_REALTIME; 				break;
		case 1: clockId = CLOCK_REALTIME_COARSE;		break;
		case 2: clockId = CLOCK_MONOTONIC;				break;
		case 3: clockId = CLOCK_MONOTONIC_COARSE;		break;
		case 4: clockId = CLOCK_MONOTONIC_RAW;			break;
		case 5: clockId = CLOCK_BOOTTIME;				break;
		case 6: clockId = CLOCK_PROCESS_CPUTIME_ID;	break;
		case 7: clockId = CLOCK_THREAD_CPUTIME_ID;	break;
	}
	rc = clock_gettime(clockId, &ts);
	if(rc != 0)
	{
		isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, 
				"Unable to get system clock value")));
		return;
	}
	if(returnArray)
	{
		//Return Array:
		Local<Array> result = Array::New(isolate);
		result->Set(0, Number::New(isolate, ts.tv_sec));
		result->Set(1, Number::New(isolate, ts.tv_nsec));
		args.GetReturnValue().Set(result);
	}
	else
	{
		//Return Number:
		args.GetReturnValue().Set(Number::New(isolate, 
				double(ts.tv_sec)+double(ts.tv_nsec)/double(1E9)));
		return;
	}
}
//}}}

void run(SetTimeoutHandler *tmh)
{
	if(tmh == NULL)
		return;
	if(tmh->callback.IsEmpty())
	{
		delete tmh;
		return;
	}
	Isolate *isolate = Isolate::GetCurrent();
	Local<Function> cb = Local<Function>::New(isolate, tmh->callback);
	tmh->args->Length();
	/*
	if(tmh->args->Length() > 2)
		cb->Call(Null(isolate), tmh->args->Length()-2, &tmh->args[2]);
	else
		cb->Call(Null(isolate), 0, NULL);
	*/
	//tmh->callback.Reset();
	delete tmh;
	return;
}

//{{{ NMSetTimeout()
void NMSetTimeout(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	int argc = args.Length();
	//Check the number of arguments passed:
	if(argc < 2)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,
				"Wrong number of arguments")));
		return;
	}
	//Check arguments type:
	if(!args[0]->IsFunction() || !args[1]->IsNumber())
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,
				"Wrong arguments")));
		return;
	}
	Local<Function> cb = Local<Function>::Cast(args[0]);
	SetTimeoutHandler *tmh = new SetTimeoutHandler;
	Local<Value> localArgs[args.Length()];
	for(int i=0; i<args.Length(); i++)
		localArgs[i] = args[i];
	tmh->args->Reset(isolate, *localArgs);
	tmh->callback.Reset(isolate, cb);
	tmh->timeMs = args[1]->IntegerValue();
	sleep(2);
	run(tmh);
}
//}}}

//{{{ NMSetInterval()
/**
	NUtils.SetInterval(<Callback>cb, <Number>timeMs)
*/
void NMSetInterval(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	int argc = args.Length();
	//Check the number of arguments passed:
	if(argc < 2)
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, 
				"Wrong number of arguments")));
		return;
	}
	//Check arguments type:
	if(!args[0]->IsFunction() || !args[1]->IsNumber())
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, 
				"Wrong arguments")));
		return;
	}
	Local<Function> cb = Local<Function>::Cast(args[0]);
	//int64_t timeValueMs = args[1]->IntegerValue();
	if(argc > 2)
	{
		//Callback with arguments:
		Local<Value> argv[argc-2];
		for(int i=2,j=0; i<argc; i++,j++)
			argv[j] = args[i];
		cb->Call(Null(isolate), argc-2, argv);
		return;
	}
	cb->Call(Null(isolate), 0, NULL);
}
//}}}

NODE_MODULE(nutils, init)

