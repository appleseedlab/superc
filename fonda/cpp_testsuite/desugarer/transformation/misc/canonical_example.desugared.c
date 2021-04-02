#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_1;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_2", "x");
__static_renaming("__y_4", "y");

__static_condition_renaming("__static_condition_default_1", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_3", "(defined A) && !(defined B)");

};

int  __main_0 () {
{
if (__static_condition_default_1) {
__static_type_error("invalid declaration of x under this presence condition");
}
long int  __x_2;
if (__static_condition_default_3) {
__static_type_error("invalid declaration of y under this presence condition");
}
long int  __y_4;
}


}

