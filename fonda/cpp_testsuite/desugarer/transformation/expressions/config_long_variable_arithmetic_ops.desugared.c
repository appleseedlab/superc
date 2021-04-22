#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_22;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_15;
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
__static_renaming("__main_24", "main");

__static_condition_renaming("__static_condition_default_10", "A");
__static_condition_renaming("__static_condition_default_11", "!A");
__static_condition_renaming("__static_condition_default_12", "B");
__static_condition_renaming("__static_condition_default_13", "!B");
__static_condition_renaming("__static_condition_default_14", "C");
__static_condition_renaming("__static_condition_default_15", "!C");
__static_condition_renaming("__static_condition_default_16", "A && B && C");
__static_condition_renaming("__static_condition_default_17", "A && B && !C");
__static_condition_renaming("__static_condition_default_18", "A && !B && C");
__static_condition_renaming("__static_condition_default_19", "A && !B && !C");
__static_condition_renaming("__static_condition_default_20", "!A && B && C");
__static_condition_renaming("__static_condition_default_21", "!A && B && !C");
__static_condition_renaming("__static_condition_default_22", "!A && !B && C");
__static_condition_renaming("__static_condition_default_23", "!A && !B && !C");

if (0)
{
__static_parse_error("Unable to parse");
}
};

int  __main_24 (void  ) {
{
int  __x_0;
char  __x_1;
unsigned int  __y_2;
unsigned char  __y_3;
int  __z_4;
int  __w_5;
int  __u_6;
int  __v_7;
long  __t_8;
short  __t_9;

{
if (__static_condition_default_10) {
 __x_0  = 2 ;

}

if (__static_condition_default_11) {
 __x_1  = 2 ;

}

}
{
if (__static_condition_default_12) {
 __y_2  = 3 ;

}

if (__static_condition_default_13) {
 __y_3  = 3 ;

}

} __z_4  = 5 ;

 __w_5  = 1 ;

 __u_6  = 7 ;

 __v_7  = 6 ;


{
if (__static_condition_default_14) {
 __t_8  = 8 ;

}

if (__static_condition_default_15) {
 __t_9  = 8 ;

}

}
{
if (__static_condition_default_16) {
 __x_0  =  __y_2  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_8  ;

}

if (__static_condition_default_17) {
 __x_0  =  __y_2  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_9  ;

}

if (__static_condition_default_18) {
 __x_0  =  __y_3  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_8  ;

}

if (__static_condition_default_19) {
 __x_0  =  __y_3  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_9  ;

}

if (__static_condition_default_20) {
 __x_1  =  __y_2  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_8  ;

}

if (__static_condition_default_21) {
 __x_1  =  __y_2  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_9  ;

}

if (__static_condition_default_22) {
 __x_1  =  __y_3  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_8  ;

}

if (__static_condition_default_23) {
 __x_1  =  __y_3  +  __z_4  -  __w_5  *  __u_6  /  __v_7  %  __t_9  ;

}

}return 0 ;

}


}

