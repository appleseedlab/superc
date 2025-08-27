#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
void __static_initializer_default() {
__static_renaming("__family_0", "family");
__static_renaming("__parse_url_2", "parse_url");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_1", "!APR_HAVE_IPV6");

};

int  (__parse_url_2) () {

{// L6
{



int  __family_0= 6;// L7

if (__static_condition_default_1) {
__static_type_error("invalid declaration of family under this presence condition");
}

}
}// L8


}
int  (__main_3) (void  ) {

{// L11
{



 __parse_url_2 ( ) ; // L12
return 0 ;// L13
}
}// L14


}

