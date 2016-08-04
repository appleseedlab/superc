// Test whether the open paren can be controlled by a conditional.

/* #define F(x) G */
/* #define G(x) expanded */

/* F(ys) */
/* #ifdef A */
/* ( */
/* #endif */
/* yo */
/*  ) */


#define F(x) expanded
#define M (
#define G(x) x in G

G(F M)

