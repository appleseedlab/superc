#ifndef CONFIG_NR_CPUS

#define CONFIG_NR_CPUS  1
#endif


#define NR_CPUS         CONFIG_NR_CPUS



int nr_cpus = NR_CPUS;


#if NR_CPUS > 1
kprintf("bob");
#endif
