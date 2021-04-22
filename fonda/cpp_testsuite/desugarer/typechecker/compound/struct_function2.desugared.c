#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__x_4", "x");
__static_renaming("__x_5", "x");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");
__static_condition_renaming("__static_condition_default_7", "(defined A)");

if (0)
{
__static_parse_error("Unable to parse");
}
};
struct __anonymous_tag_0 {
char  __a_1;
};

struct __anonymous_tag_0  __x_4;
char  __x_5 (int  __y_2) {

if (__static_condition_default_3) {
{

if (__static_condition_default_3) {
return  __y_2  ;

}
}

}

}
int  __main_8 () {
{

{
if (__static_condition_default_6) {
 __x_5  ( 2 ) ;

}

if (__static_condition_default_7) {
__static_type_error("type error") ;

}

}return 0 ;

}


}

