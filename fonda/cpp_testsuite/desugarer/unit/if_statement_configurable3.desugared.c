#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__z_2", "z");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_3", "(defined A)");
__static_condition_renaming("__static_condition_default_4", "(defined B)");
__static_condition_renaming("__static_condition_default_5", "(defined C)");
__static_condition_renaming("__static_condition_default_6", "!(defined C)");

};

int  __main_7 () {
{
int  __x_0;
int  __y_1;
int  __z_2;
if (  __x_0  ) {
 __x_0  -- ;


if (__static_condition_default_3) {
 __x_0  ++ ;

}

if (__static_condition_default_4) {
 __y_1  ++ ;

}

if (__static_condition_default_5) {
 __z_2  ++ ;

}

{
if (__static_condition_default_6) {
 __z_2  -- ;

}

if (__static_condition_default_5) {
 __z_2  -- ;

}

}}



}


}

