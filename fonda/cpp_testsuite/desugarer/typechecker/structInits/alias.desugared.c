#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__X_3", "X");
__static_renaming("__a_4", "a");
__static_renaming("__main_5", "main");


};
struct __x_0 {
int  __a_1;
int  __b_2;
};
typedef struct __x_0  __X_3;

// typedef moved to top of scope
int  __main_5 () {

{



__X_3  __a_4;
{
if (1) {
__a_4.__a_1 = 1;
__a_4.__b_2 = 2;
}
}

return 0 ;// L10
}



}

