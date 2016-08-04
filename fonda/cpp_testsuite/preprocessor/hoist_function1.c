#ifndef __LINUX_BITMAP_H
#define __LINUX_BITMAP_H

#ifndef __ASSEMBLY__

#include <linux/types.h>

/*#ifdef CONFIG_PROFILE_ALL_BRANCHES
#define if(cond, ...) __trace_if( (cond , ## __VA_ARGS__) )
#define __trace_if(cond) \
        if (__builtin_constant_p((cond)) ? !!(cond) :                   \
        ({                                                              \
                int ______r;                                            \
                static struct ftrace_branch_data                        \
                        __attribute__((__aligned__(4)))                 \
                        __attribute__((section("_ftrace_branch")))      \
                        ______f = {                                     \
                                .func = __func__,                       \
                                .file = __FILE__,                       \
                                .line = __LINE__,                       \
                        };                                              \
                ______r = !!(cond);                                     \
                ______f.miss_hit[______r]++;                                    \
                ______r;                                                \
        }))
#endif*/

//__trace_if(BITS_PER_LONG)

#define __trace_if(x)

if (BITS_PER_LONG)

//if (BITS_PER_LONG)

//if (small_const_nbits(nbits))

#endif /* __ASSEMBLY__ */

#endif /* __LINUX_BITMAP_H */
