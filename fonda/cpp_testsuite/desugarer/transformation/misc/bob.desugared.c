#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_2", "(defined CONFIG_B) && !(defined CONFIG_C)");
__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_B) && (defined CONFIG_C)");
__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_B) && (defined CONFIG_C)");
__static_condition_renaming("__static_condition_default_5", "(defined CONFIG_B) && !(defined CONFIG_C)");
__static_condition_renaming("__static_condition_default_6", "(defined CONFIG_B)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_B)");

};

int  __main_7 () {

if (__static_condition_default_8) {
{
int  __x_0;
int  __y_1;

{
if (__static_condition_default_2) {
__static_type_error("type error : no valid expression");

}

if (__static_condition_default_3) {
 __y_1  = 4 ;

}

}
{
if (__static_condition_default_4) {
 __x_0  =  __y_1  ;

}

if (__static_condition_default_5) {
__static_type_error("type error") ;

}

}
if (__static_condition_default_6) {
 __x_0  ++ ;

}

if (__static_condition_default_6) {
return  __x_0  ;

}
}

}

}

