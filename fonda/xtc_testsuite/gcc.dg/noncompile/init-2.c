/* {{ dg-checkwhat "c-analyzer" }} */
int d[][] = { {1}, {2}, {3} };	/* {{ dg-error "incomplete element type" }} */
