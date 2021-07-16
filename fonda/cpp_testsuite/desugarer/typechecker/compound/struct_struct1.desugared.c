#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__x_4", "x");
__static_renaming("__x_5", "x");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_7", "(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

};

int  __main_6 () {

{

struct __anonymous_tag_0 {
char  __a_1;
};
struct __anonymous_tag_2 {
int  __field1_3;
};


struct __anonymous_tag_0  __x_4;

struct __anonymous_tag_2  __x_5;

if (__static_condition_default_7) {
 __x_4  . __a_1 ; // L8
}
if (__static_condition_default_8) {
__static_type_error("type error") ; // L8
}
return 0 ;// L10
}



}

