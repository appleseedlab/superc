#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

};
struct __bob_6 {
int  __x_7;// L17
};

static int  __x_0;// L3
static char  __x_1;// L5
int  (__main_3) () {

{
{



int  __y_2;// L9

if (__static_condition_default_4) {
 __x_0  ++ ; // L10
}
if (__static_condition_default_5) {
 __x_1  ++ ; // L10
}
 __y_2  ++ ; // L11
__static_type_error("type error : no valid expression"); // L12
}
}


}
struct __bob_6 ;// L17

