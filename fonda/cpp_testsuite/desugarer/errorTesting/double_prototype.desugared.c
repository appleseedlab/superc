#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__foo_0", "foo");
__static_renaming("__bar_1", "bar");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_3", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_5", "!(defined A) && !(defined B) || (defined A) && (defined B)");

if (__static_condition_default_5)
{
__static_parse_error("Unable to parse");
}
};

int  __foo_0 () {

if (__static_condition_default_2) {

{



return 1 ;// L8
}


}

}
int  __bar_1 () {

if (__static_condition_default_3) {

{



return 1 ;// L8
}


}

}
int  __main_4 () {

{



return 0 ;// L13
}



}

