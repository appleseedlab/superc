#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_2", "y");
__static_renaming("__y_3", "y");

__static_condition_renaming("__static_condition_default_1", "(defined A)");
__static_condition_renaming("__static_condition_default_4", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_5", "(defined A) && (defined B)");

};

void  __x_0 () {

if (__static_condition_default_1) {

{
{



}
}


}
}
void  __y_2 () {

if (__static_condition_default_4) {

{
{



}
}


}
}
void  __y_3 () {

if (__static_condition_default_5) {

{
{



}
}


}
}

