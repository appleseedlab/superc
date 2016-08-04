/* {{ dg-checkwhat "c-analyzer" }} */
struct a { char *b; } c[D]; /* {{ dg-error "undeclared" }} */
