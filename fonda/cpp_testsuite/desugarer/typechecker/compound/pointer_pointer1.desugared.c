#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_2", "x");
__static_renaming("__x_3", "x");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_5", "(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");

};
struct __s_0 {
int  __field1_1;
};

struct __s_0 ;// L1
int  __main_4 () {

{



int  (* __x_2);// L5

struct __s_0  (* __x_3);// L7

if (__static_condition_default_5) {
*  __x_2  ; // L10
}
if (__static_condition_default_6) {
*  __x_3  ; // L10
}
return 0 ;// L12
}



}

