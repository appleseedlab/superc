typedef
#ifdef ENABLE_A
int
#else
double
#endif
a;

int main() {
  a x;
  return sizeof(x);

}

