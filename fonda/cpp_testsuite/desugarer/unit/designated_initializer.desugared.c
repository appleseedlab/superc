#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__bob_4", "bob");
__static_renaming("__main_5", "main");


};
struct __anonymous_tag_0 {
int  __f_1;
};
struct __s_2 {
struct __anonymous_tag_0  (__x_3[4]);
};

struct __s_2  __bob_4= { .x = { [0].f = 10 } };// L1:L3
int  __main_5 () {

{
{



}
}



}

