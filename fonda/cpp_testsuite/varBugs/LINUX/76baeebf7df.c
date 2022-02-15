#ifdef CONFIG_X86_32
#undef CONFIG_X86_64
#endif

#include <stdio.h>

/* #define NR_CPUS 64 */
typedef unsigned long cpumask_t;

cpumask_t cpu_none_mask = 0;
cpumask_t cpu_online_mask = 0;

#ifdef CONFIG_NUMA
#define NODES_SHIFT     8
#define MAX_NUMNODES    (1 << NODES_SHIFT)

int nr_node_ids;

cpumask_t* node_to_cpumask_map[MAX_NUMNODES];
#else
#define nr_node_ids             1
#endif

#ifdef CONFIG_NUMA

void setup_node_to_cpumask_map(void)
{
  unsigned int node;

  /* allocate the map */
  for (node = 0; node < nr_node_ids; node++)
    node_to_cpumask_map[node] = &cpu_online_mask;
}

#ifdef CONFIG_DEBUG_PER_CPU_MAPS
const cpumask_t *cpumask_of_node(int node)
{
  if (node >= nr_node_ids) {
    fprintf(stderr, "cpumask_of_node(%d): node > nr_node_ids(%d)\n",
            node, nr_node_ids);
    return cpu_none_mask;
  }
  if (node_to_cpumask_map[node] == NULL) {
    fprintf(stderr, "cpumask_of_node(%d): no node_to_cpumask_map!\n", node);
    return cpu_online_mask;
  }
  return node_to_cpumask_map[node];
}
#else
/* Returns a pointer to the cpumask of CPUs on Node 'node'. */
static inline const cpumask_t *cpumask_of_node(int node)
{
  return node_to_cpumask_map[node];
}
#endif /* CONFIG_DEBUG_PER_CPU_MAPS */

#else /* !CONFIG_NUMA */

static inline const cpumask_t *cpumask_of_node(int node)
{
  return &cpu_online_mask;
}

static inline void setup_node_to_cpumask_map(void) { }
#endif

#ifdef CONFIG_PCI

#ifdef CONFIG_NUMA

#define BUS_NR 256

#ifdef CONFIG_X86_64

static int mp_bus_to_node[BUS_NR] = {
    [0 ... BUS_NR - 1] = -1
};

int get_mp_bus_to_node(int busnum)
{
  int node = -1;

  if (busnum < 0 || busnum > (BUS_NR - 1))
    return node;

  node = mp_bus_to_node[busnum];

  return node;
}

#else /* CONFIG_X86_32 */

static unsigned char mp_bus_to_node[BUS_NR] = {
    [0 ... BUS_NR - 1] = -1
};

int get_mp_bus_to_node(int busnum)
{
  int node;

  if (busnum < 0 || busnum > (BUS_NR - 1))
    return 0;
  node = mp_bus_to_node[busnum];
  return node;
}

#endif /* CONFIG_X86_32 */

#else

static inline int get_mp_bus_to_node(int busnum)
{
  return 0;
}

#endif /* CONFIG_NUMA */

#ifdef CONFIG_NUMA
static const cpumask_t *
cpumask_of_pcibus(int node)
{
  return (node == -1) ? &cpu_online_mask
    : cpumask_of_node(node);
}
#endif

static int local_cpus_show(int node)
{
  const cpumask_t *mask;
  int len = 1;

  #ifdef CONFIG_NUMA
  mask = cpumask_of_pcibus(node);
  #else
  mask = cpumask_of_node(node);
  #endif
  printf("mask: %ld\n", *mask);

  return len;
}

static int dev_attr_show(int node)
{
  int ret;
  ret = local_cpus_show(node);
  return ret;
}

int pcibios_scan_root()
{
  return get_mp_bus_to_node(0);
}
#endif /* CONFIG_PCI */

int main(int argc, char** argv)
{
  #ifdef CONFIG_NUMA
  nr_node_ids = rand() % (MAX_NUMNODES-1);
  #endif
  setup_node_to_cpumask_map();
  #ifdef CONFIG_PCI
  int node = pcibios_scan_root();
  dev_attr_show(node);
  #endif
  return 0;
}
