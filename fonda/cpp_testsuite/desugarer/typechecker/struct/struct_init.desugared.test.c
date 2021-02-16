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
  int  __a_1; //1
  int  __b_2; //A
  int  __c_3; //!A
  int  __c_4; //A
};

struct __x_0 ;
int  __main_5 (void  ) {
{
  {struct __x_0  __myFirstStruct_6;
  if (PCA)
    {__myFirstStruct_6 . __a_1 = 1; __myFirstStruct_6 . __c_3 = 0;}
  if (!PCA)
    {__myFirstStruct_6 . __a_1 = 1; __myFirstStruct_6 . __b_2 = 0;}}
  if (sizeof(struct __x_0) > 10)
    ...
return 0 ;

}


}

