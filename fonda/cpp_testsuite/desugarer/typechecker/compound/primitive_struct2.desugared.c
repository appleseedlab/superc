#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_2", "x");
__static_renaming("__x_3", "x");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A)");

if (0)
{
__static_parse_error("Unable to parse");
}
};

int  __main_6 () {
{struct __anonymous_tag_0 {
int  __field1_1;
};

int  __x_2;
struct __anonymous_tag_0  __x_3;

{
if (__static_condition_default_4) {
 __x_3  . __field1_1 ;

}

if (__static_condition_default_5) {
__static_type_error("type error") ;

}

}return 0 ;

}


}

