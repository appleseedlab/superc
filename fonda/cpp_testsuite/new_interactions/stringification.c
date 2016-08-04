#ifdef A
#define MACRO a
#else
#define MACRO b
#endif

#define _str(x) #x
#define str(x) _str(x)

int main() {
  printf(str(MACRO));
}

