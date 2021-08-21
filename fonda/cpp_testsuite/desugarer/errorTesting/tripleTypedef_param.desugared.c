#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_18;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_17;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__c_2", "c");
__static_renaming("__foo_8", "foo");
__static_renaming("__foo_9", "foo");
__static_renaming("__foo_10", "foo");
__static_renaming("__foo_12", "foo");
__static_renaming("__main_19", "main");

__static_condition_renaming("__static_condition_default_11", "!(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_13", "!(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_14", "(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_15", "!(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_16", "(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_17", "(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_18", "(defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_20", "!(defined B) && (defined C)");

if (__static_condition_default_20)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __a_0;// L2
typedef int  __b_1;// L6
typedef int  __c_2;// L10

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
void  (__foo_8) () {

if (__static_condition_default_13) {

{
{



if (__static_condition_default_14) {
__static_type_error("type error") ; // L23
}
return  ;// L31
}
}


}
}
void  (__foo_9) () {

if (__static_condition_default_15) {


}
}
void  (__foo_10) (__a_0  __x_3, __c_2  __z_5, __b_1  __y_7) {

if (__static_condition_default_16) {

{
{



 __x_3  = 2 ; // L23
 __y_7  = 2 ; // L26
 __z_5  = 2 ; // L29
return  ;// L31
}
}


}
}
void  (__foo_12) (__b_1  __y_6) {

if (__static_condition_default_17) {

{
{



if (__static_condition_default_18) {
__static_type_error("type error") ; // L23
}
 __y_6  = 2 ; // L26
return  ;// L31
}
}


}
}
int  (__main_19) () {

{
{



return 0 ;// L36
}
}


}

