#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__adder_2", "adder");
__static_renaming("__argOne_3", "argOne");
__static_renaming("__argTwo_4", "argTwo");
__static_renaming("__result_5", "result");
__static_renaming("__main_6", "main");


};

int  __adder_2 (int  __a_0, int  __b_1) {

{



return  __a_0  +  __b_1  ;// L2
}



}
int  __main_6 (void  ) {

{



int  __argOne_3= 2;// L6

int  __argTwo_4= 5;// L7

int  __result_5;// L8

 __result_5  =  __adder_2  (  __argOne_3 ,  __argTwo_4  ) ; // L10
return 0 ;// L12
}



}

