#ifndef CONFIG_NR_CPUS
/* FIXME: This should be fixed in the arch's Kconfig */
#define CONFIG_NR_CPUS  1
#endif

/* Places which use this should consider cpumask_var_t. */
#define NR_CPUS         CONFIG_NR_CPUS

extern unsigned long __per_cpu_offset[NR_CPUS];
