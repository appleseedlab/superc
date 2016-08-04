#ifdef C1
#define ZONES_WIDTH     A
#else
#define ZONES_WIDTH     B
#endif

#ifdef C2
#define NODES_SHIFT     X
#else
#define NODES_SHIFT     Y
#endif

#if ZONES_WIDTH+NODES_SHIFT
IFBRANCH
#else
ELSEBRANCH
#endif

