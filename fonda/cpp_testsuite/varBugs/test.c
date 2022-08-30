int main() {
  int *x = malloc(sizeof(int));
  *x = 2;
  free(x);
  return *x;
}
