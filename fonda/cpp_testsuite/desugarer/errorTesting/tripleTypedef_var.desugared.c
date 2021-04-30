#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__c_2", "c");
__static_renaming("__k_3", "k");
__static_renaming("__main_7", "main");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A) && !(defined C) || (defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_5", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_6", "!(defined A) || (defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_9", "!(defined C)");
__static_condition_renaming("__static_condition_default_10", "(defined C)");
__static_condition_renaming("__static_condition_default_11", "!(defined A)");

if (__static_condition_default_11)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __a_0;
typedef int  __b_1;
typedef int  __c_2;

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
int  __main_7 () {

if (__static_condition_default_9) {
{
__c_2  __k_3;
if (__static_condition_default_4) {
__static_type_error("invalid declaration of k under this presence condition");
}

{
if (__static_condition_default_5) {
return 0 ;

}

if (__static_condition_default_6) {
return 0 ;

}

}}

}

}
int  __main_8 () {

if (__static_condition_default_10) {
{
__c_2  __k_3;
if (__static_condition_default_4) {
__static_type_error("invalid declaration of k under this presence condition");
}

{
if (__static_condition_default_5) {
return 0 ;

}

if (__static_condition_default_6) {
return 0 ;

}

}}

}

}

