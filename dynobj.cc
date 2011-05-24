/* This code is PUBLIC DOMAIN, and is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND. See the accompanying 
 * LICENSE file.
 */

#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

class DynObj: ObjectWrap
{
private:
	int m_count;
public:

	static Persistent<FunctionTemplate> s_ct;
	static void Init(Handle<Object> target)
	{
		HandleScope scope;

		Local<FunctionTemplate> t = FunctionTemplate::New(New);

		s_ct = Persistent<FunctionTemplate>::New(t);
		s_ct->InstanceTemplate()->SetInternalFieldCount(1);
		s_ct->SetClassName(String::NewSymbol("DynObj"));
		s_ct->InstanceTemplate()->SetNamedPropertyHandler(GetIndexedProperty,
														  SetIndexedProperty,
// different versions of V8 require different return types
// 0.2.0 is where the switch occurred
#ifndef NODE_MAJOR_VERSION
														  NULL, //QueryIndexedProperty,
#elif PROXY_NODE_VERSION_AT_LEAST(0, 2, 0)
														  NULL, //QueryIndexedPropertyInteger,
#else
														  NULL, //QueryIndexedProperty,
#endif
														  NULL, //DeleteIndexedProperty
									  NULL //NamedPropertyEnumerator
			);
		NODE_SET_PROTOTYPE_METHOD(s_ct, "create", CreateDynObj);
	
		target->Set(String::NewSymbol("DynObj"),
					s_ct->GetFunction());
	}

	DynObj() :
		m_count(0)
	{
	}

	~DynObj()
	{
	}

	static Handle<Value> New(const Arguments& args)
	{
		HandleScope scope;
		DynObj* hw = new DynObj();
		hw->Wrap(args.This());

		return args.This();
	}

	/*
	 * If real property exists, return it first
	 * If the object has a __get__ property, if its function invoke it
	 * to get the property. If not, return the __get__ directly
	 */
	static Handle<Value> GetIndexedProperty(v8::Local<v8::String> name,
											const AccessorInfo &info) {
		HandleScope scope;
		// Send real properties untouched
		Local<Value> value =  scope.Close(info.This()->GetRealNamedProperty(name));
		if (!value.IsEmpty()) {
			return value;
		}

		Local<String> getter = String::New("__get__");

		Handle<Value> accessor = info.This()->GetRealNamedPropertyInPrototypeChain(getter);
		if (!accessor.IsEmpty() && accessor->IsFunction()) {
			Handle<Function> accessorFn = Handle<Function>(Function::Cast(*accessor));
			int argc=1;
			Local<Value> argv[1];
			argv[0] = name;
			Local<Value> dynamicProperty = accessorFn->Call(info.This(), argc, argv);
			return dynamicProperty;
		} else {
			return accessor;
		}

		return scope.Close(Handle<Value>(NULL));
	}

	/*
	 * If __set__ function exists, invoke it to set the property.
	 * If __set__ returns boolean 'false', set real property.
	 * If not return the value returned
	 */
	static Handle<Value> SetIndexedProperty(v8::Local<v8::String> name,
											Local<Value> value,
											const AccessorInfo &info) {
		HandleScope scope;

		Local<String> setter = String::New("__set__");

		Handle<Value> accessor = info.This()->GetRealNamedPropertyInPrototypeChain(setter);
		if (!accessor.IsEmpty() && accessor->IsFunction()) {
			Handle<Function> accessorFn = Handle<Function>(Function::Cast(*accessor));
			int argc=2;
			Local<Value> argv[2];
			argv[0] = name;
			argv[1] = value;
			Local<Value> result = accessorFn->Call(info.This(), argc, argv);
			if (result->IsBoolean() && result->BooleanValue()) {
				return scope.Close(Handle<Value>(NULL));
			} else {
				return result;
			}
		}
		return scope.Close(Handle<Value>(NULL));
	}

	static Handle<Array> NamedPropertyEnumerator(const AccessorInfo &info)  {
		HandleScope scope;

		Local<String> enumerator = String::New("__enum__");
		Handle<Value> accessor = info.This()->GetRealNamedPropertyInPrototypeChain(enumerator);
		if (!accessor.IsEmpty() && accessor->IsFunction()) {
			Handle<Function> accessorFn = Handle<Function>(Function::Cast(*accessor));
			int argc=0;
			Local<Value> result = accessorFn->Call(info.This(), argc, NULL);
			return Local<Array>::Cast(result);
		}
		return scope.Close(Handle<Array>(NULL));
	}

	static Handle<Value> CreateDynObj(const Arguments& args)
	{
		HandleScope scope;

		Local<FunctionTemplate> t = FunctionTemplate::New(New);

		s_ct = Persistent<FunctionTemplate>::New(t);
		s_ct->InstanceTemplate()->SetInternalFieldCount(1);
		s_ct->SetClassName(String::NewSymbol("DynObj"));
		s_ct->InstanceTemplate()->SetNamedPropertyHandler(GetIndexedProperty,
														  SetIndexedProperty,
// different versions of V8 require different return types
// 0.2.0 is where the switch occurred
#ifndef NODE_MAJOR_VERSION
														  NULL, //QueryIndexedProperty,
#elif PROXY_NODE_VERSION_AT_LEAST(0, 2, 0)
														  NULL, //QueryIndexedPropertyInteger,
#else
														  NULL, //QueryIndexedProperty,
#endif
														  NULL, //DeleteIndexedProperty
														  NamedPropertyEnumerator
			);

		return s_ct->GetFunction();
	}

};

Persistent<FunctionTemplate> DynObj::s_ct;

extern "C" {
	static void init (Handle<Object> target)
	{
		DynObj::Init(target);
	}

	NODE_MODULE(dynobj, init);
}
