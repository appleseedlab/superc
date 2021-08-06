#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__main_2", "main");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A)");

};

static int  __x_0;// L4
int  __main_2 () {

if (__static_condition_default_4) {

{



char  __x_1;// L9

 __x_1  ++ ; // L12
return  __x_1  ;// L14
}


}

}
int  __main_3 () {

if (__static_condition_default_5) {

{



 __x_0  ++ ; // L12
return  __x_0  ;// L14
}


}

}

