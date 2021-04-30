#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__main_2", "main");


};

int  __main_2 (void  ) {
{
int  __x_0;
int  __y_1;
 __x_0  = 1 ;

 __y_1  = 2 ;

 __x_0  +=  __y_1  ;

 __x_0  -=  __y_1  ;

 __x_0  *=  __y_1  ;

 __x_0  /=  __y_1  ;

 __x_0  %=  __y_1  ;

return 0 ;

}


}

