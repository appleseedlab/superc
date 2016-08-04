struct s {
  int a;
  int b : 1;
  int : 0;
  int c : 0; // {{ dg-error "zero width for bit-field" }}
  int d;
};
