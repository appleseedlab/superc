//(2) processing conditional block expressions
//(7) add new definition
#ifdef C1
#define MACRO 1
#elif defined C2
#define MACRO 2
#else
#define MACRO 3 
#endif
 
//(1) expanding macro to multiple definitions
int x = MACRO;

int y = x * MACRO;

//(3) combine multiple streams
#define square(x) (x)*(x)

int z = square(
#ifdef C3
1
#elif defined C4
2
#else
3
#endif
);

//(4) expand function to multiple definitions
#ifdef C5
#define F(x) f1(x)
#elif defined C6
#define F(x) f2(x)
#else C7
#define F(x) f3(x)
#endif

F(1);

//(5) compute guard condition
//(10) rectify self-guarding condition
#include "exercise_bdds.h"
#include "exercise_bdds.h"

//(8) add new definition, overriding a previous one
#define A 1

#define A 2

//(9) add same definition, different configuration
#ifdef C8
#define B 1
#elif defined C9
#define B 1
#endif

