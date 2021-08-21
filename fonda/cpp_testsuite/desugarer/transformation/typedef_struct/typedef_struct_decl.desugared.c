#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__intAlias_0", "intAlias");
__static_renaming("__intWrapper_4", "intWrapper");
__static_renaming("__main_5", "main");


};
typedef int  __intAlias_0;// L1

// typedef moved to top of scope
int  (__main_5) (void  ) {

{
{

struct ____anonymous_tag_1_2 {
__intAlias_0  __x_3;// L0
};


struct ____anonymous_tag_1_2  __intWrapper_4;// L4

 __intWrapper_4  . __x_3 = 2 ; // L6
return 0 ;// L8
}
}


}

