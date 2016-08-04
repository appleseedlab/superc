/* PR/11658  The error message was quite mysterious for gcc up to 3.4.x */
/* {{ dg-checkwhat "c-analyzer" }} */
union a {
  int x;
};

int bug_if(union a a) { if (a) return 1; else return 0; }  /* {{ dg-error "scalar required" }} */
int bug_while(union a a) { while (a); }                    /* {{ dg-error "scalar required" }} */
int bug_do_while(union a a) { do ; while (a); }            /* {{ dg-error "scalar required" }} */
int bug_for(union a a) { for ( ; a; ) ; }                  /* {{ dg-error "scalar required" }} */
int bug_or(union a a) { return (a || 1); }                 /* {{ dg-error "scalar required" }} */
int bug_and(union a a) { return (a && 1); }                /* {{ dg-error "scalar required" }} */
int bug_cond(union a a) { return (a ? 1 : 0); }            /* {{ dg-error "scalar required" }} */
int bug_cond2(union a a) { return (a ? : 0); }             /* {{ dg-error "scalar required" }} */
int bug_bool(union a a) { return (_Bool) a; }              /* {{ dg-error "scalar required" }} */
