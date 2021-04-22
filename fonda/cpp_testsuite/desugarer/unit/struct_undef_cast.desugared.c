#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_1", "x");
__static_renaming("__main_8", "main");


if (0)
{
__static_parse_error("Unable to parse");
}
};
struct __s2_2 {
int  __data_3;
struct __forward_tag_reference_0  (* __next_4);
};
struct __s1_5 {
int  __data_6;
struct __forward_tag_reference_0  (* __next_7);
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __s1_5 __s1_5;
};
};

struct __forward_tag_reference_0  __x_1;
struct __s2_2 ;
struct __s1_5 ;
int  __main_8 () {
{
}


}

