// {{ dg-preprocess "Need preprocessing" }}
#define empty
#if defined(empty) /* #cpu(m68k) --- assertions are deprecated */
#endif

f (){}
