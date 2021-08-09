#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_3", "x");
__static_renaming("__nonenumerator_4", "nonenumerator");
__static_renaming("__main_5", "main");


};
enum E {
__A_0,
__B_1,
__C_2,
};

enum E  __x_3;// L1
int  __nonenumerator_4= 10;// L2
int  __main_5 () {

{
{



 __x_3  =  __nonenumerator_4  ; // L5
}
}


}

