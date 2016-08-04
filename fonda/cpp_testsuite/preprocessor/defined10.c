#ifdef C1
#define M 7 + 7
#else
#define M defined CONFIG_VAR
#endif

#if M
ONE
#endif

