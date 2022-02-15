#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__y_0", "y");
__static_renaming("__y_1", "y");
__static_renaming("__x_3", "x");


};
const int  __y_1= 7;// L4
enum __bob_6 {
__A_4 =  __y_0  + 2,
__A_5 =  __y_1  + 2,
};

union __forward_tag_reference_2 { // generated union of enum variations
enum __bob_6 __bob_6;
};

int  __y_0= 7;// L2

union __forward_tag_reference_2 ;// L0
union __forward_tag_reference_2  __x_3;// L8
enum __bob_6 ;// L11

