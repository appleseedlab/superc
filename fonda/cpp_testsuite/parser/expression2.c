int main() {
  int x = 
#ifdef A
    1
#else
#ifdef B
    2 + 3 + 4
#else
    5 + 6
#endif
    + 7
#endif
    ;
}

