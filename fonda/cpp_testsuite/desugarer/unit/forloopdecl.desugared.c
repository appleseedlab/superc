#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__j_1", "j");
__static_renaming("__i_2", "i");


};

int  __main_0 () {
{
int  __j_1;
{ int  __i_2= 0;
 for ( ;  __i_2  < 10 ;  __i_2  ++ ) {
 __j_1  ++ ;

} }

}


}

