#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__v_0", "v");
__static_renaming("__foo_1", "foo");
__static_renaming("__x_2", "x");
__static_renaming("__main_3", "main");


};
typedef void  __v_0;// L1

// typedef moved to top of scope
__v_0  __foo_1 (__v_0  );// L3
__v_0  (* (__x_2));// L5
int  __main_3 () {

{
{



return 0 ;// L9
}
}


}
__v_0  __foo_4 (__v_0  ) {

{
{



return  ;// L14
}
}


}

