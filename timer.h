#ifndef NUTILS_TIMER_H
#define NUTILS_TIMER_H

#include <node.h>
#include <node_object_wrap.h>

namespace nmtimer{
	
class NMTimer : public node::ObjectWrap{
	
	public:
		static void Init(v8::Local<v8::Object> exports);
	
	private:
		explicit NMTimer();
		~NMTimer();
		
		static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
		static v8::Persistent<v8::Function> constructor;
};

} //namespace nmtimer

#endif //NUTILS_TIMER_H
