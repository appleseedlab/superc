struct s1 x;

struct s2 {
  int data;
  struct s1 *next;
};

int main() {
  return ((struct s2) x).data;
}
