#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__myFirstArr_0", "myFirstArr");
__static_renaming("__main_1", "main");


};

int  __main_1 (void  ) {

{



int  (__myFirstArr_0[3]);

 __myFirstArr_0  [ 1 ] = 7 ;
return 0 ;
}



}

