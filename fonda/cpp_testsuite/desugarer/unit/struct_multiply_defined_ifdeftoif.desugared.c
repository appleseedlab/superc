#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("___1_var_joe_6", "_1_var_joe");
__static_renaming("___2_var_joe_13", "_2_var_joe");


};
struct ____anonymous_tag_0_1 {
int  __x_2;
};
struct ____anonymous_tag_3_4 {
int  __yy_5;
};
struct ____anonymous_tag_7_8 {
int  __y_9;
};
struct ____anonymous_tag_10_11 {
int  __xx_12;
};

struct ____anonymous_tag_0_1 ;// L2
struct ____anonymous_tag_3_4  ___1_var_joe_6;// L5:L7
struct ____anonymous_tag_7_8 ;// L8
struct ____anonymous_tag_10_11  ___2_var_joe_13;// L11:L13

