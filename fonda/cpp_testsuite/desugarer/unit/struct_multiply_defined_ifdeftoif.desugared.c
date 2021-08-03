#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("___1_var_joe_4", "_1_var_joe");
__static_renaming("___2_var_joe_9", "_2_var_joe");


};
struct __anonymous_tag_0 {
int  __x_1;
};
struct __anonymous_tag_2 {
int  __yy_3;
};
struct __anonymous_tag_5 {
int  __y_6;
};
struct __anonymous_tag_7 {
int  __xx_8;
};

struct __anonymous_tag_0 ;// L2
struct __anonymous_tag_2  ___1_var_joe_4;// L5:L7
struct __anonymous_tag_5 ;// L8
struct __anonymous_tag_7  ___2_var_joe_9;// L11:L13

