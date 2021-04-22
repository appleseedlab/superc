#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__x_5", "x");
__static_renaming("__x_6", "x");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A)");
__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_7", "!(defined A)");

if (0)
{
__static_parse_error("Unable to parse");
}
};

float  __x_5 (float  __a_0, float  __b_1) {

{
if (__static_condition_default_2) {
{

if (__static_condition_default_2) {
return  __a_0  *  __b_1  ;

}
}

}

}
}
char  __x_6 (int  __y_3) {

{
if (__static_condition_default_4) {
{

if (__static_condition_default_4) {
return  __y_3  ;

}
}

}

}
}
int  __main_8 () {
{

{
if (__static_condition_default_2) {
 __x_5  ( 3.2, 4.0 ) ;

}

if (__static_condition_default_7) {
__static_type_error("type error") ;

}

}return 0 ;

}


}

