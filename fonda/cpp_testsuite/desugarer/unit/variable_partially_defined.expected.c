int a_1;
char a_2;
int x;
int main() {
  if (A)
    a_1;
  if (B)
    a_2;
  if (C)
    error();
  if (A && B)
    error();
  if (!A && !B)
    error();

  if (A)
    x = 7 * a_1 + 2;
  if (B)
    x = 7 * a_2 + 2;  
  if (C)
    error();
  if (A && B)
    error();
  if (!A && !B)
    error();

}
