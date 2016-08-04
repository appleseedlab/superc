/* {{ dg-checkwhat "c-analyzer" }} */
struct s{struct s{int i;}x;};	/* {{ dg-error "redefinition" }} */
