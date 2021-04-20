#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__c_1", "c");
__static_renaming("__d_2", "d");
__static_renaming("__e_3", "e");
__static_renaming("__f_4", "f");
__static_renaming("__main_5", "main");


};

int  __main_5 (void  ) {
{
_Complex  __a_0;
if (1) {
__static_type_error("invalid declaration of b under this presence condition");
}
_Complex double  __c_1;
_Complex float  __d_2;
_Complex double  __e_3;
_Complex long double  __f_4;
return 0 ;

}


}

