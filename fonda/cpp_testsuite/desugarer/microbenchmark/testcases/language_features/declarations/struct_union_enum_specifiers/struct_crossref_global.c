struct s1 {
  int data;
#ifdef STRUCT
  struct s2 next;
#else
  struct s2 *next;
#endif
};

struct s2 {
  int data;
#ifdef STRUCT
  struct s1 next;
#else
  struct s1 *next;
#endif
};
