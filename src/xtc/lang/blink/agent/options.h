#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include "state.h"

struct agent_options {
    int jinn;          /* Turn on Jinn error checking. */
    int failstop;      /* Generate a Java exception at a failure. */
    int interpose;     /* Turn on the transition interposition. */
    int stats;         /* Turn on collecting statstics. */
};

extern struct agent_options agent_options;

extern void agent_parse_options(const char *options);

#endif /* _OPTIONS_H_ */
