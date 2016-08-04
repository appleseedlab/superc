/* {{ dg-checkwhat "c-analyzer" }} */
struct a
{
  struct b t;	/* {{ dg-error "has incomplete type" }} */  
};
