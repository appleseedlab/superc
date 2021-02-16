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


};

int  __main_0 (void  ) {
{
long  __a_1;
long long  __b_2;
long int  __c_3;
long long int  __d_4;
long double  __e_5;
return 0 ;

}


}

