#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_2();

void __static_initializer_2() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");


};
int  __main_0 ();

int  __main_0 () {
{
char  (__x_1[5]);
__static_type_error("type error");

 __x_1  ++ ;

return 0 ;

}


}

