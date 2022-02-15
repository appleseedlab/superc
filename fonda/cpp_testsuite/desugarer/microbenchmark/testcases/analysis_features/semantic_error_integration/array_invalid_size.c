#ifdef INVALID
int a[-1];
#else
int a[1];
#endif

int main() {
  return a[0];
}
