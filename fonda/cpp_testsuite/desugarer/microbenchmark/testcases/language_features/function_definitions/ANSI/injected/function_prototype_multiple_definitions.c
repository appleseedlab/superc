struct x;
enum z {R,S,T};
#ifdef A
struct x* foo(struct x *);
#else
int foo(enum z a, struct x *z);
#endif

#ifdef B
struct x {long field;};
#else
struct x {char field;};
#endif


int main() {
  struct x * temp;
  #ifdef C
  temp = foo(temp);
  return sizeof(temp->field);
  #else
  return foo(2,temp);
  #endif
}

#ifdef C
struct x* foo(struct x* q) { return q;} 
#else
int foo(enum z a, struct x* z) {return a;}
#endif

