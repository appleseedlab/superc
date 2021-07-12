#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__g_2", "g");
__static_renaming("__a_3", "a");
__static_renaming("__b_4", "b");
__static_renaming("__c_5", "c");
__static_renaming("__d_6", "d");
__static_renaming("__e_7", "e");
__static_renaming("__f_8", "f");
__static_renaming("__g_9", "g");
__static_renaming("__main_10", "main");


};

int  __main_10 (void  ) {

{



char  __a_0= 2;
char  __b_1;
char  __g_2= 4;

char  __a_3= 2;
char  __b_4;
char  __c_5= 6;
char  __d_6;
char  __e_7;
char  __f_8;
char  __g_9= 4;

return 0 ;// L11
}



}

