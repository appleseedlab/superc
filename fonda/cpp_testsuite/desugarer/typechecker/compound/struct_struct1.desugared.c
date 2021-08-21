#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__x_6", "x");
__static_renaming("__x_7", "x");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_9", "(defined A)");
__static_condition_renaming("__static_condition_default_10", "!(defined A)");

};

int  (__main_8) () {

{
{

struct ____anonymous_tag_0_1 {
char  __a_2;// L3
};
struct ____anonymous_tag_3_4 {
int  __field1_5;// L5
};


struct ____anonymous_tag_0_1  __x_6;// L3

struct ____anonymous_tag_3_4  __x_7;// L5

if (__static_condition_default_9) {
 __x_6  . __a_2 ; // L8
}
if (__static_condition_default_10) {
__static_type_error("type error") ; // L8
}
return 0 ;// L10
}
}


}

