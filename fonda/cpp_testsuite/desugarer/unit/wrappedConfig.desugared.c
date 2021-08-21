#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__y_0", "y");
__static_renaming("__x_1", "x");
__static_renaming("__foo_2", "foo");
__static_renaming("__x_4", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_3", "(defined A)");

};

int  __y_0;// L3
char  (__foo_2) () {

if (__static_condition_default_3) {

{
{



int  __x_1;// L7

}
}


}
}
int  (__main_5) () {

if (__static_condition_default_3) {

{
{



int  __x_4;// L12

return  __foo_2 ( ) ;// L13
}
}


}
}

