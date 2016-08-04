//partially defined configuration variable

#ifdef CONFIG_CONFIG
#define M_CONFIG
//define M_CONFIG
#endif

#ifdef M_CONFIG
#define A
//define A
#endif

#ifdef A
//use A to configure this code
#endif
