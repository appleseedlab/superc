unsigned factorial(unsigned n) {
   #ifdef CONFIG_A
     if (n <= 1) {
       return 1;
     }
     return n * factorial(n - 1);
   #else
     return n;
   #endif
}

int main() {
 int x = 5;
 x = factorial(x);
 return x;
}
