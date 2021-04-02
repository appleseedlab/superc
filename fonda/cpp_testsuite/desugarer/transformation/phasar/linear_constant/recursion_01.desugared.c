#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("___CfIf3K_CONFIG_A_0", "_CfIf3K_CONFIG_A");
__static_renaming("___Djkifd_CONFIG_A_defined_1", "_Djkifd_CONFIG_A_defined");
__static_renaming("__factorial_3", "factorial");
__static_renaming("__main_4", "main");
__static_renaming("__x_5", "x");


};

extern int  ___CfIf3K_CONFIG_A_0;
extern int  ___Djkifd_CONFIG_A_defined_1;
unsigned  __factorial_3 (unsigned  __n_2) {
{
if (  ___Djkifd_CONFIG_A_defined_1  ) {
if (  __n_2  <= 1 ) {
return 1 ;

}



return  __n_2  *  __factorial_3  (  __n_2  - 1 ) ;

}

 {
return  __n_2  ;

}



}


}
int  __main_4 () {
{
int  __x_5= 5;
 __x_5  =  __factorial_3  (  __x_5  ) ;

return  __x_5  ;

}


}

