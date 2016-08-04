// From linux-3.2.9/kernel/sched.c

#define SCHED_FEAT(name, enabled)       \
        __SCHED_FEAT_##name ,

enum {
#include "sched_features.h"
};

#undef SCHED_FEAT

#define SCHED_FEAT(name, enabled)       \
        (1UL << __SCHED_FEAT_##name) * enabled |

static const unsigned int sysctl_sched_features =
#include "sched_features.h"
        0;
