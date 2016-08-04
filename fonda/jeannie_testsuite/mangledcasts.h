#ifndef _MANGLED_CASTS_H_

#ifdef __LP64__
jlong ptr2long(void* p) { return (jlong)p; }
void* long2ptr(jlong l) { return (void*)l; }
#else
//go indirectly through jint, to suppress gcc warning on 32-bit pointer cast
jlong ptr2long(void* p) { jint i = (jint)p; return (jlong)i; }
void* long2ptr(jlong l) { jint i = (jint)l; return (void*)i; }
#endif

#define env2long(p)   ptr2long(p)
#define long2env(l,T) ((struct T*)long2ptr(l))

#endif
