#ifdef A
typedef long long type;
#else
typedef int type;
#endif
int foo (type x);
int foo2 (type *x);
int foo3 (type *(x));
int foo4 (type **x);
int foo5 (type (*(*(x))));
int foo6 (type x[]);
int foo7 (const type x[2]);
int foo8 (type x[3][3]);
int foo9 (type *x[4]);
int foo10 (type **const x[6]);
int foo11 (type (*x)[7]);

int main() {
  return foo(1);
}

int foo (type x) {return sizeof(x);}
int foo2 (type *x){return sizeof(x);}
int foo3 (type *(x)){return sizeof(x);}
int foo4 (type **x){return sizeof(x);}
int foo5 (type (*(*(x)))){return sizeof(x);}
int foo6 (type x[]){return sizeof(x);}
int foo7 (const type x[2]){return sizeof(x);}
int foo8 (type x[3][3]){return sizeof(x);}
int foo9 (type *x[4]){return sizeof(x);}
int foo10 (type **const x[6]){return sizeof(x);}
int foo11 (type (*x)[7]){return sizeof(x);}
