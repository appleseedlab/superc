#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__foo_2", "foo");
__static_renaming("__foo_3", "foo");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A)");
__static_condition_renaming("__static_condition_default_7", "!(defined X)");
__static_condition_renaming("__static_condition_default_8", "!(defined A) || (defined A) && (defined X)");

if (__static_condition_default_8)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __x_0;

// typedef moved to top of scope
void  __foo_2 () {

if (__static_condition_default_4) {
{
return  ;

}

}

}
void  __foo_3 (__x_0  __a_1) {

if (__static_condition_default_5) {
{
return  ;

}

}

}
int  __main_6 () {

if (__static_condition_default_7) {
{

{
if (__static_condition_default_5) {
 __foo_3  ( 1 ) ;

}

if (__static_condition_default_4) {
__static_type_error("type error") ;

}

}return 0 ;

}

}

}

