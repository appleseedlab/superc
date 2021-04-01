#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__a_1", "a");
__static_renaming("__c_2", "c");
__static_renaming("__d_3", "d");
__static_renaming("__e_4", "e");
__static_renaming("__f_5", "f");


};

int  __main_0 (void  ) {
{
_Complex  __a_1;
if (1) {
__static_type_error("invalid declaration of b under this presence condition");
}
_Complex double  __c_2;
_Complex float  __d_3;
_Complex double  __e_4;
_Complex long double  __f_5;
return 0 ;

}


}

