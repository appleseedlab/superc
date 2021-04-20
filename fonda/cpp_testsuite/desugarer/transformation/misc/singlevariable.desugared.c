#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_1;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_1", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_2", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_5", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_6", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_B)");

};

int  __main_7 () {

if (__static_condition_default_8) {
{
int  __x_0;

{
if (__static_condition_default_1) {
__static_type_error("type error : no valid expression");

}

if (__static_condition_default_2) {
 __x_0  = 2 ;

}

}
{
if (__static_condition_default_3) {
 __x_0  ++ ;

}

if (__static_condition_default_4) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_5) {
return  __x_0  ;

}

if (__static_condition_default_6) {
__static_type_error("invalid type found in return expression");

}

}}

}

}

