#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__z_3", "z");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined B)");
__static_condition_renaming("__static_condition_default_6", "(defined C)");
__static_condition_renaming("__static_condition_default_7", "!(defined C)");

};

int  __main_0 () {
{
int  __x_1;
int  __y_2;
int  __z_3;
if (  __x_1  ) {
 __x_1  -- ;


if (__static_condition_default_4) {
 __x_1  ++ ;

}

if (__static_condition_default_5) {
 __y_2  ++ ;

}

if (__static_condition_default_6) {
 __z_3  ++ ;

}

{
if (__static_condition_default_7) {
 __z_3  -- ;

}

if (__static_condition_default_6) {
 __z_3  -- ;

}

}}



}


}

