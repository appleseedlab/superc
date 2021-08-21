#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__data_3", "data");
__static_renaming("__main_4", "main");


};
struct ____anonymous_tag_0_1 {
char  __p_2;// L2
};

struct ____anonymous_tag_0_1  __data_3;// L1:L3
int  (__main_4) () {

{
{



 __data_3  . __p_2 ; // L7
return 0 ;// L9
}
}


}

