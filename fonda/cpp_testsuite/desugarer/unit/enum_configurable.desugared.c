#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_4();

void __static_initializer_4() {
__static_renaming("__p_0", "p");
__static_renaming("__x_1", "x");


};

enum __anonymous_tag_3 {
__A_2 /* = 1 */,
};
extern const int  __p_0;
int  __x_1=  __p_0  ? 1 : 0;
enum   __anonymous_tag_3 ;

