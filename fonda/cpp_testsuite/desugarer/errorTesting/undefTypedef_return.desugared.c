#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__foo_2", "foo");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_1", "(defined A)");
__static_condition_renaming("__static_condition_default_3", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

if (__static_condition_default_5)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __x_0;

// typedef moved to top of scope
__x_0  __foo_2 () {

if (__static_condition_default_1) {
{

if (__static_condition_default_1) {
return 1 ;

}
}

}

}
int  __main_4 () {
{

{
if (__static_condition_default_1) {
 __foo_2  ( ) ;

}

if (__static_condition_default_3) {
__static_type_error("type error") ;

}

}return 0 ;

}


}

