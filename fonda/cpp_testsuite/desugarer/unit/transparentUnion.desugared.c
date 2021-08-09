#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__U_3", "U");
__static_renaming("__foo_4", "foo");
__static_renaming("__x_5", "x");
__static_renaming("__main_6", "main");


};
union __anonymous_tag_0 {
int  (* __a_1);
long  __b_2;
};
typedef union __anonymous_tag_0  __U_3;// L1:L4

// typedef moved to top of scope
extern void  __foo_4 (__U_3  );// L6
int  __main_6 () {

{
{



int  __x_5;// L10

 __foo_4  ((union __anonymous_tag_0)&  __x_5 ) ; // L11
return 0 ;// L12
}
}


}

