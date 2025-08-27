extern void* malloc(unsigned int);
struct a {
  struct a * b;
  int value;
};

int main() {
  struct a * c, *d;
  c = malloc(sizeof(struct a));
  d = malloc(sizeof(struct a));
  d->b = malloc(sizeof(struct a));
  #ifdef A
  d->b->value = 3;
  #else
  d->b->value = 2;
  #endif
 *c = *(d->b);
 return c->value;
}
