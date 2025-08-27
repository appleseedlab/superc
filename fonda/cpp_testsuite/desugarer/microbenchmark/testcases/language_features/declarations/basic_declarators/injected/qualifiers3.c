#ifdef ENABLE_A
static const int a = 1;
extern const char b;
const float c;
volatile double d;
#else
unsigned char f;
signed long g = 2;
unsigned long h;
signed long long i;
unsigned long long j;
signed long long int k;
unsigned long long int l;
signed int m;
unsigned int n;
#endif

int main() {
  #ifdef ENABLE_A
  register const float e;
  return a;
  #else
  return g;
  #endif
}
