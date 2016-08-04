/*
 * Works without optimization.  Broken with Oshare and Olazy together,
 * or all three together.
 */

#ifdef B
# ifdef C
#  define if(cond, ...) if (0)
# endif

# ifndef C
#  define m3()	a()
# endif
#endif

# ifdef D
#  define m2() b()
# endif

# ifdef E
#  define m2() do { } while (0)
# endif

#ifdef CONFIG_BUG
# define m1() ({ if (m3()) m2(); })
#endif

int f() 
{

#ifdef CONFIG_DEBUG_VM
		m1();
#endif
}
