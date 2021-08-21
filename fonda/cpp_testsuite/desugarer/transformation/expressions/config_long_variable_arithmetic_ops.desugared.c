#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_14;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_24;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_22;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__y_3", "y");
__static_renaming("__z_4", "z");
__static_renaming("__w_5", "w");
__static_renaming("__u_6", "u");
__static_renaming("__v_7", "v");
__static_renaming("__t_8", "t");
__static_renaming("__t_9", "t");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_11", "A");
__static_condition_renaming("__static_condition_default_12", "!A");
__static_condition_renaming("__static_condition_default_13", "B");
__static_condition_renaming("__static_condition_default_14", "!B");
__static_condition_renaming("__static_condition_default_15", "C");
__static_condition_renaming("__static_condition_default_16", "!C");
__static_condition_renaming("__static_condition_default_17", "A && B && C");
__static_condition_renaming("__static_condition_default_18", "A && B && !C");
__static_condition_renaming("__static_condition_default_19", "A && !B && C");
__static_condition_renaming("__static_condition_default_20", "A && !B && !C");
__static_condition_renaming("__static_condition_default_21", "!A && B && C");
__static_condition_renaming("__static_condition_default_22", "!A && B && !C");
__static_condition_renaming("__static_condition_default_23", "!A && !B && C");
__static_condition_renaming("__static_condition_default_24", "!A && !B && !C");

};

int  (__main_10) (void  ) {

{
{



int  __x_0;// L3

char  __x_1;// L5

unsigned int  __y_2;// L9

unsigned char  __y_3;// L11

int  __z_4;// L14

int  __w_5;// L15

int  __u_6;// L16

int  __v_7;// L17

long  __t_8;// L20

short  __t_9;// L22

if (__static_condition_default_11) {
 __x_0  = 2 ; // L25
}
if (__static_condition_default_12) {
 __x_1  = 2 ; // L25
}
if (__static_condition_default_13) {
 __y_2  = 3 ; // L26
}
if (__static_condition_default_14) {
 __y_3  = 3 ; // L26
}
 __z_4  = 5 ; // L27
 __w_5  = 1 ; // L28
 __u_6  = 7 ; // L29
 __v_7  = 6 ; // L30
if (__static_condition_default_15) {
 __t_8  = 8 ; // L31
}
if (__static_condition_default_16) {
 __t_9  = 8 ; // L31
}
if (__static_condition_default_17) {
 __x_0  =  __y_2  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_8  ; // L33
}
if (__static_condition_default_18) {
 __x_0  =  __y_2  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_9  ; // L33
}
if (__static_condition_default_19) {
 __x_0  =  __y_3  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_8  ; // L33
}
if (__static_condition_default_20) {
 __x_0  =  __y_3  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_9  ; // L33
}
if (__static_condition_default_21) {
 __x_1  =  __y_2  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_8  ; // L33
}
if (__static_condition_default_22) {
 __x_1  =  __y_2  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_9  ; // L33
}
if (__static_condition_default_23) {
 __x_1  =  __y_3  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_8  ; // L33
}
if (__static_condition_default_24) {
 __x_1  =  __y_3  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_9  ; // L33
}
return 0 ;// L35
}
}


}

