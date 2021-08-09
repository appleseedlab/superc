#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__Y_2", "Y");
__static_renaming("__testStruct_5", "testStruct");
__static_renaming("__x_6", "x");
__static_renaming("__main_7", "main");


};
struct __anonymous_tag_0 {
unsigned long int  (__a_1[( 1024 / ( 8 * sizeof(unsigned long int  ) ) )]);
};
typedef struct __anonymous_tag_0  __Y_2;// L2:L4
struct __X_3 {
__Y_2  __b_4;
};
typedef struct __X_3  (__testStruct_5[1]);// L10

// typedef moved to top of scope
struct __X_3 ;// L6
// typedef moved to top of scope
__testStruct_5  __x_6;// L12
void  __main_7 () {

{
{



}
}


}

