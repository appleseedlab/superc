#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_1", "x");
__static_renaming("__main_2", "main");


};
struct __x_0 {
};

struct __x_0  __x_1;// L1:L2
int  (__main_2) () {

{
{



}
}


}

