#define USER_PRIO(p)		((p)-MAX_RT_PRIO)
#define TASK_USER_PRIO(p)	USER_PRIO((p)->static_prio)
#define MAX_USER_PRIO		(USER_PRIO(MAX_PRIO))

/*
 * Helpers for converting nanosecond timing to jiffy resolution
 */
#define NS_TO_JIFFIES(TIME)	((unsigned long)(TIME) / (NSEC_PER_SEC / HZ))

#define NICE_0_LOAD		SCHED_LOAD_SCALE
#define NICE_0_SHIFT		SCHED_LOAD_SHIFT

/*
 * These are the 'tuning knobs' of the scheduler:
 *
 * default timeslice is 100 msecs (used only for SCHED_RR tasks).
 * Timeslices get refilled after they expire.
 */
#define DEF_TIMESLICE		(100 * HZ / 1000)

/*
 * single value that denotes runtime == period, ie unlimited time.
 */
#define RUNTIME_INF	((u64)~0ULL)

#ifdef CONFIG_SMP
1
#endif

2

#ifdef CONFIG_RT_GROUP_SCHED
3
#endif

4

#ifdef CONFIG_GROUP_SCHED

5

#ifdef CONFIG_CGROUP_SCHED
7
#endif

8

#ifdef CONFIG_FAIR_GROUP_SCHED
9
#endif

10

#ifdef CONFIG_RT_GROUP_SCHED
11
#endif

12

#ifdef CONFIG_USER_SCHED

13

#ifdef CONFIG_FAIR_GROUP_SCHED

14

#endif /* CONFIG_FAIR_GROUP_SCHED */

15

#ifdef CONFIG_RT_GROUP_SCHED

16

#endif /* CONFIG_RT_GROUP_SCHED */

17

#else /* !CONFIG_USER_SCHED */

18

#endif /* CONFIG_USER_SCHED */

19

#ifdef CONFIG_FAIR_GROUP_SCHED
20
#ifdef CONFIG_USER_SCHED
21
#else /* !CONFIG_USER_SCHED */
22
#endif /* CONFIG_USER_SCHED */

23

#endif

24

#ifdef CONFIG_USER_SCHED
25
#elif defined(CONFIG_CGROUP_SCHED)
26
#else
27
#endif

28

#ifdef CONFIG_FAIR_GROUP_SCHED

29

#endif

#ifdef CONFIG_RT_GROUP_SCHED

30

#endif

31

#else

32

#endif	/* CONFIG_GROUP_SCHED */

33

#ifdef CONFIG_FAIR_GROUP_SCHED

34

#ifdef CONFIG_SMP

35

#endif

36

#endif

37

#if defined CONFIG_SMP || defined CONFIG_RT_GROUP_SCHED

38

#endif

39

#ifdef CONFIG_SMP

40

#endif

41

#ifdef CONFIG_RT_GROUP_SCHED

42

#endif

43

#ifdef CONFIG_SMP

44

#ifdef CONFIG_SMP

45

#endif

46

#endif

47

#ifdef CONFIG_NO_HZ

48

#endif

49

#ifdef CONFIG_FAIR_GROUP_SCHED

50

#endif

51

#ifdef CONFIG_RT_GROUP_SCHED

52

#endif

53

#ifdef CONFIG_SMP

54

#endif

55

#ifdef CONFIG_SCHED_HRTICK

56

#ifdef CONFIG_SMP

57

#endif

58

#endif

59

#ifdef CONFIG_SCHEDSTATS

60

#endif

61

#ifdef CONFIG_SMP

62

#else

63

#endif

64

#define for_each_domain(cpu, __sd) \

#define cpu_rq(cpu)		(&per_cpu(runqueues, (cpu)))
#define this_rq()		(&__get_cpu_var(runqueues))
#define task_rq(p)		cpu_rq(task_cpu(p))
#define cpu_curr(cpu)		(cpu_rq(cpu)->curr)

65

#ifdef CONFIG_SCHED_DEBUG

66

# define const_debug __read_mostly

#else

67

# define const_debug static const

#endif

68

#define SCHED_FEAT(name, enabled)	\
	__SCHED_FEAT_##name ,

#undef SCHED_FEAT

#define SCHED_FEAT(name, enabled)	\
	(1UL << __SCHED_FEAT_##name) * enabled |


#undef SCHED_FEAT

#ifdef CONFIG_SCHED_DEBUG

69

#define SCHED_FEAT(name, enabled)	\
	#name ,


#undef SCHED_FEAT

#endif

70

#define sched_feat(x) (sysctl_sched_features & (1UL << __SCHED_FEAT_##x))

#ifndef prepare_arch_switch

71

# define prepare_arch_switch(next)	do { } while (0)
#endif

72

#ifndef finish_arch_switch

73

# define finish_arch_switch(prev)	do { } while (0)
#endif

74

#ifndef __ARCH_WANT_UNLOCKED_CTXSW

75

#ifdef CONFIG_DEBUG_SPINLOCK

76

#endif

77

#else /* __ARCH_WANT_UNLOCKED_CTXSW */

78

#ifdef CONFIG_SMP

79

#else

80

#endif

81

#ifdef CONFIG_SMP

82

#endif

83

#ifdef __ARCH_WANT_INTERRUPTS_ON_CTXSW

84

#else

85

#endif

86

#ifdef CONFIG_SMP

87

#endif

88

#ifndef __ARCH_WANT_INTERRUPTS_ON_CTXSW

89

#endif

90

#endif /* __ARCH_WANT_UNLOCKED_CTXSW */

91

#ifdef CONFIG_SCHED_HRTICK

92

#ifdef CONFIG_SMP

93

#else

94

#endif /* CONFIG_SMP */

95

#ifdef CONFIG_SMP

96

#endif

97

#else	/* CONFIG_SCHED_HRTICK */

98

#endif	/* CONFIG_SCHED_HRTICK */

99
