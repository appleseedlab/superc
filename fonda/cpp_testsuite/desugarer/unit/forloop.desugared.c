#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__i_1", "i");
__static_renaming("__j_2", "j");


};

int  __main_0 () {
{
int  __i_1;
int  __j_2;
for (  __i_1  = 0 ;  __i_1  < 10 ;  __i_1  ++ ) {
 __j_2  ++ ;

}

}


}

