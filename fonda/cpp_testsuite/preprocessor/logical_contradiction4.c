#ifdef P

# ifndef ONE
#  define ONE
# endif

# ifdef TWO
#  undef TWO
# endif



#endif



#if G //global context of self-guarding macro conditionals


# ifndef ONE
#  define ONE
# endif

# ifdef TWO
#  undef TWO
# endif




#endif
