#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__bob_2", "bob");
__static_renaming("__r_5", "r");
__static_renaming("__q_6", "q");
__static_renaming("__main_7", "main");
__static_renaming("__r_12", "r");
__static_renaming("__q_13", "q");


};
struct __s_0 {
int  __x_1;
};
struct ____s_0_8 {
int  __x_9;
};
struct ____s_1_10 {
};

struct __s_0  __bob_2;// L1:L3
int  __main_7 () {

{

struct __s_3 {
char  __y_4;
};


struct __s_3  __r_5;// L6:L8

struct __s_3  __q_6;// L10

}



}
struct ____s_0_8 ;// L15
struct ____s_1_10 ;// L19
struct __s_0  __bob_11;// L24
int  __main_14 () {

{



struct __s_0  __r_12;// L27

struct __s_0  __q_13;// L29

}



}

