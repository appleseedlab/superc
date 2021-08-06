#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_9;
extern const bool __static_condition_default_10;
void __static_initializer_default() {
__static_renaming("__bee_8", "bee");
__static_renaming("__main_11", "main");

__static_condition_renaming("__static_condition_default_9", "(defined A)");
__static_condition_renaming("__static_condition_default_10", "!(defined A)");

};
struct __a_0 {
int  __a_1;
int  __b_2;
int  __c_3;
int  __c_4;
};
struct __b_5 {
int  __a_6;
struct __a_0  __field_7;
};

struct __a_0 ;// L1
struct __b_5 ;// L9
int  __main_11 () {

{
{



struct __b_5  __bee_8;// L16
{
if (1) {
__bee_8.__a_6 = 1;
if (__static_condition_default_9) {
__bee_8.__field_7.__a_1 = 2;
__bee_8.__field_7.__b_2 = 3;
}
if (__static_condition_default_10) {
__bee_8.__field_7.__a_1 = 2;
__bee_8.__field_7.__c_3 = 3;
}
}
}

return 0 ;// L17
}
}



}

