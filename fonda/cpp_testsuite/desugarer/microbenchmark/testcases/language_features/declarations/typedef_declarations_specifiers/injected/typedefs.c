#ifdef ENABLE_A
typedef unsigned int i;
i y = 10;
typedef long long x;
typedef const x z;
typedef int *q;
typedef q w[2];
volatile typedef i j;
#else
typedef long unsigned int size_t;
size_t y = 5;
#endif

int main() {
  return y;
}
