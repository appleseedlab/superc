#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_18;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__y_5", "y");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_B) && (defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_7", "(defined CONFIG_B)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_B) && (defined CONFIG_C) && !(defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_9", "(defined CONFIG_B) && !(defined CONFIG_C) && !(defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_10", "(defined CONFIG_B) && !(defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_B) && (defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_12", "(defined CONFIG_B) && (defined CONFIG_A) && (defined CONFIG_C) && !(defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_13", "(defined CONFIG_B) && (defined CONFIG_A) && !(defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_14", "(defined CONFIG_B) && !(defined CONFIG_A) && (defined CONFIG_C) && !(defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_15", "(defined CONFIG_B) && !(defined CONFIG_A) && !(defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_16", "(defined CONFIG_B) && !(defined CONFIG_C) && !(defined CONFIG_D) || (defined CONFIG_B) && (defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_17", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_18", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_19", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_20", "(defined CONFIG_B) && !(defined CONFIG_A)");

};

int  __main_6 () {

if (__static_condition_default_7) {

{
{



int  __x_0;// L4

char  __x_1;// L6

int  __y_2;// L9

if (__static_condition_default_4) {
__static_type_error("redeclaration of local symbol: y");
}

char  __y_5;// L12

if (__static_condition_default_8) {
 __y_2  = 4 ; // L15
}
if (__static_condition_default_9) {
__static_type_error("type error") ; // L15
}
if (__static_condition_default_10) {
 __y_5  = 4 ; // L15
}
if (__static_condition_default_11) {
__static_type_error("type error") ; // L15
}
if (__static_condition_default_12) {
 __x_0  =  __y_2  ; // L16
}
if (__static_condition_default_13) {
 __x_0  =  __y_5  ; // L16
}
if (__static_condition_default_14) {
 __x_1  =  __y_2  ; // L16
}
if (__static_condition_default_15) {
 __x_1  =  __y_5  ; // L16
}
if (__static_condition_default_16) {
__static_type_error("type error") ; // L16
}
if (__static_condition_default_17) {
 __x_0  ++ ; // L17
}
if (__static_condition_default_18) {
 __x_1  ++ ; // L17
}
if (__static_condition_default_19) {
return  __x_0  ;// L19
}
if (__static_condition_default_20) {
return  __x_1  ;// L19
}
}
}


}
}

