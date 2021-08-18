#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__c_2", "c");
__static_renaming("__main_3", "main");


};

void  (* (__a_0));// L1
void  __b_1 () {

{
{



return  ;// L4
}
}


}
inline int  __c_2 () {

{
{



return 0 ;// L9
}
}


}
int  __main_3 () {

{
{



}
}


}

