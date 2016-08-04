/* {{ dg-checkwhat "c-analyzer" }} */
int i = 7 / 0;  /* {{ dg-warning "division by zero" }} */
/* {{ dg-error "not constant" 2 }} */


