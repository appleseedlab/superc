#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {


};
struct ____anonymous_tag_0_1 {
char  __p_2;
};
struct __list_4 {
struct ____anonymous_tag_0_1  __data_5;
struct __forward_tag_reference_3  (* __next_6);
};

struct __forward_tag_reference_3 { // generated union of struct variations
union {
struct __list_4 __list_4;
};
};

struct __list_4 ;// L1

