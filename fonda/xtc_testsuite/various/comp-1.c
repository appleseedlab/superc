int main(void) {
  int const n = 100;
  int * const p = (int*)100;
  void* const NULL = 0;

  n == NULL; // {{ dg-warning "comparison between pointer and integer" }}
  NULL == n; // {{ dg-warning "comparison between pointer and integer" }}
  n != NULL; // {{ dg-warning "comparison between pointer and integer" }}
  NULL != n; // {{ dg-warning "comparison between pointer and integer" }}
  n == p; // {{ dg-warning "comparison between pointer and integer" }}
  p == n; // {{ dg-warning "comparison between pointer and integer" }}
  n != p; // {{ dg-warning "comparison between pointer and integer" }}
  p != n; // {{ dg-warning "comparison between pointer and integer" }}
}
