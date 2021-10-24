
extern const struct globals * ptr_to_globals;
enum {
  TEST_BUFFER_BLOCKS = 16,
};

struct globals {
    char check_blocks_buffer[TEST_BUFFER_BLOCKS];
};

int main() {
  (*(struct globals**)&ptr_to_globals) = (void*)(0);
  return 0;
}
