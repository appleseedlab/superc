#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__typeAlias_0", "typeAlias");
__static_renaming("__typeAlias_1", "typeAlias");
__static_renaming("__intOrCharWrapper_6", "intOrCharWrapper");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_8", "(defined A)");
__static_condition_renaming("__static_condition_default_9", "!(defined A)");

};
typedef int  __typeAlias_0;// L1:L7
typedef char  __typeAlias_1;// L1:L7

// typedef moved to top of scope
// typedef moved to top of scope
int  __main_7 (void  ) {

{
{

struct ____anonymous_tag_2_3 {
__typeAlias_0  __x_4;// L0
__typeAlias_1  __x_5;// L0
};


struct ____anonymous_tag_2_3  __intOrCharWrapper_6;// L10

if (__static_condition_default_8) {
 __intOrCharWrapper_6  . __x_4 = 2 ; // L12
}
if (__static_condition_default_9) {
 __intOrCharWrapper_6  . __x_5 = 2 ; // L12
}
return 0 ;// L14
}
}


}

