external int printf ( const char * format, ... );
struct list {
  struct contents {
  } data;
  struct list *next;
};

int main() {
  struct list head;
  struct list tail;

  error();
  head.next = &tail;
  error();
  tail.next = 0;

  struct list *current = &head;
  while (0 != current) {
    printf("data: %d\n", current->data);
    current = current->next;
  }
  
  return 0;
}
