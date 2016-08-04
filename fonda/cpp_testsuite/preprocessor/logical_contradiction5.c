#ifdef ONE
# define NODEP  //this macro should still depend on ONE being free
#endif


#if G



# ifndef ONE
#  define ONE
#  define DEP  //this macro should not depend on ONE being free
# endif



#endif

DEP
