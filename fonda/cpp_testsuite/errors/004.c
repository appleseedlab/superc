#define PASTE(x, y) x ## y
PASTE(
#ifndef A
^
#else
&
#endif
,
#ifndef B
*
#else
|
#endif
)
after
