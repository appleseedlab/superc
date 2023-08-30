#ifdef ENABLE_A
const const float a;
const const const const const float b;
volatile volatile volatile volatile int c = 1;
#else
long d;
long long e;
long int f;
long long int g = 2;
long double h;
#endif

int main() {
  #ifdef ENABLE_A
  return c;
  #else
  return g;
  #endif
}
