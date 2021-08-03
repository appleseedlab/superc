#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__v_0", "v");
__static_renaming("__foo_1", "foo");
__static_renaming("__main_2", "main");


};
typedef void  __v_0;// L1

// typedef moved to top of scope
__v_0  __foo_1 (__v_0  );// L3
int  __main_2 () {

{



return 0 ;// L9
}



}
__v_0  __foo_3 (__v_0  ) {

{



return  ;// L14
}



}

