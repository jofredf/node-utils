#include <uv.h>

struct SetTimeoutHandler
{
	Persistent<Value> *args;
	Persistent<Function> callback;
	int64_t timeMs;
	SetTimeoutHandler()
	{
		args = nullptr;
	}
	~SetTimeoutHandler()
	{
		callback.Reset();
	}
};

