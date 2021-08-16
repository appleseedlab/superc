#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__a_6", "a");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_7", "(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

};
struct __x_0 {
int  __a_1;// L3
unsigned  __a_2;// L5
};
struct __y_3 {
struct __x_0  __a_4;// L9
int  __b_5;// L10
};

struct __x_0 ;// L1
struct __y_3 ;// L8
int  __main_9 () {

{
{



struct __y_3  __a_6;// L14
{
if (1) {
if (__static_condition_default_7) {
__a_6.__a_4.__a_1 = 2;
}
if (__static_condition_default_8) {
__a_6.__a_4.__a_2 = 2;
}
}
}

return 0 ;// L15
}
}


}

