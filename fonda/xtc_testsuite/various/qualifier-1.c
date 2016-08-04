int main(void) {
  const int * cip = 0;
  int * ip = 0;

  ip = cip; // {{ dg-warning "discards qualifiers" }}
}
