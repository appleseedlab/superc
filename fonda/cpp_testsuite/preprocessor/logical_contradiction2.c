#if G //global context of self-guarding macro conditionals


# ifndef ONE
#  define ONE
# endif

# ifdef TWO
#  undef TWO
# endif

# ifndef THREE
#  define THREE
#  undef THREE
# endif

# ifdef FOUR
#  undef FOUR
#  define FOUR
# endif

/*# if A && defined FIVE || B && ! defined FIVE
#  undef FIVE
#  define FIVE
# endif*/


#endif
