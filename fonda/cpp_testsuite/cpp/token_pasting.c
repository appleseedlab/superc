#define OBJECT ID ## 1
OBJECT
#define f(x) ID_ ## x
f(1 2 3)
f(OBJECT)
f(a ## 1)
#define X PREFIX_ ## OBJECT
X
#define MACRO token
#define EXPAND MAC ## RO
EXPAND
f(MACRO)
f(
#define Y y macro
Y)
#undef Y
f(1
#define Y y macro
Y)
#define id(x) x
id(a ## 1)
#define DOUBLEHASH # ## #
DOUBLEHASH
#define SYMBOL < ## =
SYMBOL
#define FOO(x) x ## _ID
FOO(1 2 3)
FOO(1 ## 2)
