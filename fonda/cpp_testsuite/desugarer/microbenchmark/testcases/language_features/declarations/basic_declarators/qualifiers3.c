#ifdef STATIC_CONST_AUTO_REGISTER
static const int a;
extern const char b;
volatile double d;
#endif

#ifdef SIGNED_UNSIGNED
unsigned char f;
signed long g;
unsigned long h;
signed long long i;
unsigned long long j;
signed long long int k;
unsigned long long int l;
signed int m;
unsigned int n;
#endif

int main() {
  #ifdef STATIC_CONST_AUTO_REGISTER
  auto c;
  register const float e;
  #endif
}
