#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_11;
extern const bool __static_condition_default_12;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_9", "y");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_11", "(defined A)");
__static_condition_renaming("__static_condition_default_12", "!(defined A)");

};

int  (__main_10) () {

{
{

typeof(int)__typeofStandin_2;
typeof(long long)__typeofStandin_3;
union ____anonymous_tag_4_5 {
typeof ( __typeofStandin_2 )  __a_6;// L9
typeof ( __typeofStandin_3 )  __a_7;// L9
int  __b_8;// L10
};


int  __x_0;// L4

long long  __x_1;// L6

union ____anonymous_tag_4_5  __y_9;// L8:L11

if (__static_condition_default_11) {
return ( ( ( sizeof(int)  >=  sizeof(int) ) ) ? sizeof(int) : ( sizeof(int) ) ) ;// L12
}
if (__static_condition_default_12) {
return ( ( ( sizeof(long long)  >=  sizeof(int) ) ) ? sizeof(long long) : ( sizeof(int) ) ) ;// L12
}
}
}


}


int main () {
  return __main_10();
}
