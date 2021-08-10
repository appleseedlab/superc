#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_12;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__c_2", "c");
__static_renaming("__k_3", "k");
__static_renaming("__main_5", "main");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A) && !(defined C) || (defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_7", "!(defined C)");
__static_condition_renaming("__static_condition_default_8", "(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_9", "!(defined A) && !(defined C) || (defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_10", "(defined C)");
__static_condition_renaming("__static_condition_default_11", "(defined A) && !(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_12", "!(defined A) && (defined C) || (defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_13", "!(defined A)");

if (__static_condition_default_13)
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
int  __main_5 () {

if (__static_condition_default_7) {

{
{



if (__static_condition_default_4) {
__static_type_error("invalid declaration of k under this presence condition");
}

if (__static_condition_default_8) {
return 0 ;// L23
}
if (__static_condition_default_9) {
return 0 ;// L23
}
}
}


}
}
int  __main_6 () {

if (__static_condition_default_10) {

{
{



__c_2  __k_3;// L21

if (__static_condition_default_11) {
return 0 ;// L23
}
if (__static_condition_default_12) {
return 0 ;// L23
}
}
}


}
}

