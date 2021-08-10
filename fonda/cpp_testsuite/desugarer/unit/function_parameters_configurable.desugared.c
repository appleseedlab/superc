#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__z_4", "z");
__static_renaming("__z_5", "z");
__static_renaming("__f_6", "f");
__static_renaming("__f_7", "f");

__static_condition_renaming("__static_condition_default_3", "(defined B)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");
__static_condition_renaming("__static_condition_default_9", "!(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_10", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_11", "(defined A)");
__static_condition_renaming("__static_condition_default_12", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_13", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_14", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_15", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_16", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_17", "(defined A) && (defined B)");

};

int  __f_6 (char  __x_0) {

if (__static_condition_default_8) {

{
{



if (__static_condition_default_3) {
__static_type_error("redeclaration of local symbol: x");
}


int  __z_4;// L9

int  __z_5;// L9

__static_type_error("type error") ; // L11
__static_type_error("type error") ; // L13
if (__static_condition_default_9) {
return  __z_4  ;// L15
}
if (__static_condition_default_10) {
return  __z_5  ;// L15
}
}
}


}
}
int  __f_7 (char  __x_0, int  __y_1) {

if (__static_condition_default_11) {

{
{



if (__static_condition_default_3) {
__static_type_error("redeclaration of local symbol: x");
}


int  __z_4;// L9

int  __z_5;// L9

if (__static_condition_default_12) {
 __y_1  =  __x_0  +  __y_1  ; // L11
}
if (__static_condition_default_13) {
__static_type_error("type error") ; // L11
}
if (__static_condition_default_14) {
 __z_4  =  __y_1  ; // L13
}
if (__static_condition_default_15) {
 __z_5  =  __y_1  ; // L13
}
if (__static_condition_default_16) {
return  __z_4  ;// L15
}
if (__static_condition_default_17) {
return  __z_5  ;// L15
}
}
}


}
}

