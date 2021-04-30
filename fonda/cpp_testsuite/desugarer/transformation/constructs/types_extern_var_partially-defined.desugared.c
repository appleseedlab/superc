#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__main_3", "main");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_1", "(defined A)");
__static_condition_renaming("__static_condition_default_2", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "(defined A)");

};

extern int  __x_0;
int  __main_3 () {

if (__static_condition_default_5) {
{

{
if (__static_condition_default_1) {
 __x_0  ++ ;

}

if (__static_condition_default_2) {
__static_type_error("type error") ;

}

}}

}

}
int  __main_4 () {

if (__static_condition_default_6) {
{

{
if (__static_condition_default_1) {
 __x_0  ++ ;

}

if (__static_condition_default_2) {
__static_type_error("type error") ;

}

}}

}

}

