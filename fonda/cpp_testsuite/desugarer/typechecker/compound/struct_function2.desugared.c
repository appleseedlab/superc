#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_9;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_4", "x");
__static_renaming("__x_5", "x");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_6", "!(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");
__static_condition_renaming("__static_condition_default_9", "(defined A)");

};
struct ____anonymous_tag_0_1 {
char  __a_2;// L2
};

struct ____anonymous_tag_0_1  __x_4;// L2
char  __x_5 (int  __y_3) {

if (__static_condition_default_6) {

{
{



return  __y_3  ;// L5
}
}


}
}
int  __main_7 () {

{
{



if (__static_condition_default_8) {
 __x_5  (2) ; // L10
}
if (__static_condition_default_9) {
__static_type_error("type error") ; // L10
}
return 0 ;// L11
}
}


}

