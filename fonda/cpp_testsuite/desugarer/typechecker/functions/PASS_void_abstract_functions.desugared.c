#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__foo_0", "foo");
__static_renaming("__fwotwo_1", "fwotwo");
__static_renaming("__main_2", "main");


};

void  __foo_0 (void  );// L1
void  __fwotwo_1 (void  *, void  *);// L3
int  __main_2 () {

{
{



return 1 ;// L7
}
}


}

