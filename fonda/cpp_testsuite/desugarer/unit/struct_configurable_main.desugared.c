#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__main_7", "main");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_9", "!(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_10", "(defined CONFIG_A)");

};
struct __anonymous_tag_0 {
int  __a_1;
int  __x_2;
};
struct __anonymous_tag_3 {
int  __a_4;
int  __x_5;
int  __yy_6;
};

struct __anonymous_tag_0 ;
struct __anonymous_tag_3 ;
int  __main_7 () {

if (__static_condition_default_9) {

{



return 0 ;// L14
}


}

}
int  __main_8 () {

if (__static_condition_default_10) {

{



return 0 ;// L14
}


}

}

