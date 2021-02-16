#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__adder_2", "adder");
__static_renaming("__main_3", "main");
__static_renaming("__argOne_4", "argOne");
__static_renaming("__argTwo_5", "argTwo");
__static_renaming("__result_6", "result");


};

int  __adder_2 (int  __a_0, int  __b_1) {
{
return  __a_0  +  __b_1  ;

}


}
int  __main_3 (void  ) {
{
int  __argOne_4= 2;
int  __argTwo_5= 5;
int  __result_6;
 __result_6  =  __adder_2  (  __argOne_4 ,  __argTwo_5  ) ;

return 0 ;

}


}

