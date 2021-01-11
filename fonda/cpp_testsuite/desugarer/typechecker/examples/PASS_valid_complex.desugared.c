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
__static_renaming("__d_4", "d");
__static_renaming("__e_5", "e");
__static_renaming("__f_6", "f");


};

int  __main_0 (void  ) {
{
_Complex  __a_1;
_Complex int  __b_2;
_Complex double  __c_3;
_Complex float  __d_4;
_Complex double  __e_5;
_Complex long double  __f_6;
return 0 ;

}


}

