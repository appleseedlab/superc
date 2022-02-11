#ifdef ENABLE_A
struct list {
  struct contents {
  } data;
} list;
#else
struct list {
  struct {
    char p;
  } data;
} list;
#endif

int main() {
  return sizeof(list.data);
}
