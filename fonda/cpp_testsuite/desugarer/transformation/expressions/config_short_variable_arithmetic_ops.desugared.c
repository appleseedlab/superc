#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__z_3", "z");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_5", "A");
__static_condition_renaming("__static_condition_default_6", "!A");

};

int  (__main_4) (void  ) {

{
{



int  __x_0;// L4

char  __x_1;// L6

int  __y_2;// L9

int  __z_3;// L10

if (__static_condition_default_5) {
 __x_0  = 1 ; // L11
}
if (__static_condition_default_6) {
 __x_1  = 1 ; // L11
}
 __y_2  = 2 ; // L12
 __z_3  = 3 ; // L13
if (__static_condition_default_5) {
 __x_0  =  __y_2  +  __z_3  ; // L15
}
if (__static_condition_default_6) {
 __x_1  =  __y_2  +  __z_3  ; // L15
}
if (__static_condition_default_5) {
 __x_0  =  __y_2  -  __z_3  ; // L17
}
if (__static_condition_default_6) {
 __x_1  =  __y_2  -  __z_3  ; // L17
}
if (__static_condition_default_5) {
 __x_0  =  __y_2  *  __z_3  ; // L19
}
if (__static_condition_default_6) {
 __x_1  =  __y_2  *  __z_3  ; // L19
}
if (__static_condition_default_5) {
 __x_0  =  __y_2  /  __z_3  ; // L21
}
if (__static_condition_default_6) {
 __x_1  =  __y_2  /  __z_3  ; // L21
}
if (__static_condition_default_5) {
 __x_0  =  __y_2  %  __z_3  ; // L23
}
if (__static_condition_default_6) {
 __x_1  =  __y_2  %  __z_3  ; // L23
}
return 0 ;// L25
}
}


}

