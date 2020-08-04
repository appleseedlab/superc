struct list {
  struct contents {
    char p;
  } data;
  struct list *next;
};

int main() {
  struct list head;
  struct list tail;

  head.data.p = 'a';
  head.next = &tail;
  tail.data.p = 'b';
  tail.next = 0;

  struct list *current = &head;
  while (0 != current) {
    struct contents data = current->data;
    printf("data: %c\n", data.p);
    current = current->next;
  }
  
  return 0;
}
