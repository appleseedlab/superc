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
__static_renaming("__f_5", "f");
__static_renaming("__g_6", "g");
__static_renaming("__main_7", "main");


};

int  __main_7 (void  ) {

{
{



char  __a_0;// L3

char  __b_1;// L3

char  __c_2;// L3

char  __d_3;// L3

char  __e_4;// L3

char  __f_5;// L3

char  __g_6= 1;// L3

return 0 ;// L5
}
}


}

