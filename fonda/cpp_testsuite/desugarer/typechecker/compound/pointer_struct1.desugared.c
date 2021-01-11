#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_5();

void __static_initializer_5() {
__static_renaming("__num_0", "num");
__static_renaming("__main_1", "main");
__static_renaming("__x_4", "x");


};
int  __main_1 ();

int  __num_0= 5;
int  __main_1 () {
{struct __anonymous_tag_2 {
int  __field1_3;
};

struct __anonymous_tag_2  __x_4;
__static_type_error("type error");

*  __x_4  ;

return 0 ;

}


}

