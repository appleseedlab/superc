
#ifdef A
const int TEST_BUFFER_BLOCKS = 16;
#else
int TEST_BUFFER_BLOCKS = 10;
#endif
int xx;
int main() {
  const struct globals * ptr_to_globals;
  struct globals {
    char check_blocks_buffer[TEST_BUFFER_BLOCKS];
  };
  (*(struct globals**)&ptr_to_globals) = (void*)(0);
  return 0;
}
