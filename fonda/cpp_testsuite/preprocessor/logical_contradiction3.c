#if G //global context of self-guarding macro conditionals


# if P && ! defined ONE
#  define ONE
# endif

# if P && defined TWO
#  undef TWO
# endif

# if P && ! defined THREE
#  define THREE
#  undef THREE
# endif

# if P && defined FOUR
#  undef FOUR
#  define FOUR
# endif

/*# if A && defined FIVE || B && ! defined FIVE
#  undef FIVE
#  define FIVE
# endif*/


#endif
