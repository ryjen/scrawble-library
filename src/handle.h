#ifndef _HANDLE_H_INCLUDED_
#define _HANDLE_H_INCLUDED_
#include <jni.h>
#include <memory>
#include <map>

jfieldID getHandleFieldID(JNIEnv *env, jobject obj)
{

	jclass c = env->GetObjectClass(obj);
	// J is the type signature for long:
	return env->GetFieldID(c, "handle", "J");
}

template <typename T>
std::shared_ptr<T> getHandle(JNIEnv *env, jobject obj)
{
	jlong handle = env->GetLongField(obj, getHandleFieldID(env, obj));
	return std::shared_ptr<T>(reinterpret_cast<T*>(handle));
}

template <typename T>
void setHandle(JNIEnv *env, jobject obj, const std::shared_ptr<T> &t)
{
	env->SetLongField(obj, getHandleFieldID(env, obj), reinterpret_cast<jlong>(t.get()));
}


template <typename T>
void removeHandle(JNIEnv *env, jobject obj)
{
	auto fieldID = getHandleFieldID(env, obj);
	env->SetLongField(obj, fieldID, 0);
}

#endif
