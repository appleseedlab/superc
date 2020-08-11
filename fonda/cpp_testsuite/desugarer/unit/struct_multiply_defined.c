#ifdef CONFIG_A
struct {
  int x;
};
struct {
  int yy;
} var_joe;
#else  
struct {
  int y;
};
struct {
  int xx;
} var_joe;
#endif

/* struct bob var; */
