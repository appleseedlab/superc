typedef struct {
  unsigned long int a[16];
} Y;

struct X {
  Y b;
};

#ifdef ENABLE_A
typedef struct X testStruct[1];
testStruct x;
#else
int x;
#endif

int main() {
  return sizeof(x);
}
