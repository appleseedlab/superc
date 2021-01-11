#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__a_1", "a");
__static_renaming("__b_2", "b");
__static_renaming("__g_3", "g");
__static_renaming("__a_4", "a");
__static_renaming("__b_5", "b");
__static_renaming("__c_6", "c");
__static_renaming("__d_7", "d");
__static_renaming("__e_8", "e");
__static_renaming("__f_9", "f");
__static_renaming("__g_10", "g");


};

int  __main_0 (void  ) {
{
char  __a_1= 2;
char  __b_2;
char  __g_3= 4;
char  __a_4= 2;
char  __b_5;
char  __c_6= 6;
char  __d_7;
char  __e_8;
char  __f_9;
char  __g_10= 4;
return 0 ;

}


}

