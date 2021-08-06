#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__i_0", "i");
__static_renaming("__x_1", "x");
__static_renaming("__z_2", "z");
__static_renaming("__q_3", "q");
__static_renaming("__w_4", "w");
__static_renaming("__j_5", "j");
__static_renaming("__a_6", "a");
__static_renaming("__b_7", "b");
__static_renaming("__c_8", "c");
__static_renaming("__d_9", "d");
__static_renaming("__e_10", "e");
__static_renaming("__f_11", "f");
__static_renaming("__main_12", "main");


};
typedef unsigned int  __i_0;// L1
typedef long long  __x_1;// L2
typedef const __x_1  __z_2;// L3
typedef int  (* __q_3);// L4
typedef __q_3  (__w_4[2]);// L5
volatile typedef __i_0  __j_5;// L6

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
int  __main_12 () {

{
{



__i_0  __a_6;// L9

__x_1  __b_7;// L10

__z_2  __c_8;// L11

__q_3  __d_9;// L12

__w_4  __e_10;// L13

__j_5  __f_11;// L14

return 0 ;// L15
}
}



}

