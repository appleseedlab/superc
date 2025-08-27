int
#ifdef ENABLE_A
  *
#else
  **
#endif
    c;

int main() {
  return sizeof(*c);
}
