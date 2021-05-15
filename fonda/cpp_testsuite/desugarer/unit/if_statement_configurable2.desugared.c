#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_10;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__z_2", "z");
__static_renaming("__main_11", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined C)");
__static_condition_renaming("__static_condition_default_4", "(defined A) && !(defined C)");
__static_condition_renaming("__static_condition_default_5", "(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_6", "(defined C)");
__static_condition_renaming("__static_condition_default_7", "(defined A) && (defined C)");
__static_condition_renaming("__static_condition_default_8", "(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_9", "(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_10", "!(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_12", "(defined A) && !(defined C)");
__static_condition_renaming("__static_condition_default_13", "(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_14", "(defined A) && (defined C)");
__static_condition_renaming("__static_condition_default_15", "(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_16", "(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_17", "!(defined B) && (defined C)");

};

int  __main_11 () {

{



int  __x_0;
int  __y_1;
int  __z_2;

if (  __x_0  )
if (__static_condition_default_3) {

{



if (__static_condition_default_12) {
 __x_0  ++ ;
}
if (__static_condition_default_13) {
 __y_1  ++ ;
}
}
}
if (__static_condition_default_6) {

{



if (__static_condition_default_14) {
 __x_0  ++ ;
}
if (__static_condition_default_15) {
 __y_1  ++ ;
}
if (__static_condition_default_16) {
 __z_2  ++ ;
}
if (__static_condition_default_17) {
 __z_2  ++ ;
}
}
}
}



}

