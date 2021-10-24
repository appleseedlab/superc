#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_1", "x");


};
enum __bob_3 {
__A_2,
};

union __forward_tag_reference_0 { // generated union of enum variations
enum __bob_3 __bob_3;
};

union __forward_tag_reference_0 ;// L0
union __forward_tag_reference_0  __x_1;// L3
enum __bob_3 ;// L5

