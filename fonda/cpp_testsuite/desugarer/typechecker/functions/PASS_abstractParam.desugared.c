#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__foo_0", "foo");
__static_renaming("__x_1", "x");
__static_renaming("__main_2", "main");


};

int  __foo_0 (int  *);
int  __main_2 () {
{
int  __x_1= 1;
return 0 ;

}


}
int  __foo_4 (int  (* __x_3)) {
{
return 1 ;

}


}

