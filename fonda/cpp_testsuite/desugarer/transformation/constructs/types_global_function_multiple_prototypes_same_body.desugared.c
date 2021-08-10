#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_14;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__b_1", "b");
__static_renaming("__x_2", "x");
__static_renaming("__x_3", "x");
__static_renaming("__x_4", "x");
__static_renaming("__x_5", "x");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_6", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_7", "!(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_8", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_9", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_11", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_12", "!(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_13", "(defined B)");
__static_condition_renaming("__static_condition_default_14", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_15", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_16", "!(defined B)");

};

int  __x_2 () {

if (__static_condition_default_6) {

{
{



int  __b_1= 1;// L12

__static_type_error("type error") ; // L14
return  __b_1  ;// L15
}
}


}
}
char  __x_3 () {

if (__static_condition_default_7) {

{
{



int  __b_1= 1;// L12

__static_type_error("type error") ; // L14
return  __b_1  ;// L15
}
}


}
}
int  __x_4 (int  __y_0) {

if (__static_condition_default_8) {

{
{



int  __b_1= 1;// L12

 __b_1  =  __b_1  +  __y_0  ; // L14
return  __b_1  ;// L15
}
}


}
}
char  __x_5 (int  __y_0) {

if (__static_condition_default_9) {

{
{



int  __b_1= 1;// L12

 __b_1  =  __b_1  +  __y_0  ; // L14
return  __b_1  ;// L15
}
}


}
}
int  __main_10 () {

{
{



if (__static_condition_default_11) {
 __x_2 ( ) ; // L20
}
if (__static_condition_default_12) {
 __x_3 ( ) ; // L20
}
if (__static_condition_default_13) {
__static_type_error("type error") ; // L20
}
if (__static_condition_default_14) {
 __x_4  (2) ; // L21
}
if (__static_condition_default_15) {
 __x_5  (2) ; // L21
}
if (__static_condition_default_16) {
__static_type_error("type error") ; // L21
}
}
}


}

