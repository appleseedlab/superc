#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {


};
struct __contents_0 {
};
struct __list_2 {
struct __contents_0  __data_3;// L2
struct __forward_tag_reference_1  (* (__next_4));// L0
};

struct __forward_tag_reference_1 { // generated union of struct variations
union {
struct __list_2 __list_2;
};
};

struct __list_2 ;// L1

