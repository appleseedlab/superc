#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__a_3", "a");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "!(defined A)");

};
enum __e_1 {
__eA_0 = 5,
};

enum __e_1 ;// L5

int  (__main_4) () {

{
{



enum __e_1  __a_3;// L10

return 0 ;// L11
}
}


}

