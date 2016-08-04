//testing undefinition

#ifdef A
#define CONFIG
#endif

#undef CONFIG

#if defined CONFIG
#endif

