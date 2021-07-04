#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__x_5", "x");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_6", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_7", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_8", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_9", "!(defined A) && !(defined B)");

};
struct __x_0 {
int  __a_1;
unsigned  __a_2;
int  __b_3;
unsigned  __b_4;
};

struct __x_0 ;
int  __main_10 () {

{



struct __x_0  __x_5;
{
if (__static_condition_default_6) {
__x_5.__a_1 = 1;
__x_5.__b_3 = 2;
}
if (__static_condition_default_7) {
__x_5.__a_1 = 1;
__x_5.__b_4 = 2;
}
if (__static_condition_default_8) {
__x_5.__a_2 = 1;
__x_5.__b_3 = 2;
}
if (__static_condition_default_9) {
__x_5.__a_2 = 1;
__x_5.__b_4 = 2;
}
}

return 0 ;
}



}

