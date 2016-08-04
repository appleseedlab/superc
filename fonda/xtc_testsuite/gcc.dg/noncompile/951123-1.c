/* {{ dg-checkwhat "c-parser" }} */
struct S { int a; int b[2]; };
struct S x = { 0, [0]; };    /* {{ dg-error "expected" }} */
