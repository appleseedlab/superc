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
__static_renaming("__d_3", "d");
__static_renaming("__e_4", "e");
__static_renaming("__main_5", "main");


};

int  (__main_5) (void  ) {

{
{



long  __a_0;// L2

long long  __b_1;// L3

long int  __c_2;// L4

long long int  __d_3;// L5

long double  __e_4;// L6

return 0 ;// L8
}
}


}

