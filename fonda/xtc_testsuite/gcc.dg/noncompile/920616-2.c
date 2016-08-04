/* {{ dg-checkwhat "c-analyzer" }} */
f(void a,...){}	 /* {{ dg-error "has incomplete type" }} */
