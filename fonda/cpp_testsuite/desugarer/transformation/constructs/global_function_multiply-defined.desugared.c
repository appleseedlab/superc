#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_2", "x");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_1", "(defined A)");
__static_condition_renaming("__static_condition_default_3", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

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
char  __x_2 () {

{
if (__static_condition_default_3) {
{

if (__static_condition_default_3) {
return 2 ;

}
}

}

}
}
int  __main_4 () {
{

{
if (__static_condition_default_1) {
 __x_0  ( ) ;

}

if (__static_condition_default_5) {
 __x_2  ( ) ;

}

}}


}

