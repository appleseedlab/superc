#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("___CfIf3K_CONFIG_A_0", "_CfIf3K_CONFIG_A");
__static_renaming("___Djkifd_CONFIG_A_defined_1", "_Djkifd_CONFIG_A_defined");
__static_renaming("__increment_3", "increment");
__static_renaming("__main_4", "main");
__static_renaming("__x_5", "x");


};

extern int  ___CfIf3K_CONFIG_A_0;
extern int  ___Djkifd_CONFIG_A_defined_1;
int  __increment_3 (int  __i_2) {
{
return ++  __i_2  ;

}


}
int  __main_4 () {
{
int  __x_5= 99;
if (  ___Djkifd_CONFIG_A_defined_1  ) {
 __x_5  =  __increment_3  (  __x_5  ) ;

}



return  __x_5  ;

}


}
