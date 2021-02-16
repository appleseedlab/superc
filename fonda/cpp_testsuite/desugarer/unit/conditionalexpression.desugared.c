#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__a_1", "a");
__static_renaming("__b_2", "b");
__static_renaming("__c_3", "c");
__static_renaming("__result_4", "result");


};

int  __main_0 () {
{
int  __a_1;
int  __b_2;
int  __c_3;
int  __result_4;
 __result_4  =  __a_1  ?  __b_2  :  __c_3  ;

}


}

