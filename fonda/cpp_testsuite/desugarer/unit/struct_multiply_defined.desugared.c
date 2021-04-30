#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__var_joe_8", "var_joe");
__static_renaming("__var_joe_9", "var_joe");


};
struct __anonymous_tag_0 {
int  __x_1;
};
struct __anonymous_tag_2 {
int  __yy_3;
};
struct __anonymous_tag_4 {
int  __y_5;
};
struct __anonymous_tag_6 {
int  __xx_7;
};

struct __anonymous_tag_0 ;
struct __anonymous_tag_4 ;
struct __anonymous_tag_2  __var_joe_8;
struct __anonymous_tag_6  __var_joe_9;

