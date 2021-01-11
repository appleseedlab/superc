#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_4();

void __static_initializer_4() {
__static_renaming("__main_0", "main");
__static_renaming("__x_3", "x");


};
int  __main_0 ();

int  __main_0 () {
{struct __anonymous_tag_1 {
int  __field1_2;
};

struct __anonymous_tag_1  __x_3;
__static_type_error("type error");

return 0 ;

}


}

