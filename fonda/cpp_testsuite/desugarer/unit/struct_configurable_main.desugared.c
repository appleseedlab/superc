#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__main_5", "main");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_7", "(declare-fun |(defined CONFIG_A)| () Bool)(assert (not |(defined CONFIG_A)|))");
__static_condition_renaming("__static_condition_default_8", "(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_A)|)");

};
struct __anonymous_tag_0 {
};
struct __anonymous_tag_1 {
int  __a_2;
int  __x_3;
int  __yy_4;
};

struct __anonymous_tag_0 ;struct __anonymous_tag_1 ;
int  __main_5 () {

if (__static_condition_default_7) {
{
return 0 ;

}

}

}
int  __main_6 () {

if (__static_condition_default_8) {
{
return 0 ;

}

}

}

