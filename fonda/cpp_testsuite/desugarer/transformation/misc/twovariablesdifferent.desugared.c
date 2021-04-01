#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_15;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_14;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__y_3", "y");
__static_renaming("__y_6", "y");

__static_condition_renaming("__static_condition_default_5", "(defined CONFIG_B) && (defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_7", "(defined CONFIG_B) && (defined CONFIG_C) && !(defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_B) && !(defined CONFIG_C) && !(defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_9", "(defined CONFIG_B) && !(defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_10", "(defined CONFIG_B) && (defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_B) && (defined CONFIG_A) && (defined CONFIG_C) && !(defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_12", "(defined CONFIG_B) && (defined CONFIG_A) && !(defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_13", "(defined CONFIG_B) && !(defined CONFIG_A) && (defined CONFIG_C) && !(defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_14", "(defined CONFIG_B) && !(defined CONFIG_A) && !(defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_15", "(defined CONFIG_B) && !(defined CONFIG_C) && !(defined CONFIG_D) || (defined CONFIG_B) && (defined CONFIG_C) && (defined CONFIG_D)");
__static_condition_renaming("__static_condition_default_16", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_17", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_18", "(defined CONFIG_B) && (defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_19", "(defined CONFIG_B) && !(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_20", "(defined CONFIG_B)");

};

int  __main_0 () {

if (__static_condition_default_20) {
{
int  __x_1;
char  __x_2;
int  __y_3;
if (__static_condition_default_5) {
__static_type_error("redeclaration of local symbol: y");
}

char  __y_6;

{
if (__static_condition_default_7) {
 __y_3  = 4 ;

}

if (__static_condition_default_8) {
__static_type_error("type error") ;

}

if (__static_condition_default_9) {
 __y_6  = 4 ;

}

if (__static_condition_default_10) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_11) {
 __x_1  =  __y_3  ;

}

if (__static_condition_default_12) {
 __x_1  =  __y_6  ;

}

if (__static_condition_default_13) {
 __x_2  =  __y_3  ;

}

if (__static_condition_default_14) {
 __x_2  =  __y_6  ;

}

if (__static_condition_default_15) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_16) {
 __x_1  ++ ;

}

if (__static_condition_default_17) {
 __x_2  ++ ;

}

}
{
if (__static_condition_default_18) {
return  __x_1  ;

}

if (__static_condition_default_19) {
return  __x_2  ;

}

}}

}

}

