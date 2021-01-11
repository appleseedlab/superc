#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("___CfIf3K_CONFIG_A_0", "_CfIf3K_CONFIG_A");
__static_renaming("___Djkifd_CONFIG_A_defined_1", "_Djkifd_CONFIG_A_defined");
__static_renaming("__main_2", "main");
__static_renaming("__x_3", "x");
__static_renaming("__i_4", "i");


};

extern int  ___CfIf3K_CONFIG_A_0;
extern int  ___Djkifd_CONFIG_A_defined_1;
int  __main_2 () {
{
int  __x_3= 0;
if (  ___Djkifd_CONFIG_A_defined_1  ) {
{ int  __i_4= 0;
 for ( ;  __i_4  < 10 ; ++  __i_4  ) {
++  __x_3  ;

} }

}



return  __x_3  ;

}


}

