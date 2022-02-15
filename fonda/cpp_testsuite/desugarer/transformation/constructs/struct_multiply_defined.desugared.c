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


};
struct __bob_0 {
int  __x_1;// L3
};
struct __joe_2 {
int  __yy_3;// L6
};
struct __bob_4 {
int  __y_5;// L10
};
struct __joe_6 {
int  __xx_7;// L13
};

struct __bob_0 ;// L2
struct __bob_4 ;// L9
struct __joe_2  __var_joe_8;// L5:L7
struct __joe_6  __var_joe_9;// L12:L14
struct __bob_0  __var_10;// L17
struct __bob_4  __var_11;// L17

