extern int a;
#ifdef MULTI
extern int a;
#endif

int main() {
  a++;
}
