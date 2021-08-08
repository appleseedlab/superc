#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "A");
__static_condition_renaming("__static_condition_default_5", "!A");

};

int  __main_3 (void  ) {

{
{



int  __x_0;// L3

char  __x_1;// L5

if (__static_condition_default_4) {
 __x_0  = 1 ; // L8
}
if (__static_condition_default_5) {
 __x_1  = 1 ; // L8
}
if (__static_condition_default_4) {
 __x_0  ++ ; // L10
}
if (__static_condition_default_5) {
 __x_1  ++ ; // L10
}
if (__static_condition_default_4) {
 __x_0  -- ; // L11
}
if (__static_condition_default_5) {
 __x_1  -- ; // L11
}
int  __y_2;// L13

if (__static_condition_default_4) {
 __y_2  =  __x_0  ; // L15
}
if (__static_condition_default_5) {
 __y_2  =  __x_1  ; // L15
}
++  __y_2  ; // L17
--  __y_2  ; // L18
return 0 ;// L20
}
}



}

