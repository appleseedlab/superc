#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_4", "x");
__static_renaming("__nonenumerator_5", "nonenumerator");
__static_renaming("__main_6", "main");


};
enum __E_3 {
__A_0,
__B_1,
__C_2,
};

enum __E_3  __x_4;// L1
int  __nonenumerator_5= 10;// L2
int  (__main_6) () {

{
{



 __x_4  =  __nonenumerator_5  ; // L5
}
}


}

