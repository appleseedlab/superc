#ifdef STRUCT_INIT
struct s {
  struct { int f; } x[4];
} bob = {.x = {[0].f = 10}};
#endif

#ifdef INIT
int x1 =  1;
int *x2 =  1;
int *( x2b) =  1;
int **x3 =  1;
int ( *( *( x3b))) =  1;
int x4a =  {1};
int x4b[2] =  {1, 2};
int x5[1][1] =  {{1}};
int *x6[1] =  {0};
int **x7[1] =  {0};
int ( *x8)[1] =  {0};
#endif
