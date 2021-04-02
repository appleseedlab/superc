#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__x_2", "x");
__static_renaming("__x_5", "x");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_3", "(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

};

float  __x_2 (float  __a_0, float  __b_1) {

{
if (__static_condition_default_3) {
{

if (__static_condition_default_3) {
return  __a_0  *  __b_1  ;

}
}

}

}
}
char  __x_5 (int  __y_4) {

{
if (__static_condition_default_6) {
{

if (__static_condition_default_6) {
return  __y_4  ;

}
}

}

}
}
int  __main_7 () {
{

{
if (__static_condition_default_3) {
 __x_2  ( 3.2, 4.0 ) ;

}

if (__static_condition_default_8) {
__static_type_error("type error") ;

}

}return 0 ;

}


}

