#ifndef NUTILS_H
#define NUTILS_H

using namespace v8;

#include "tdef.h"
#include "timer.h"

#define CHECK(expr) \
	do{ \
		if(UNLIKELY(!(expr))){ \
			static const char* const args[] = {__FILE__, STRINGIFY(__LINE__), \
					#expr, PRETTY_FUNCTION_NAME}; \
			node::Assert(&args); \
		} \
	}while(0) \


void NMClockGetTime(const FunctionCallbackInfo<Value>& args);
void NMSetInterval(const FunctionCallbackInfo<Value>& args);
void NMSetTimeout(const FunctionCallbackInfo<Value>& args);

#endif //NUTILS_H
