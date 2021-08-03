#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_3", "x");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

};
struct __x_0 {
int  __a_1;
unsigned  __a_2;
};

struct __x_0 ;// L1
int  __main_6 () {

{



struct __x_0  __x_3;// L12
{
if (__static_condition_default_4) {
__x_3.__a_1 = 1;
__static_type_error("designator doesn't exist.");
}
if (__static_condition_default_5) {
__x_3.__a_2 = 1;
__static_type_error("designator doesn't exist.");
}
}

return 0 ;// L13
}



}

