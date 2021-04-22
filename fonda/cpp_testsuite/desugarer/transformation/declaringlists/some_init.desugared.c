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


if (0)
{
__static_parse_error("Unable to parse");
}
};

int  __main_7 (void  ) {
{
char  __a_0= 2;
char  __b_1;
char  __c_2= 6;
char  __d_3;
char  __e_4;
char  __f_5;
char  __g_6= 4;
return 0 ;

}


}

