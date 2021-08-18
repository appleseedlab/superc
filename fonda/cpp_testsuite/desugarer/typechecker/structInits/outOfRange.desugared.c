#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__x_5", "x");
__static_renaming("__x_7", "x");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_6", "!(defined A)");
__static_condition_renaming("__static_condition_default_8", "(defined A)");

};
struct __x_0 {
int  __a_1;// L3
};
struct __x_2 {
int  __a_3;// L3
int  __b_4;// L5
};

struct __x_0 ;// L1
struct __x_2 ;// L1
int  __main_9 () {

{
{



struct __x_0  __x_5;// L11
{
if (__static_condition_default_6) {
__x_5.__a_1 = 1;
__static_type_error("assigning value out of struct range.");
}
}

struct __x_2  __x_7;// L11
{
if (__static_condition_default_8) {
__x_7.__a_3 = 1;
__x_7.__b_4 = 2;
}
}

return 0 ;// L12
}
}


}

