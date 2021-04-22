#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_2", "a");
__static_renaming("__main_3", "main");


if (0)
{
__static_parse_error("Unable to parse");
}
};
struct __x_0 {
int  (__a_1[5]);
};

struct __x_0 ;
int  __main_3 () {
{
struct __x_0  __a_2;
{
if (1) {
__a_2.__a_1[0] = 1;
__a_2.__a_1[2] = 2;
__a_2.__a_1[3] = 3;
}
}
}


}

