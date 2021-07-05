#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_3", "a");
__static_renaming("__x_5", "x");
__static_renaming("__x_6", "x");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_4", "(defined C)");
__static_condition_renaming("__static_condition_default_8", "(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_9", "!(defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_10", "!(defined A) && !(defined B) || !(defined A) && (defined B) && (defined C) || (defined A) && !(defined B) && (defined C) || (defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_11", "(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_12", "!(defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_13", "!(defined A) && !(defined B) || !(defined A) && (defined B) && (defined C) || (defined A) && !(defined B) && (defined C) || (defined A) && (defined B)");

};

int  __a_0;

char  __a_3;
int  __x_5;
int  __x_6;
int  __main_7 () {

{



if (__static_condition_default_8) {
 __a_0  ;
}
if (__static_condition_default_9) {
 __a_3  ;
}
if (__static_condition_default_10) {
__static_type_error("type error") ;
}
if (__static_condition_default_11) {
 __x_5  = 7 *  __a_0  + 2 ;
}
if (__static_condition_default_12) {
 __x_5  = 7 *  __a_3  + 2 ;
}
if (__static_condition_default_13) {
__static_type_error("type error") ;
}
}



}

