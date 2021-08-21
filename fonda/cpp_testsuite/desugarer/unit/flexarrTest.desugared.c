#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__main_4", "main");


};
struct __x_1 {
int  __x_2;// L4
char  __name_3[];// L5
};

int  __a_0;// L2
struct __x_1 ;// L3
int  (__main_4) () {

{
{



 __a_0  = ( sizeof(int  )  +  sizeof(char  [0]) ) ; // L9
return  __a_0  ;// L10
}
}


}

