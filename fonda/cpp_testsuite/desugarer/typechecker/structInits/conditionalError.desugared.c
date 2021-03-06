#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__main_6", "main");
__static_renaming("__x_7", "x");

__static_condition_renaming("__static_condition_default_5", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_8", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_9", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_10", "!(defined A) && !(defined B)");

};
struct __x_0 {
int  __a_1;
int  __a_2;
int  __b_3;
int  __b_4;
};

struct __x_0 ;
int  __main_6 () {
{
struct __x_0  __x_7;
{
if (__static_condition_default_8) {
__x_7.__a_1 = 1;
}
if (__static_condition_default_9) {
__x_7.__a_2 = 1;
}
if (__static_condition_default_10) {
__x_7.__b_3 = 1;
}
}
if (__static_condition_default_5) {
__static_type_error("invalid declaration of x under this presence condition");
}
}


}

