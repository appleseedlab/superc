#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__x_6", "x");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_7", "(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

};
struct __x_0 {
int  __a_1;
int  __b_2;
int  __c_3;
int  __d_4;
int  __d_5;
};

struct __x_0 ;// L1
int  __main_9 () {

{
{



struct __x_0  __x_6;// L12
{
if (__static_condition_default_7) {
__x_6.__a_1 = 1;
__x_6.__b_2 = 2;
__x_6.__c_3 = 3;
__x_6.__b_2 = 4;
__x_6.__c_3 = 5;
}
if (__static_condition_default_8) {
__x_6.__a_1 = 1;
__x_6.__b_2 = 2;
__x_6.__d_4 = 3;
__x_6.__b_2 = 4;
__x_6.__d_4 = 5;
}
}

return 0 ;// L13
}
}



}

