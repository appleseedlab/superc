#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__var_joe_12", "var_joe");
__static_renaming("__var_joe_13", "var_joe");


};
struct ____anonymous_tag_0_1 {
int  __x_2;// L3
};
struct ____anonymous_tag_3_4 {
int  __yy_5;// L6
};
struct ____anonymous_tag_6_7 {
int  __y_8;// L10
};
struct ____anonymous_tag_9_10 {
int  __xx_11;// L13
};

struct ____anonymous_tag_0_1 ;// L2
struct ____anonymous_tag_6_7 ;// L9
struct ____anonymous_tag_3_4  __var_joe_12;// L5:L7
struct ____anonymous_tag_9_10  __var_joe_13;// L12:L14

