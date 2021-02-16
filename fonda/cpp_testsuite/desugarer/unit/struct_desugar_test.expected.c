struct __s_1 {
  int data;
  struct s *next;
};

struct s {
  union {
    struct __s_1 __s_1;
  };
};


struct s;


struct s x1;

int main() {
  struct s;
  return x1.  __s_1.data  ;
}
