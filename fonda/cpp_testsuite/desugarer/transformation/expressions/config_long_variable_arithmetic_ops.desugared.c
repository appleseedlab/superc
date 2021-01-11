#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_11;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_24;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_22;
extern const bool __static_condition_default_19;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__y_3", "y");
__static_renaming("__y_4", "y");
__static_renaming("__z_5", "z");
__static_renaming("__w_6", "w");
__static_renaming("__u_7", "u");
__static_renaming("__v_8", "v");
__static_renaming("__t_9", "t");
__static_renaming("__t_10", "t");

__static_condition_renaming("__static_condition_default_11", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))");
__static_condition_renaming("__static_condition_default_12", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))");
__static_condition_renaming("__static_condition_default_13", "(declare-fun B () Bool)(assert B)");
__static_condition_renaming("__static_condition_default_14", "(declare-fun B () Bool)(assert (not B))");
__static_condition_renaming("__static_condition_default_15", "(declare-fun C () Bool)(assert C)");
__static_condition_renaming("__static_condition_default_16", "(declare-fun C () Bool)(assert (not C))");
__static_condition_renaming("__static_condition_default_17", "(declare-fun B () Bool)(declare-fun A () Bool)(declare-fun C () Bool)(assert (or (and A B) (and A (not B))))(assert B)(assert C)");
__static_condition_renaming("__static_condition_default_18", "(declare-fun B () Bool)(declare-fun A () Bool)(declare-fun C () Bool)(assert (or (and A B) (and A (not B))))(assert B)(assert (not C))");
__static_condition_renaming("__static_condition_default_19", "(declare-fun B () Bool)(declare-fun A () Bool)(declare-fun C () Bool)(assert (or (and A B) (and A (not B))))(assert (not B))(assert C)");
__static_condition_renaming("__static_condition_default_20", "(declare-fun B () Bool)(declare-fun A () Bool)(declare-fun C () Bool)(assert (or (and A B) (and A (not B))))(assert (not B))(assert (not C))");
__static_condition_renaming("__static_condition_default_21", "(declare-fun B () Bool)(declare-fun A () Bool)(declare-fun C () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert B)(assert C)");
__static_condition_renaming("__static_condition_default_22", "(declare-fun B () Bool)(declare-fun A () Bool)(declare-fun C () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert B)(assert (not C))");
__static_condition_renaming("__static_condition_default_23", "(declare-fun B () Bool)(declare-fun A () Bool)(declare-fun C () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert (not B))(assert C)");
__static_condition_renaming("__static_condition_default_24", "(declare-fun B () Bool)(declare-fun A () Bool)(declare-fun C () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert (not B))(assert (not C))");

};

int  __main_0 (void  ) {
{
int  __x_1;
char  __x_2;
unsigned int  __y_3;
unsigned char  __y_4;
int  __z_5;
int  __w_6;
int  __u_7;
int  __v_8;
long  __t_9;
short  __t_10;

{
if (__static_condition_default_11) {
 __x_1  = 2 ;

}

if (__static_condition_default_12) {
 __x_2  = 2 ;

}

}
{
if (__static_condition_default_13) {
 __y_3  = 3 ;

}

if (__static_condition_default_14) {
 __y_4  = 3 ;

}

} __z_5  = 5 ;

 __w_6  = 1 ;

 __u_7  = 7 ;

 __v_8  = 6 ;


{
if (__static_condition_default_15) {
 __t_9  = 8 ;

}

if (__static_condition_default_16) {
 __t_10  = 8 ;

}

}
{
if (__static_condition_default_17) {
 __x_1  =  __y_3  +  __z_5  -  __w_6  *  __u_7  /  __v_8  %  __t_9  ;

}

if (__static_condition_default_18) {
 __x_1  =  __y_3  +  __z_5  -  __w_6  *  __u_7  /  __v_8  %  __t_10  ;

}

if (__static_condition_default_19) {
 __x_1  =  __y_4  +  __z_5  -  __w_6  *  __u_7  /  __v_8  %  __t_9  ;

}

if (__static_condition_default_20) {
 __x_1  =  __y_4  +  __z_5  -  __w_6  *  __u_7  /  __v_8  %  __t_10  ;

}

if (__static_condition_default_21) {
 __x_2  =  __y_3  +  __z_5  -  __w_6  *  __u_7  /  __v_8  %  __t_9  ;

}

if (__static_condition_default_22) {
 __x_2  =  __y_3  +  __z_5  -  __w_6  *  __u_7  /  __v_8  %  __t_10  ;

}

if (__static_condition_default_23) {
 __x_2  =  __y_4  +  __z_5  -  __w_6  *  __u_7  /  __v_8  %  __t_9  ;

}

if (__static_condition_default_24) {
 __x_2  =  __y_4  +  __z_5  -  __w_6  *  __u_7  /  __v_8  %  __t_10  ;

}

}return 0 ;

}


}

