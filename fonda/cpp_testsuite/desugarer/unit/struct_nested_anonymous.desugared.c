#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {


};
struct __anonymous_tag_0 {
char  __p_1;
};
struct __list_3 {
struct __anonymous_tag_0  __data_4;
struct __forward_tag_reference_2  (* __next_5);
};

struct __forward_tag_reference_2 { // generated union of struct variations
union {
struct __list_3 __list_3;
};
};

struct __list_3 ;// L1

