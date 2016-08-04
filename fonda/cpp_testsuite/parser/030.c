#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#define container_of(ptr, type, member) ({                      \
        const typeof(((type *)0)->member) * __mptr = (ptr);     \
        (type *)((char *)__mptr - offsetof(type, member)); })

#ifdef CONFIG_CGROUP_SCHED

/*
 * Return the group to which this tasks belongs.
 *
 * We use task_subsys_state_check() and extend the RCU verification
 * with lockdep_is_held(&task_rq(p)->lock) because cpu_cgroup_attach()
 * holds that lock for each task it moves into the cgroup. Therefore
 * by holding that lock, we pin the task to the current cgroup.
 */
static inline struct task_group *task_group(struct task_struct *p)
{
  struct task_group *tg;
  struct cgroup_subsys_state *css;

  if (p->flags & PF_EXITING)
    return &root_task_group;

  css = task_subsys_state_check(p, cpu_cgroup_subsys_id,
                                lockdep_is_held(&task_rq(p)->lock));
  tg = container_of(css, struct task_group, css);

  return autogroup_task_group(p, tg);
}

/* Change a task's cfs_rq and parent entity if it moves across CPUs/groups */
static inline void set_task_rq(struct task_struct *p, unsigned int cpu)
{
#ifdef CONFIG_FAIR_GROUP_SCHED
  p->se.cfs_rq = task_group(p)->cfs_rq[cpu];
  p->se.parent = task_group(p)->se[cpu];
#endif

#ifdef CONFIG_RT_GROUP_SCHED
  p->rt.rt_rq  = task_group(p)->rt_rq[cpu];
  p->rt.parent = task_group(p)->rt_se[cpu];
#endif
}

#else /* CONFIG_CGROUP_SCHED */

static inline void set_task_rq(struct task_struct *p, unsigned int cpu) { }
static inline struct task_group *task_group(struct task_struct *p)
{
  return NULL;
}

#endif /* CONFIG_CGROUP_SCHED */
