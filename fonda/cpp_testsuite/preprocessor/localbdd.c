//define M under A and !A
#if A
#define M BOB
#else
#define M JOE
#endif

//use M under just A
#if A
M
#endif

//use M under TRUE
M

//conditional block with elifs
#if A
1
#elif B
2
#elif C
3
#else
4
#endif

