#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_10", "x");
__static_renaming("__y_11", "y");


};
enum ____anonymous_tag_2_3 {
__A_0,
__B_1,
};
enum __bob_6 {
__C_4,
__D_5,
};
enum __joe_9 {
__E_7 = 1,
__F_8,
};

enum ____anonymous_tag_2_3 ;// L1
enum __bob_6 ;// L2
enum __joe_9 ;// L3
enum __bob_6  __x_10;// L5
int  __y_11=  __F_8 ;// L6

