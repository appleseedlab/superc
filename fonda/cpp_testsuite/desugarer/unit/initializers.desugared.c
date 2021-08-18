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
__static_renaming("__y1_11", "y1");
__static_renaming("__y2_12", "y2");
__static_renaming("__y2b_13", "y2b");
__static_renaming("__y3_14", "y3");
__static_renaming("__y3b_15", "y3b");
__static_renaming("__y4a_16", "y4a");
__static_renaming("__y4b_17", "y4b");
__static_renaming("__y5_18", "y5");
__static_renaming("__y6_19", "y6");
__static_renaming("__y7_20", "y7");
__static_renaming("__y8_21", "y8");


};

int  __x1_0= 1;// L1
int  (* (__x2_1))= 1;// L2
int  (* (__x2b_2))= 1;// L3
int  (* ((* (__x3_3))))= 1;// L4
int  (* ((* (__x3b_4))))= 1;// L5
int  (__x4a_5[])= 1;// L6
int  (__x4b_6[2])= 1;// L7
int  (__x5_7[3][3])= 1;// L8
int  (* ((__x6_8[4])))= 1;// L9
int  (* ((* ((__x7_9[6])))))= 1;// L10
int  ((* (__x8_10))[7])= 1;// L11
int  __y1_11;// L16
int  (* (__y2_12));// L16
int  (* (__y2b_13));// L16
int  (* ((* (__y3_14))));// L16
int  (* ((* (__y3b_15))));// L16
int  (__y4a_16[]);// L16
int  (__y4b_17[2]);// L16
int  (__y5_18[3][3]);// L16
int  (* ((__y6_19[4])));// L16
int  (* ((* ((__y7_20[6])))));// L16
int  ((* (__y8_21))[7]);// L16

