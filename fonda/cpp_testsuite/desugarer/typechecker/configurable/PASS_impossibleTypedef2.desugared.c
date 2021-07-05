#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__first_1", "first");
__static_renaming("__main_2", "main");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");

if (__static_condition_default_6)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __a_0;

// typedef moved to top of scope
int  __main_2 () {

if (__static_condition_default_4) {

{



int  __first_1;

return 0 ;
}


}

}
int  __main_3 () {

if (__static_condition_default_5) {

{



int  __first_1;

return 0 ;
}


}

}

