int f(int **[4][5]);
int g(int (**[4][5]));
/* int h(int **([4])[5]); */  // parse error with superc
int i(int *(*([4]))[5]);
int j(int ((*(*))[4][5]));
int k(int **[4][5]);
int l(int **[4][5]);
