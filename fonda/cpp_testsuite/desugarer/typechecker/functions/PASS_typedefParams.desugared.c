#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__foo_4", "foo");
__static_renaming("__foo_5", "foo");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_6", "(defined A)");
__static_condition_renaming("__static_condition_default_7", "!(defined A)");

};
typedef int  __x_0;
typedef float  __x_1;

// typedef moved to top of scope
// typedef moved to top of scope
int  __foo_4 (__x_0  __a_2) {

if (__static_condition_default_6) {

{



return 0 ;
}


}

}
int  __foo_5 (__x_1  __a_3) {

if (__static_condition_default_7) {

{



return 0 ;
}


}

}
int  __main_8 () {

{



return 0 ;
}



}

