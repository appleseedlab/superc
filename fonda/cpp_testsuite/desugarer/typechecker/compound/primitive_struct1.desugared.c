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

int  __main_4 () {

{
{

struct __anonymous_tag_0 {
int  __field1_1;
};


int  __x_2;// L3

struct __anonymous_tag_0  __x_3;// L5

if (__static_condition_default_5) {
 __x_2  = 1 ; // L8
}
if (__static_condition_default_6) {
__static_type_error("type error") ; // L8
}
if (__static_condition_default_5) {
 __x_2  ++ ; // L9
}
if (__static_condition_default_6) {
__static_type_error("type error") ; // L9
}
return 0 ;// L11
}
}


}

