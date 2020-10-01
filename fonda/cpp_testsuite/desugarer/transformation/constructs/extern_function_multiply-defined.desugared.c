#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_2();

void __static_initializer_2() {
__static_renaming("__x_0", "x");
__static_renaming("__main_1", "main");


};
int  __main_1 ();

extern float  __x_0 ();
int  __main_1 () {
{
 __x_0  ( ) ;

}


}

