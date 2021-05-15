#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("___CfIf3K_CONFIG_A_0", "_CfIf3K_CONFIG_A");
__static_renaming("___Djkifd_CONFIG_A_defined_1", "_Djkifd_CONFIG_A_defined");
__static_renaming("__factorial_3", "factorial");
__static_renaming("__x_4", "x");
__static_renaming("__main_5", "main");


};

extern int  ___CfIf3K_CONFIG_A_0;
extern int  ___Djkifd_CONFIG_A_defined_1;
unsigned  __factorial_3 (unsigned  __n_2) {

{



if (  ___Djkifd_CONFIG_A_defined_1  )

{



if (  __n_2  <= 1 )

{



return 1 ;
}
__static_type_error("invalid type found in return expression");
}
else

{



return  __n_2  ;
}
}



}
int  __main_5 () {

{



int  __x_4= 5;

 __x_4  =  __factorial_3  (  __x_4  ) ;
return  __x_4  ;
}



}

