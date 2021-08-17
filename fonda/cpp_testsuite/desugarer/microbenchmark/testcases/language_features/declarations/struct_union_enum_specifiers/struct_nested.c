#ifdef NESTED
struct list {
  struct contents {
  } data;
};
#endif

#ifdef NESTEDANONYMOUS
struct list2 {
  struct {
    char p;
  } data;
};
#endif
