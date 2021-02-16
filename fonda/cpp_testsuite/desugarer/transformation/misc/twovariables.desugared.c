#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_11;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");

__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_B) && !(defined CONFIG_C)");
__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_B) && (defined CONFIG_C)");
__static_condition_renaming("__static_condition_default_5", "(defined CONFIG_B) && (defined CONFIG_A) && (defined CONFIG_C)");
__static_condition_renaming("__static_condition_default_6", "(defined CONFIG_B) && !(defined CONFIG_A) || (defined CONFIG_B) && (defined CONFIG_A) && !(defined CONFIG_C)");
__static_condition_renaming("__static_condition_default_7", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_9", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_10", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_B)");

};

int  __main_0 () {

if (__static_condition_default_11) {
{
int  __x_1;
int  __y_2;

{
if (__static_condition_default_3) {
__static_type_error("type error");

}

if (__static_condition_default_4) {
 __y_2  = 4 ;

}

}
{
if (__static_condition_default_5) {
 __x_1  =  __y_2  ;

}

if (__static_condition_default_6) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_7) {
 __x_1  ++ ;

}

if (__static_condition_default_8) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_9) {
return  __x_1  ;

}

if (__static_condition_default_10) {
__static_type_error("invalid type found in return expression");

}

}}

}

}

