#ifdef STRUCT_INIT
struct s {
  struct { int f; } x[4];
} bob = {.x = {[0].f = 10}};
#endif

#ifdef INIT
int x1 = 1;
int *x2 = 1;
int *(x2b) = 1;
int **x3 = 1;
int (*(*(x3b))) = 1;
int x4a[] = 1;
int x4b[2] = 1;
int x5[3][3] = 1;
int *x6[4] = 1;
int **x7[6] = 1;
int (*x8)[7] = 1;
#endif
