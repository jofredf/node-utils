#include <uv.h>

struct SetTimeoutHandler
{
	uv_work_t request;
	Persistent<Function> callback;
	int64_t timeMs;
};

