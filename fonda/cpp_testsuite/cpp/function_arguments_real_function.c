#define _SIG_SET_BINOP(name, op) op(a3, b3);                                 

#define _sig_or(x,y)    ((x) | (y))
_SIG_SET_BINOP(sigorsets, _sig_or)
