#include <stdbool.h>

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
__static_renaming("__main_5", "main");


};

int  __main_5 (void  ) {
{
long  __a_0;
long long  __b_1;
long int  __c_2;
long long int  __d_3;
long double  __e_4;
return 0 ;

}


}

