#ifdef CONFIG_SMP
extern void cpu_load_update_active(int this_rq);
#else
static inline void cpu_load_update_active(int this_rq) { }
#endif
