#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_3();

void __static_initializer_3() {
__static_renaming("__y_0", "y");
__static_renaming("__x_1", "x");


};

enum bob {
__A_2 /* =  __y_0  + 2 */,
};
int  __y_0= 7;
enum   bob ;
enum   bob  __x_1;
enum   bob ;
