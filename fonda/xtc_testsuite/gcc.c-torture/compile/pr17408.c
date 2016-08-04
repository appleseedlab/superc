/* PRs 17408 and 17409, with different options. */
extern int t;
extern int t = 0; // {{ dg-warning "initialized and declared" }}
void f(){t =0;}
void g(){h(&t);}
