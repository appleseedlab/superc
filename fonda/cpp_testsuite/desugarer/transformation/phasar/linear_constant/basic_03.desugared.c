#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("___CfIf3K_CONFIG_A_0", "_CfIf3K_CONFIG_A");
__static_renaming("___Djkifd_CONFIG_A_defined_1", "_Djkifd_CONFIG_A_defined");
__static_renaming("__x_2", "x");
__static_renaming("__y_3", "y");
__static_renaming("__main_4", "main");


};

extern int  ___CfIf3K_CONFIG_A_0;// L2
extern int  ___Djkifd_CONFIG_A_defined_1;// L4
int  (__main_4) () {

{
{



int  __x_2;// L8

int  __y_3= 210;// L9

if (  ___Djkifd_CONFIG_A_defined_1  )// L10
{

{
{



 __x_2  = 42 ; // L11
}
}
}
else
{

{
{



 __x_2  = 13 ; // L13
}
}
}
return  __x_2  ;// L15
}
}


}

