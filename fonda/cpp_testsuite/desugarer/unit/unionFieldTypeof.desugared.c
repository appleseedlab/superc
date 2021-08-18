#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_9", "y");
__static_renaming("__main_10", "main");


};

int  __main_10 () {

{
{

typeof(int*)__typeofStandin_2;
typeof(long)__typeofStandin_3;
union ____anonymous_tag_4_5 {
typeof ( __typeofStandin_2 )  __a_6;// L9
typeof ( __typeofStandin_3 )  __a_7;// L9
int  __b_8;// L10
};


int  (* (__x_0));// L4

long  __x_1;// L6

union ____anonymous_tag_4_5  __y_9;// L8:L11

return 0 ;// L12
}
}


}

