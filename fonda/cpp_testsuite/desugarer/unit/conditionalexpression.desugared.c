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
__static_renaming("__result_3", "result");
__static_renaming("__main_4", "main");


};

 int  __main_4 () {

{



int  __a_0;
int  __b_1;
int  __c_2;

int  __result_3;

 __result_3  =  __a_0  ?  __b_1  :  __c_2  ;
}



}

