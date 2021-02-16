#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_5", "main");
__static_renaming("__myFirstStruct_6", "myFirstStruct");


};
struct __x_0 {
int  __a_1;
int  __b_2;
int  __c_3;
int  __c_4;
};

struct __x_0 ;
int  __main_5 (void  ) {
{
struct __x_0  __myFirstStruct_6= { 1, 2 };
return 0 ;

}


}

