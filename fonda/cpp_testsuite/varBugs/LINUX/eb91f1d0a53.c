#if defined(CONFIG_LOCKDEP) && defined(CONFIG_TRACE_IRQFLAGS) && defined(CONFIG_PROVE_LOCKING)
#include <assert.h>
#endif
#include <stdbool.h>

#define ___GFP_WAIT             0x10u
#define ___GFP_IO               0x40u
#define ___GFP_FS               0x80u
#define ___GFP_HIGH             0x20u
#define __GFP_HIGH      ((gfp_t)___GFP_HIGH)
#define __GFP_WAIT      ((gfp_t)___GFP_WAIT)    /* Can wait and reschedule? */
#define __GFP_IO        ((gfp_t)___GFP_IO)      /* Can start physical IO? */
#define __GFP_FS        ((gfp_t)___GFP_FS)      /* Can call down to low-level FS? */
#define GFP_KERNEL      (__GFP_WAIT | __GFP_IO | __GFP_FS)
#define GFP_ATOMIC      (__GFP_HIGH)
#define GFP_NOWAIT      (GFP_ATOMIC & ~__GFP_HIGH)

typedef int gfp_t;

bool irqs_disabled = false;

void local_irq_disable(void)
{
  irqs_disabled = true;
}

#if defined(CONFIG_LOCKDEP) && defined(CONFIG_TRACE_IRQFLAGS) && defined(CONFIG_PROVE_LOCKING)
static void __lockdep_trace_alloc(gfp_t gfp_mask)
{
  if (!(gfp_mask & __GFP_WAIT))
    return;

  if (!(gfp_mask & __GFP_FS))
    return;

  assert(!irqs_disabled);
}

void lockdep_trace_alloc(gfp_t gfp_mask)
{
  __lockdep_trace_alloc(gfp_mask);
}
#else
void lockdep_trace_alloc(gfp_t gfp_mask)
{
}
#endif

#ifdef CONFIG_SLAB

#ifdef CONFIG_NUMA
void __cache_alloc_node(gfp_t flags)
{
  lockdep_trace_alloc(flags);
}

void kmem_cache_alloc_node(gfp_t flags)
{
  __cache_alloc_node(flags);
}

#ifdef CONFIG_KMEMTRACE
void kmem_cache_alloc_node_notrace(gfp_t flags)
{
  __cache_alloc_node(flags);
}
#else
void kmem_cache_alloc_node_notrace(gfp_t flags)
{
  kmem_cache_alloc_node(flags);
}
#endif
#endif /* CONFIG_NUMA */


#ifdef CONFIG_NUMA
static void kmalloc_node(gfp_t gfp_mask)
{
  kmem_cache_alloc_node_notrace(gfp_mask);
}
#endif

#if !defined(CONFIG_NUMA)
void kmalloc_node()
{
  return;
}
#endif

static int setup_cpu_cache()
{
  kmalloc_node(GFP_KERNEL);
}

void kmem_cache_create()
{
  setup_cpu_cache();
}

void kmem_cache_init(void)
{
  #ifdef CONFIG_SLAB
  kmem_cache_create();
  #endif
}
#else
void kmem_cache_init(void)
{
}
#endif

static void mm_init(void)
{
  kmem_cache_init();
}

int main()
{
  local_irq_disable();
  mm_init();
  return 0;
}
