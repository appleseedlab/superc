#ifdef SELFREF
struct list {
  int data;
  struct list *next;
};
#endif

#ifdef SELFREF_LOCAL
int main() {
  struct list2 {
    int data;
    struct list2 *next;
  };
}
#endif
