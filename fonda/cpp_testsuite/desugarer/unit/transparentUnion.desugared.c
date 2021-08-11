#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__U_4", "U");
__static_renaming("__foo_5", "foo");
__static_renaming("__x_6", "x");
__static_renaming("__main_7", "main");


};
union ____anonymous_tag_0_1 {
int  (* __a_2);
long  __b_3;
};
typedef union ____anonymous_tag_0_1  __U_4;// L1:L4

// typedef moved to top of scope
extern void  __foo_5 (__U_4  );// L6
int  __main_7 () {

{
{



int  __x_6;// L10

 __foo_5  ((union ____anonymous_tag_0_1)&  __x_6 ) ; // L11
return 0 ;// L12
}
}


}

