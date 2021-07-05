#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__z_3", "z");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_5", "A");
__static_condition_renaming("__static_condition_default_6", "!A");

};

int  __main_4 (void  ) {

{



int  __x_0;

char  __x_1;

int  __y_2;

int  __z_3;

 __y_2  = 2 ;
 __z_3  = 4 ;
if (__static_condition_default_5) {
 __x_0  = 3 + 5 ;
}
if (__static_condition_default_6) {
 __x_1  = 3 + 5 ;
}
if (__static_condition_default_5) {
 __x_0  =  __x_0  +  __z_3  -  __y_2  ;
}
if (__static_condition_default_6) {
 __x_1  =  __x_1  +  __z_3  -  __y_2  ;
}
if (__static_condition_default_5) {
 __x_0  =  __x_0  / 4 ;
}
if (__static_condition_default_6) {
 __x_1  =  __x_1  / 4 ;
}
if (__static_condition_default_5) {
 __x_0  = 2 *  __y_2  ;
}
if (__static_condition_default_6) {
 __x_1  = 2 *  __y_2  ;
}
if (__static_condition_default_5) {
 __x_0  =  __z_3  % 5 ;
}
if (__static_condition_default_6) {
 __x_1  =  __z_3  % 5 ;
}
if (__static_condition_default_5) {
 __x_0  += 1 ;
}
if (__static_condition_default_6) {
 __x_1  += 1 ;
}
if (__static_condition_default_5) {
 __x_0  -= 2 ;
}
if (__static_condition_default_6) {
 __x_1  -= 2 ;
}
if (__static_condition_default_5) {
 __x_0  *= 5 ;
}
if (__static_condition_default_6) {
 __x_1  *= 5 ;
}
if (__static_condition_default_5) {
 __x_0  /= 3 ;
}
if (__static_condition_default_6) {
 __x_1  /= 3 ;
}
if (__static_condition_default_5) {
 __x_0  %= 4 ;
}
if (__static_condition_default_6) {
 __x_1  %= 4 ;
}
return 0 ;
}



}

