#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x1_0", "x1");
__static_renaming("__x2_1", "x2");
__static_renaming("__x2b_2", "x2b");
__static_renaming("__x3_3", "x3");
__static_renaming("__x3b_4", "x3b");
__static_renaming("__x4a_5", "x4a");
__static_renaming("__x4b_6", "x4b");
__static_renaming("__x5_7", "x5");
__static_renaming("__x6_8", "x6");
__static_renaming("__x7_9", "x7");
__static_renaming("__x8_10", "x8");


};

int  __x1_0;// L1
int  * (__x2_1);// L2
int  * (__x2b_2);// L3
int  * (* (__x3_3));// L4
int  * (* (__x3b_4));// L5
int  __x4a_5[];// L6
int  __x4b_6[2];// L7
int  __x5_7[3][3];// L8
int  * (__x6_8[4]);// L9
int  * (* (__x7_9[6]));// L10
int  * (__x8_10)[7];// L11

