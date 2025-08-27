typedef union {
  int* a;
  long b;
#ifdef ENABLE_A
} U __attribute__ ((__transparent_union__));
#else
} U;
#endif

int foo(U x) {
  return 1;
}


int main ()
{
  int x;
  #ifdef ENABLE_A
  return foo (&x);
  #else
  return 0;
  #endif
}

