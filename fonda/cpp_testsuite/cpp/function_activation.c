extern void foo(void);
#define foo() expansion
foo();
funcptr = foo;
