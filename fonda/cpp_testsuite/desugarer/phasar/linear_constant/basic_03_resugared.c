int main() {
 int x;
 int y = 210;

 #ifdef CONFIG_A
   x = 42;
 #else 
   x = 13;
 #endif

 return x;
}
