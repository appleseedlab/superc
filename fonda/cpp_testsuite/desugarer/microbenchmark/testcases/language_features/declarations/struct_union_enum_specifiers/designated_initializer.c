#ifdef A
struct s {
  struct { int f; } x[4];
} bob = {.x = {[0].f = 10}};
#endif
