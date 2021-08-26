int main() {
  while (1) {
#ifdef BREAK
    break;
#elif defined CONTINUE
    continue;
#else
    goto ret;
#endif
  }
ret:
  return 0;
}
