#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_3", "x");
__static_renaming("__x_4", "x");

__static_condition_renaming("__static_condition_default_5", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "(defined A)");

};

int  __main_0 () {
{struct __anonymous_tag_1 {
int  __field1_2;
};

int  __x_3;
struct __anonymous_tag_1  __x_4;

{
if (__static_condition_default_5) {
 __x_4  . __field1_2 ;

}

if (__static_condition_default_6) {
__static_type_error("type error")

}

}return 0 ;

}


}

