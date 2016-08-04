// {{ dg-preprocess "Need preprocessing" }}

#define bug_on(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

enum e {
  A,
  B = A,
  C = A + 500
};

int main(void) {
  bug_on(A != B);
  bug_on(C != 500);
}
