#ifdef A
extern int x;
#endif

int main() {
  // should not be emitted when A is not defined
  x++;
}
