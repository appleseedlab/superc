#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_3", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_1", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");
__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");

};

int  __x_0 () {

{
if (__static_condition_default_1) {
{

if (__static_condition_default_1) {
return 1 ;

}
}

}

}
}
char  __x_3 (int  __y_2) {

{
if (__static_condition_default_4) {
{

if (__static_condition_default_4) {
return  __y_2  ;

}
}

}

}
}
int  __main_5 () {
{

{
if (__static_condition_default_1) {
 __x_0  ( ) ;

}

if (__static_condition_default_6) {
 __x_3  ( ) ;

}

}
{
if (__static_condition_default_1) {
__static_type_error("too many arguments to function") ;

}

if (__static_condition_default_6) {
 __x_3  ( 2 ) ;

}

}}


}

