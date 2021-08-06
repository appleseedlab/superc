#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__var_2", "var");
__static_renaming("__var_3", "var");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_5", "(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");

};
struct __test_0 {
int  __x_1;
};

struct __test_0 ;// L1
int  __main_4 () {

{
{



struct __test_0  __var_2;// L7

int  __var_3;// L9

if (__static_condition_default_5) {
 __var_2  . __x_1 = 1 ; // L13
}
if (__static_condition_default_6) {
__static_type_error("type error") ; // L13
}
}
}



}

