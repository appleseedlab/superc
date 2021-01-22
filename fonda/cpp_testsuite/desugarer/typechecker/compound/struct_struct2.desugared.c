#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_5", "x");
__static_renaming("__x_6", "x");

__static_condition_renaming("__static_condition_default_7", "!(defined A)");
__static_condition_renaming("__static_condition_default_8", "(defined A)");

};

int  __main_0 () {
{struct __anonymous_tag_1 {
char  __a_2;
};
struct __anonymous_tag_3 {
int  __field1_4;
};

struct __anonymous_tag_1  __x_5;
struct __anonymous_tag_3  __x_6;

{
if (__static_condition_default_7) {
 __x_6  . __field1_4 ;

}

if (__static_condition_default_8) {
__static_type_error("type error") ;

}

}return 0 ;

}


}

