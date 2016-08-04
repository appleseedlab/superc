#define DECLARE_PER_CPU_SECTION(type, name, sec)                        \
  extern __PCPU_DUMMY_ATTRS char __pcpu_scope_##name;                   \
  extern __PCPU_ATTRS(sec) __typeof__(type) per_cpu__##name

#define __PCPU_DUMMY_ATTRS                                              \
  __attribute__((section(".discard"), unused))

#define __PCPU_ATTRS(sec)                                               \
  __((section(PER_CPU_BASE_SECTION sec)))                               \
  PER_CPU_ATTRIBUTES

DECLARE_PER_CPU_SECTION(a, b, c);
