extern void* malloc(const int);
extern void free(void*);
extern void* calloc(const int);
int foo () {
  return 2;
}
int main () {
  int *f;
  f =  malloc(4);
  f = calloc(4);
  *f = foo();
  free(f);
  return 0;
}
