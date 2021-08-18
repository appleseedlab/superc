#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__c_2", "c");
__static_renaming("__d_3", "d");
__static_renaming("__e_4", "e");
__static_renaming("__f_5", "f");
__static_renaming("__g_6", "g");
__static_renaming("__h_7", "h");
__static_renaming("__i_8", "i");
__static_renaming("__j_9", "j");
__static_renaming("__k_10", "k");
__static_renaming("__l_11", "l");
__static_renaming("__m_12", "m");
__static_renaming("__main_13", "main");


};

int  __a_0;// L1
int  (* (__b_1));// L2
int  (* ((* (__c_2))));// L3
int  (* ((* ((* ((* ((* (__d_3))))))))));// L4
int  (__e_4[]);// L5
int  (__f_5[1]);// L6
int  (__g_6[111]);// L7
int  (__h_7[1][3]);// L8
int  (* ((* ((__i_8[])))));// L9
int  ((* (__j_9))[3]);// L10
int  (__k_10[0]);// L11
int  (__l_11[]);// L12
int  (__m_12[]);// L13
int  __main_13 () {

{
{



return 0 ;// L15
}
}


}

