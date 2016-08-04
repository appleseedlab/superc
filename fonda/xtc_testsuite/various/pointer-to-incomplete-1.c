int main(void) {
  struct s * p;

  p++;       // {{ dg-error "arithmetic on pointer" }}
  p--;       // {{ dg-error "arithmetic on pointer" }}
  ++p;       // {{ dg-error "arithmetic on pointer" }}
  --p;       // {{ dg-error "arithmetic on pointer" }}

  p + 5;     // {{ dg-error "arithmetic on pointer" }}
  p - 5;     // {{ dg-error "arithmetic on pointer" }}
  5 + p;     // {{ dg-error "arithmetic on pointer" }}
  -5 + p;    // {{ dg-error "arithmetic on pointer" }}

  *p;        // {{ dg-error "dereferencing pointer" }}
  p[7];      // {{ dg-error "dereferencing pointer" }}

  p->field;  // {{ dg-error "dereferencing pointer" }}
}
