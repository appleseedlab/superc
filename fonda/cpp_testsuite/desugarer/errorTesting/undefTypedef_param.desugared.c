#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__foo_2", "foo");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_3", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A) && !(defined X)");
__static_condition_renaming("__static_condition_default_6", "!(defined A) || (defined A) && (defined X)");

if (__static_condition_default_6)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __x_0;// L2

// typedef moved to top of scope
void  (__foo_2) (__x_0  __a_1) {

if (__static_condition_default_3) {

{
{



return  ;// L12
}
}


}
}
int  (__main_4) () {

if (__static_condition_default_5) {

{
{



 __foo_2  (1) ; // L21
return 0 ;// L22
}
}


}
}

