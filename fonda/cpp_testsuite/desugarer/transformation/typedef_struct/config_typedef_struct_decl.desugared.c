#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__typeAlias_0", "typeAlias");
__static_renaming("__typeAlias_1", "typeAlias");
__static_renaming("__intOrCharWrapper_5", "intOrCharWrapper");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_7", "(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

};
typedef int  __typeAlias_0;// L1:L7
typedef char  __typeAlias_1;// L1:L7

// typedef moved to top of scope
// typedef moved to top of scope
int  __main_6 (void  ) {

{
{

struct __anonymous_tag_2 {
__typeAlias_0  __x_3;
__typeAlias_1  __x_4;
};


struct __anonymous_tag_2  __intOrCharWrapper_5;// L10

if (__static_condition_default_7) {
 __intOrCharWrapper_5  . __x_3 = 2 ; // L12
}
if (__static_condition_default_8) {
 __intOrCharWrapper_5  . __x_4 = 2 ; // L12
}
return 0 ;// L14
}
}



}

