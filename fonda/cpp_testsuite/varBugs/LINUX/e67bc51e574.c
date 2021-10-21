#ifdef CONFIG_TRACING
void trace_dump_stack(int skip) {
  // do something
  return;
}
#else
static inline void trace_dump_stack(void) { }
#endif

int main(int argc, char** argv) {
  trace_dump_stack(0); // ERROR
  return 0;
}
