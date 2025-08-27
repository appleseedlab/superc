#ifdef ENABLE_A
struct list {
  int data;
  struct list *next;
};
#endif

int main() {
  #ifdef ENABLE_A

  #else
  struct list {
    struct list *next;
  };
  #endif
  return sizeof(struct list);
}
