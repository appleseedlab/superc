#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_1", "a");
__static_renaming("__x_2", "x");
__static_renaming("__main_3", "main");


};
typedef int  __a_0;

// typedef moved to top of scope
int  __main_3 () {
{typedef __a_0  __a_1;

// typedef moved to top of scope
__a_1  __x_2;
 __x_2  ++ ;

return 0 ;

}


}

