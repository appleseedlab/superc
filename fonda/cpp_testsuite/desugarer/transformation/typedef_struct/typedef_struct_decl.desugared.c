#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__intAlias_0", "intAlias");
__static_renaming("__main_1", "main");
__static_renaming("__intWrapper_4", "intWrapper");


};
typedef int  __intAlias_0;

// typedef moved to top of scope
int  __main_1 (void  ) {
{struct __anonymous_tag_2 {
__intAlias_0  __x_3;
};

struct __anonymous_tag_2  __intWrapper_4;
 __intWrapper_4  . __x_3 = 2 ;

return 0 ;

}


}

