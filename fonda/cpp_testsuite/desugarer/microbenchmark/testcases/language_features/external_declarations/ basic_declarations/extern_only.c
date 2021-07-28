// since the function is external, the renamed function needs to be defined to just call the external function by its original name
#ifdef CONFIG_A
extern int f(int x);
#else
extern int f(int x);
#endif
