#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {


};
struct ____s_0_1 {
int  __x_2;// L2
struct __forward_tag_reference_0  (* __z_3);// L0
};
struct ____t_1_4 {
int  __p_5;// L6
};
union ____anonymous_tag_6_7 {
struct ____t_1_4  ____t_1_8;// L11
};
struct __t_9 {
union ____anonymous_tag_6_7  __anon_id_0_10;// L9
};
union ____anonymous_tag_11_12 {
struct ____s_0_1  ____s_0_13;// L17
};
struct __s_14 {
union ____anonymous_tag_11_12  __anon_id_1_15;// L15
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __t_9 __t_9;
};
};

struct ____s_0_1 ;// L1
struct ____t_1_4 ;// L5
struct __t_9 ;// L8
struct __s_14 ;// L14

