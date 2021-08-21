#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__foo_4", "foo");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_5", "(defined A)");
__static_condition_renaming("__static_condition_default_7", "(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

if (__static_condition_default_8)
{
__static_parse_error("Unable to parse");
}
};

int  (__foo_4) (int  __a_0, float  __b1_2, char  __x_3) {

if (__static_condition_default_5) {

{
{



return 0 ;// L10
}
}


}
}
int  (__main_6) () {

if (__static_condition_default_7) {

{
{



return  __foo_4  (1,2,3) ;// L14
}
}


}
}

