#ifdef ENABLE_A
_Complex a = 1;
_Complex int b;
_Complex double c;
_Complex float d;
_Complex double e;
_Complex long double f;
#else
float *volatile g = 2;
int *volatile* h;
int * volatile const ** const * volatile * i[2];
#endif

int main() {
  #ifdef ENABLE_A
  return a;
  #else
  return g;
  #endif
}
