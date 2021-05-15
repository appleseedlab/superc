#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__returnOne_2", "returnOne");
__static_renaming("__returnOne_3", "returnOne");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_4", "A");
__static_condition_renaming("__static_condition_default_5", "!A");

};

int  __returnOne_2 (int  __x_0) {

if (__static_condition_default_4) {

{



return 1 ;
}


}

}
int  __returnOne_3 (char  __x_1) {

if (__static_condition_default_5) {

{



return 1 ;
}


}

}
int  __main_6 (void  ) {

{



return 0 ;
}



}

