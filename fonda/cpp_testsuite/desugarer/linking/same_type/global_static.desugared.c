#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__f_2", "f");
__static_renaming("__f_3", "f");

__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_5", "!(defined CONFIG_A)");

};

int  __f_2 (int  __x_0) {

{
if (__static_condition_default_4) {

{
{



return  __x_0  + 1 ;// L4
}
}


}

}}
static int  __f_3 (int  __x_1) {

{
if (__static_condition_default_5) {

{
{



return  __x_1  - 1 ;// L8
}
}


}

}}

