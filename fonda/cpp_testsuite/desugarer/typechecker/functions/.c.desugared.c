#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_5();

void __static_initializer_5() {
__static_renaming("__foo_0", "foo");
__static_renaming("__main_1", "main");
__static_renaming("__x_2", "x");


};
int  __main_1 ();

int  __foo_0 (int  *);
int  __main_1 () {
{
int  __x_2= 1;
return 0 ;

}


}
int  __foo_0 (int  (* __x_3)) {
{
return 1 ;

}


}

