#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__b_2", "b");
__static_renaming("__main_3", "main");


};
struct __x_0 {
int  __a_1;
};

 struct __x_0 ;
 int  __main_3 () {

{



struct __x_0  (__b_2[5]);
{
if (1) {
__b_2[0].__a_1 = 2;
}
if (1) {
__b_2[1].__a_1 = 2;
}
if (1) {
__b_2[4].__a_1 = 1;
}
if (1) {
__b_2[5].__a_1 = 5;
}
}

}



}

