struct test {
  int x;
};
  
int main() {
#ifdef A
  struct test var;
#else
  int var;
#endif

  // don't emit the int version of var
  var.x = 1;
}
