#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A)");
__static_condition_renaming("__static_condition_default_3", "!(defined A)");

};

int  __x_0 () {

if (__static_condition_default_2) {

{
{



return 1 ;// L8
}
}


}
}
char  __x_1 () {

if (__static_condition_default_3) {

{
{



return 1 ;// L8
}
}


}
}
int  __main_4 () {

{
{



if (__static_condition_default_2) {
 __x_0 ( ) ; // L13
}
if (__static_condition_default_3) {
 __x_1 ( ) ; // L13
}
}
}


}

