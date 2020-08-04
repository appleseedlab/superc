struct list head;

struct list {
  char data;
  struct list *next;
};

int main() {
  struct list tail;

  head.data = 'a';
  head.next = &tail;
  tail.data = 'b';
  tail.next = 0;

  struct list *current = &head;
  while (0 != current) {
    printf("data: %c\n", current->data);
    current = current->next;
  }
  
  return 0;
}
