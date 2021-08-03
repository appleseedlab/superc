#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__num_0", "num");
__static_renaming("__x_3", "x");
__static_renaming("__x_4", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_6", "!(defined A)");
__static_condition_renaming("__static_condition_default_7", "(defined A)");

};

int  __num_0= 5;// L1
int  __main_5 () {

{

struct __anonymous_tag_1 {
int  __field1_2;
};


int  (* __x_3);// L5

struct __anonymous_tag_1  __x_4;// L7

if (__static_condition_default_6) {
 __x_4  . __field1_2 ; // L10
}
if (__static_condition_default_7) {
__static_type_error("type error") ; // L10
}
return 0 ;// L12
}



}

