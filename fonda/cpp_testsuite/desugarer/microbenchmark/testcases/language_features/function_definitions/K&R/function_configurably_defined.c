#ifdef CONFIG_A
typedef struct myfirststruct {
  int x;
} myfirststruct;

struct secondstruct;

static inline myfirststruct* func(sk) 
  const struct secondstruct * sk;
{
  return (myfirststruct*)sk;
}
#endif
