#ifndef _COMMON_H_
#define _COMMON_H_

#include "state.h"
#include "agent.h"

/* Handling call stack. */
#if defined(__GNUC__)
#include <sys/types.h>
#include <unistd.h>

#if defined(__MINGW32__)
#include <windows.h>
#define MUTEX_DECL(name)   static HANDLE name;
#define MUTEX_INIT(name)   do { name = CreateMutex(NULL, FALSE, NULL); } while(0)
#define MUTEX_LOCK(name)   do { WaitForSingleObject(name, INFINITE); } while(0)
#define MUTEX_UNLOCK(name) do {ReleaseMutex(name);} while(0)
#define VM_ALLOC_EXECUTABLE(size) \
  VirtualAlloc(NULL, (size), MEM_COMMIT, PAGE_EXECUTE_READWRITE)
#else
#include <sys/mman.h>
#include <pthread.h>
#define MUTEX_DECL(name)    static pthread_mutex_t name;
#define MUTEX_INIT(name)    do { pthread_mutex_init(&name, NULL);} while (0)
#define MUTEX_LOCK(name)    do { pthread_mutex_lock(&name);} while (0)
#define MUTEX_UNLOCK(name)  do { pthread_mutex_unlock(&name);} while (0)
#define VM_ALLOC_EXECUTABLE(size) \
    mmap(NULL, (size), PROT_EXEC|PROT_WRITE|PROT_READ, \
    MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
#endif
#define TLS_TYPE_SPEC __thread

#if defined(__i386__)
#define GET_CURRENT_PROCESS_ID() getpid()
#define GET_FRAME_POINTER(fp) asm("mov %%ebp, %0;": "=m"(fp));
#define GET_RETURN_ADDRESS(addr) \
  asm("movl 4(%%ebp), %%eax;movl %%eax, %0;":"=m"(addr));
#define GET_PREVIOUS_FRAME_POINTER(fp) \
  asm("movl 0(%%ebp), %%eax;movl %%eax, %0;":"=m"(fp));
#define SET_RETURN_ADDRESS(addr) \
  asm("movl %0, %%eax;movl %%eax, 4(%%ebp);"::"m"(addr));
#define SET_PREVIOUS_FRAME_POINTER(fp) \
  asm("movl %0, %%eax;movl %%eax, 0(%%ebp);"::"m"(fp));

#elif defined(__powerpc__)
#define GET_CURRENT_PROCESS_ID() getpid()
#define GET_FRAME_POINTER(fp) asm("stw %%r1, %0": "=m"(fp));
#define GET_RETURN_ADDRESS(addr) \
  asm("lwz %%r3, 0(%%r1);lwz %%r3, 4(%%r3);stw %%r3, %0":"=m"(addr));
#define GET_PREVIOUS_FRAME_POINTER(fp) asm("lwz %0, 0(%%r1);" : "=r"(fp));
#define SET_RETURN_ADDRESS(addr) \
  asm("lwz %%r3, 0(%%r1);stw %0, 4(%%r3);"::"r"(addr));
#define SET_PREVIOUS_FRAME_POINTER(fp) asm("stw %0, 0(%%r1);" :: "r"(fp));

#else
#error "x86 and ppc support only for gcc"
#endif

#elif defined(_WIN32)
#include <windows.h>
#define GET_CURRENT_PROCESS_ID() GetCurrentProcessId()
#define GET_FRAME_POINTER(fp)  _asm { _asm mov fp, ebp }
#define GET_RETURN_ADDRESS(addr) \
  _asm { _asm mov eax, [ebp + 4] _asm mov addr, eax }
#define GET_PREVIOUS_FRAME_POINTER(fp) \
  _asm { _asm mov eax, [ebp] _asm mov fp, eax }
#define SET_RETURN_ADDRESS(addr) \
  _asm { _asm mov eax, addr  _asm mov [ebp + 4], eax }
#define SET_PREVIOUS_FRAME_POINTER(fp) \
  _asm { _asm mov eax, fp  _asm mov [ebp], eax }

#define MUTEX_DECL(name)   static HANDLE name;
#define MUTEX_INIT(name)   do { name = CreateMutex(NULL, FALSE, NULL); } while(0)
#define MUTEX_LOCK(name)   do { WaitForSingleObject(name, INFINITE); } while(0)
#define MUTEX_UNLOCK(name) do {ReleaseMutex(name);} while(0)

#define VM_ALLOC_EXECUTABLE(size) \
  VirtualAlloc(NULL, (size), MEM_COMMIT, PAGE_EXECUTE_READWRITE)

#define TLS_TYPE_SPEC __declspec(thread)

#else
#error "no support for this platform"
#endif /* _GNUC_ and _WIN32 */

extern int bda_is_agent_native_method(void *address);
extern void bda_parse_method_descriptor(
    const char *desc, const char ***arg_types, const char **ret_type);

#endif
