#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__x_3", "x");
__static_renaming("__x_4", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_6", "!(defined A)");
__static_condition_renaming("__static_condition_default_7", "(defined A)");

};

int  __main_5 () {

{
{

struct ____anonymous_tag_0_1 {
int  __field1_2;// L5
};


int  (__x_3[4]);// L3

struct ____anonymous_tag_0_1  __x_4;// L5

if (__static_condition_default_6) {
 __x_4  . __field1_2 ; // L8
}
if (__static_condition_default_7) {
__static_type_error("type error") ; // L8
}
return 0 ;// L10
}
}


}

