#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__z_2", "z");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined C)");
__static_condition_renaming("__static_condition_default_5", "(defined A) && !(defined C)");
__static_condition_renaming("__static_condition_default_6", "(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_7", "(defined C)");
__static_condition_renaming("__static_condition_default_8", "(defined A) && (defined C)");
__static_condition_renaming("__static_condition_default_9", "(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_10", "(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_11", "!(defined B) && (defined C)");

};

 int  __main_3 () {

{



int  __x_0;
int  __y_1;
int  __z_2;

if (  __x_0  )
if (__static_condition_default_4) {

{



if (__static_condition_default_5) {
 __x_0  ++ ;
}
if (__static_condition_default_6) {
 __y_1  ++ ;
}
}
}
if (__static_condition_default_7) {

{



if (__static_condition_default_8) {
 __x_0  ++ ;
}
if (__static_condition_default_9) {
 __y_1  ++ ;
}
if (__static_condition_default_10) {
 __z_2  ++ ;
}
if (__static_condition_default_11) {
 __z_2  ++ ;
}
}
}
}



}

