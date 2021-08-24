#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__Y_3", "Y");
__static_renaming("__testStruct_6", "testStruct");
__static_renaming("__x_7", "x");
__static_renaming("__main_8", "main");


};
struct ____anonymous_tag_0_1 {
unsigned long int  __a_2[( 1024 / ( 8 * sizeof(unsigned long) ) )];// L3
};
typedef struct ____anonymous_tag_0_1  __Y_3;// L2:L4
struct __X_4 {
__Y_3  __b_5;// L0
};
typedef struct __X_4  __testStruct_6[1];// L10

// typedef moved to top of scope
struct __X_4 ;// L6
// typedef moved to top of scope
__testStruct_6  __x_7;// L12
void  (__main_8) () {

{
{



}
}


}

