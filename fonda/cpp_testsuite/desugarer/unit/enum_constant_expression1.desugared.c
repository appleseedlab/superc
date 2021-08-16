#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__y_0", "y");
__static_renaming("__x_2", "x");


};
enum __bob_4 {
__A_3 =  __y_0 ,
};

union __forward_tag_reference_1 { // generated union of enum variations
enum __bob_4 __bob_4;
};

extern int  __y_0;// L1
union __forward_tag_reference_1 ;// L0
union __forward_tag_reference_1  __x_2;// L5
enum __bob_4 ;// L8

