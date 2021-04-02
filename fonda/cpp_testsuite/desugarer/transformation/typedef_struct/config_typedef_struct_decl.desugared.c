#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__typeAlias_0", "typeAlias");
__static_renaming("__typeAlias_1", "typeAlias");
__static_renaming("__main_2", "main");
__static_renaming("__intOrCharWrapper_6", "intOrCharWrapper");

__static_condition_renaming("__static_condition_default_7", "(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

};
typedef int  __typeAlias_0;
typedef char  __typeAlias_1;

// typedef moved to top of scope
// typedef moved to top of scope
int  __main_2 (void  ) {
{struct __anonymous_tag_3 {
__typeAlias_0  __x_4;
__typeAlias_1  __x_5;
};

struct __anonymous_tag_3  __intOrCharWrapper_6;

{
if (__static_condition_default_7) {
 __intOrCharWrapper_6  . __x_4 = 2 ;

}

if (__static_condition_default_8) {
 __intOrCharWrapper_6  . __x_5 = 2 ;

}

}return 0 ;

}


}

