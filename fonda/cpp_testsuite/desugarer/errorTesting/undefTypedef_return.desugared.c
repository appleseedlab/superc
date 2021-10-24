#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__foo_1", "foo");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A)");
__static_condition_renaming("__static_condition_default_4", "!(defined A)");

if (__static_condition_default_4)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __x_0;// L2

// typedef moved to top of scope
__x_0  (__foo_1) () {

if (__static_condition_default_2) {

{
{



return 1 ;// L6
}
}


}
}
int  (__main_3) () {

{
{



if (__static_condition_default_2) {
 __foo_1 ( ) ; // L13
}
return 0 ;// L14
}
}


}

