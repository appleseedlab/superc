int x1 = 1;
int *x2 = 1;
int *(x2b) = 1;
int **x3 = 1;
int (*(*(x3b))) = 1;
int x4a[] = 1;
int x4b[2] = 1;
int x5[3][3] = 1;
int *x6[4] = 1;
int **x7[6] = 1;
int (*x8)[7] = 1;


// function declarators
// function pointer declarators
int y1, *y2, *(y2b), **y3, (*(*(y3b))), y4a[], y4b[2], y5[3][3], *y6[4], **y7[6], (*y8)[7];
