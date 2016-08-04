int main(void) {
  "hello"[1] = 'a'; // {{ dg-error "read-only operand" }}
}
