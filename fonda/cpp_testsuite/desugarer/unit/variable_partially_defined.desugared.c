#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_13;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_16;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_3", "a");
__static_renaming("__a_8", "a");
__static_renaming("__x_9", "x");
__static_renaming("__x_10", "x");
__static_renaming("__main_11", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_5", "(defined A) && !(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_12", "(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_13", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_14", "!(defined A) && !(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_15", "!(defined A) && !(defined B) && !(defined C) || (defined A) && !(defined B) && (defined C) || (defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_16", "(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_17", "!(defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_18", "!(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_19", "!(defined A) && !(defined B) && (defined C)");

};

int  __a_0;

char  __a_3;

char char  __a_6;

char char  __a_8;
int  __x_9;
int  __x_10;
int  __main_11 () {
{

{
if (__static_condition_default_12) {
 __a_0  ;

}

if (__static_condition_default_13) {
 __a_3  ;

}

if (__static_condition_default_14) {
 __a_8  ;

}

if (__static_condition_default_15) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_16) {
 __x_9  = 7 *  __a_0  + 2 ;

}

if (__static_condition_default_17) {
 __x_9  = 7 *  __a_3  + 2 ;

}

if (__static_condition_default_18) {
 __x_10  = 7 *  __a_3  + 2 ;

}

if (__static_condition_default_19) {
 __x_10  = 7 *  __a_8  + 2 ;

}

}}


}

