#ifdef CONFIG_A
struct bob {
  int x;
};
struct joe {
  int yy;
} var_joe;
#else  
struct bob {
  int y;
};
struct joe {
  int xx;
} var_joe;
#endif

struct bob var;
