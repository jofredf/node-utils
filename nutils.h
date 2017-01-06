#ifndef NUTILS_H
#define NUTILS_H

using namespace v8;

inline double timespecToDouble(struct timespec *ts);
void NMClockGetTimeRealTime(const FunctionCallbackInfo<Value>& args);
void NMClockGetTimeRealTimeObject(const FunctionCallbackInfo<Value>& args);
void NMClockGetTimeMonotonicRaw(const FunctionCallbackInfo<Value>& args);
void NMClockGetTimeMonotonicRawObject(const FunctionCallbackInfo<Value>& args);

#endif //NUTILS_H
