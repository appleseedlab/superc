struct list {
  struct {
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
    printf("data: %c\n", current->data.p);
    current = current->next;
  }
  
  return 0;
}
