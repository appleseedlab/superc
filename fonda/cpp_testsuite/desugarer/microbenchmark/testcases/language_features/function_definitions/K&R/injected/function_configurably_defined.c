#ifdef ENABLE_A
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

int main() {
  #ifdef ENABLE_A
  myfirststruct *sk;
  return sizeof(func(sk));
  #else
  return 0;
  #endif
}
