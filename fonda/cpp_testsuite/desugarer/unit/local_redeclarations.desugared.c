#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__b_3", "b");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A)");

};

 int  __main_4 () {

{



int  __x_0;

if (__static_condition_default_2) {
__static_type_error("redeclaration of local symbol: x");
}


int  __b_3;

}



}

