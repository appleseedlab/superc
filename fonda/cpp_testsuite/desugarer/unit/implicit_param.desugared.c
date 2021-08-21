#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_1", "a");
__static_renaming("__foo_4", "foo");
__static_renaming("__foo_5", "foo");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_6", "(defined A)");
__static_condition_renaming("__static_condition_default_7", "!(defined A)");

};
typedef signed int  __a_0;// L2
typedef unsigned int  __a_1;// L4

// typedef moved to top of scope
// typedef moved to top of scope
int  (__foo_4) (__a_0  __x_2) {

if (__static_condition_default_6) {

{
{



 __x_2  ++ ; // L9
return 0 ;// L10
}
}


}
}
int  (__foo_5) (__a_1  __x_3) {

if (__static_condition_default_7) {

{
{



 __x_3  ++ ; // L9
return 0 ;// L10
}
}


}
}
int  (__main_8) () {

{
{



if (__static_condition_default_6) {
 __foo_4  (1) ; // L15
}
if (__static_condition_default_7) {
 __foo_5  (1) ; // L15
}
return 0 ;// L16
}
}


}

