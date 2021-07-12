#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__main_1", "main");

__static_condition_renaming("__static_condition_default_2", "(defined CONFIG_B)");
__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_5", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_6", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_7", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_B) && !(defined CONFIG_A)");

};

int  __main_1 () {

if (__static_condition_default_2) {

{



int  __x_0;

if (__static_condition_default_3) {
__static_type_error("type error : no valid expression") // L7
}
if (__static_condition_default_4) {
 __x_0  = 2 ; // L7
}
if (__static_condition_default_5) {
 __x_0  ++ ; // L8
}
if (__static_condition_default_6) {
__static_type_error("type error") ; // L8
}
if (__static_condition_default_7) {
return  __x_0  ;// L10
}
if (__static_condition_default_8) {
__static_type_error("invalid type found in return expression");
}
}


}

}

