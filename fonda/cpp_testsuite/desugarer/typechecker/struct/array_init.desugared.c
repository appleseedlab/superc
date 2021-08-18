#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__main_1", "main");

__static_condition_renaming("__static_condition_default_2", "!(defined A)");

if (__static_condition_default_2)
{
__static_parse_error("Unable to parse");
}
};

int  __main_1 () {

{
{



int  (__a_0[3]);// L3:L8
{
__a_0[0] = 1;
__a_0[1] = 2;
__a_0[2] = 3;
}


}
}


}

