#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_12;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__main_9", "main");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_11", "!(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_12", "(defined CONFIG_A)");

};
struct ____anonymous_tag_0_1 {
int  __a_2;// L3
int  __x_3;// L5
};
struct ____anonymous_tag_4_5 {
int  __a_6;// L3
int  __x_7;// L5
int  __yy_8;// L8
};

struct ____anonymous_tag_0_1 ;// L2
struct ____anonymous_tag_4_5 ;// L2
int  (__main_9) () {

if (__static_condition_default_11) {

{
{



return 0 ;// L14
}
}


}
}
int  (__main_10) () {

if (__static_condition_default_12) {

{
{



return 0 ;// L14
}
}


}
}

