/* #ifdef __ASSEMBLY__ */
/* #define _AC(X,Y)        X */
/* #define _AT(T,X)        X */
/* #else */
/* #define __AC(X,Y)       (X##Y) */
/* #define _AC(X,Y)        __AC(X,Y) */
/* #define _AT(T,X)        ((T)(X)) */
/* #endif */


/* #ifdef CONFIG_ILLEGAL_POINTER_VALUE */
/* # define POISON_POINTER_DELTA _AC(CONFIG_ILLEGAL_POINTER_VALUE, UL) */
/* #else */
/* # define POISON_POINTER_DELTA 0 */
/* #endif */

/* # define POISON_POINTER_DELTA _AC(CONFIG_ILLEGAL_POINTER_VALUE, UL) */

/* #define LIST_POISON1  ((void *) 0x00100100 + POISON_POINTER_DELTA) */

/* LIST_POISON1 */

#define CONFIG_ILLEGAL_POINTER_VALUE 0xdead000000000000

#define __AC(X,Y)       (X##Y)
#define _AC(X,Y)        __AC(X,Y)
#define POISON_POINTER_DELTA _AC(CONFIG_ILLEGAL_POINTER_VALUE, UL)

POISON_POINTER_DELTA
