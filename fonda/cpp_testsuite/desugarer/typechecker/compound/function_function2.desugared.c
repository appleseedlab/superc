#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__x_2", "x");
__static_renaming("__x_5", "x");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_3", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");
__static_condition_renaming("__static_condition_default_8", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");

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
__static_type_error("too few arguments to function") ;

}

if (__static_condition_default_8) {
 __x_5  ( 7 ) ;

}

}return 0 ;

}


}

