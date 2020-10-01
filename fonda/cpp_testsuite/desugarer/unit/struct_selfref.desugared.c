#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_2();

void __static_initializer_2() {
__static_renaming("__main_1", "main");


};
struct __list_0 {
int  data;
struct list  (* next);
}
 ;
int  __main_1 ();

struct list { // generated union of struct variations
union {
struct __list_0 __list_0;
};
};

struct list ;
int  __main_1 () {
{
}


}

