#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_7", "x");
__static_renaming("__y_8", "y");


};
enum joe {
__E_5 = 1,
__F_6,
};
enum bob {
__C_3,
__D_4,
};
enum __anonymous_tag_2 {
__A_0,
__B_1,
};

 enum __anonymous_tag_2 ;
 enum bob ;
 enum joe ;
 enum bob  __x_7;
 int  __y_8=  __F_6 ;

