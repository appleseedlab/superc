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
__static_renaming("__g_7", "g");


};

int  __main_0 (void  ) {
{
char  __a_1;
char  __b_2;
char  __c_3;
char  __d_4;
char  __e_5;
char  __f_6;
char  __g_7;
return 0 ;

}


}

