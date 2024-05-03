#ifdef ENABLE_A
int x1 = 1, *x2, *(x2b), **x3, (*(*(x3b))), x4a[], x4b[2], x5[3][3], *x6[4], **x7[6], (*x8)[7];
#else
int x1 = 2;
int *x2;
int *(x2b);
int **x3;
int (*(*(x3b)));
int x4a[];
int x4b[2];
int x5[3][3];
int *x6[4];
int **x7[6];
int (*x8)[7];
#endif

int main() {
  return x1;
}
