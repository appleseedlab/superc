#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_11;
extern const bool __static_condition_default_12;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_2", "x");
__static_renaming("__y_3", "y");
__static_renaming("__y_4", "y");
__static_renaming("__x_6", "x");
__static_renaming("__main_9", "main");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_11", "!(defined C)");
__static_condition_renaming("__static_condition_default_12", "(defined C)");

};
typedef int  __y_3;
typedef int  __y_4;

int  __x_0;
int  __x_1;
int  __x_2;
// typedef moved to top of scope
// typedef moved to top of scope
__y_3  __x_5;
__y_3  __x_6;
__y_4  __x_7;
__y_4  __x_8;
int  __main_9 () {

if (__static_condition_default_11) {
{
return - 1 ;

}

}

}
int  __main_10 () {

if (__static_condition_default_12) {
{
return - 1 ;

}

}

}
