int main() {
#if A + (1 << 3)
  1;
#elif 1 - 1
  2;  //infeasible path
#elif 3*10+4*8 > 100/30
  3;
#else
  4; //infeasible path
#endif
}
