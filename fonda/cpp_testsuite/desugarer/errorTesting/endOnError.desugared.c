#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__main_0", "main");

__static_condition_renaming("__static_condition_default_1", "(defined A)");
__static_condition_renaming("__static_condition_default_2", "!(defined A)");

if (__static_condition_default_2)
{
__static_parse_error("Unable to parse");
}
};

int  (__main_0) () {

if (__static_condition_default_1) {

{
{



return 0 ;// L3
}
}


}
}

