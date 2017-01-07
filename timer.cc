#include <node.h>

#include "nutils.h"

namespace nmtimer{

/*
using v8::Context;
using v8::Function;
*/

Persistent<Function> NMTimer::constructor;

NMTimer::NMTimer()
{
	
}

NMTimer::~NMTimer()
{
	
}

void NMTimer::Init(Local<Object> exports)
{
	Isolate *isolate = exports->GetIsolate();
	//Prepare constructor template:
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "Timer"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	//Prototype:
}

void NMTimer::New(const FunctionCallbackInfo<Value>& args)
{
	Isolate *isolate = args.GetIsolate();
	//This constructor should not be exposed to public javascript.
	if(!args.IsConstructCall())
	{
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,
				"Wrong call")));
		return;
	}
	NMTimer *tm = new NMTimer();
	tm->Wrap(args.This());
	//args.GetReturnValue(args.This());
}

} //namespace nmtimer

