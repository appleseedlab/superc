/* PR/11658  The error message was quite mysterious for gcc up to 3.4.x */
/* {{ dg-checkwhat "c-analyzer" }} */

// Note that this file actually compiles under C99. It's only gcc
// that's a little out of whack and can't pointerize the nested array.

struct s { char c[1]; };
struct s f(void);

int bug_if(void) { if (f().c) return 1; else return 0; }
int bug_while(void) { while (f().c); }
int bug_do_while(void) { do ; while (f().c); }
int bug_for(void) { for ( ; f().c; ) ; }
int bug_or(void) { return (f().c || 1); }
int bug_and(void) { return (f().c && 1); }
int bug_cond(void) { return (f().c ? 1 : 0); }
int bug_cond2(void) { return (f().c ? : 0); } // {{ dg-warning "makes integer" }}
int bug_not(void) { return !f().c; }
int bug_bool(void) { return (_Bool) f().c; }
