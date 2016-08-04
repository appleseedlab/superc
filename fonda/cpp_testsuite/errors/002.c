#define PASTE(x) % ## x
PASTE(
#ifndef A
^
#else
&
#endif
)
after
