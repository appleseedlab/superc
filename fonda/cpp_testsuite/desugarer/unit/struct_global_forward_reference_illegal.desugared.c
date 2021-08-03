#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {


};
struct __s_1 {
int  __x_2;
struct __forward_tag_reference_0  (* __z_4);
};
struct __t_5 {
int  __p_6;
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __t_5 __t_5;
};
};


struct __t_5 ;// L7

