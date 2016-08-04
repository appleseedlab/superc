 /*
 * Works without optimization.  Broken with Oshare and Olazy together,
 * or all three together.
 */ 

int   f ( )  
{ 
#if TOP
# if defined(A)
    if ( a )
# else
    if ( 
#  if defined(B)
        b
#  else
        c
#  endif
         )
# endif
# if defined(D)
      d ( )  /* this one gets added to the statement list of the
                function and of the if statement, it also never gets
                printed out because the cycle happens before this */
# endif
        ;
#endif

 } 
