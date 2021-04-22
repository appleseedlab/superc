#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__var_joe_8", "var_joe");
__static_renaming("__var_joe_9", "var_joe");
__static_renaming("__var_10", "var");
__static_renaming("__var_11", "var");


if (0)
{
__static_parse_error("Unable to parse");
}
};
struct __bob_0 {
int  __x_1;
};
struct __joe_2 {
int  __yy_3;
};
struct __bob_4 {
int  __y_5;
};
struct __joe_6 {
int  __xx_7;
};

struct __bob_0 ;
struct __bob_4 ;
struct __joe_2  __var_joe_8;
struct __joe_6  __var_joe_9;
struct __bob_0  __var_10;
struct __bob_4  __var_11;

