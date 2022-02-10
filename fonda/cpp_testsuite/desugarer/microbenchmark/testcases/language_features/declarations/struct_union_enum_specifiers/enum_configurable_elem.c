#ifdef A
#define START 1
#else
#define START 0
#endif
enum E {E = START, B, C, D};

int main() {
enum E a;
return 0;
}
