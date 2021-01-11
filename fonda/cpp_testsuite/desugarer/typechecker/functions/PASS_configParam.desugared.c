#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__foo_3", "foo");
__static_renaming("__foo_4", "foo");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");

};

int  __foo_3 (int  __y_1) {

if (__static_condition_default_5) {
{
return 0 ;

}

}

}
int  __foo_4 (int  __x_0, int  __y_2) {

if (__static_condition_default_6) {
{
return 0 ;

}

}

}
int  __main_7 () {
{
return 1 ;

}


}

