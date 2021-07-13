#ifdef CONFIG_A
typedef struct myfirststruct {
  int x;
} myfirststruct;

struct secondstruct;

static inline myfirststruct* func(const struct secondstruct* sk) {

  int example;

  return (myfirststruct*)sk;
}
#endif
