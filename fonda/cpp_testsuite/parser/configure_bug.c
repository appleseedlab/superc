/*
 * Uncovered a bug in the parser where the merged subparser's presence
 * condition was updated after instead of during merging.  Some
 * configurations got lost, because the merged subparser's presence
 * condition hadn't been disjoined yet.
 */

#ifdef A
# define __percpu	__attribute__(())
#else
# define __percpu
#endif

#ifdef B
#define PER_CPU_BASE_SECTION ".data..percpu"
#else
#define PER_CPU_BASE_SECTION ".data"
#endif

#ifdef C
int x; extern __percpu __attribute__((section(PER_CPU_BASE_SECTION))) p;
#else
extern __percpu __attribute__((section(PER_CPU_BASE_SECTION))) p;
#endif

