#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__X509_ALGOR_1", "X509_ALGOR");


};
typedef struct __forward_tag_reference_0  __X509_ALGOR_1;// L1
struct __X509_algor_st_2 {
int  (* __algorithm_3);
char  (* __parameter_4);
};
struct __Netscape_spki_st_5 {
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __X509_algor_st_2 __X509_algor_st_2;
};
};

// typedef moved to top of scope
struct __X509_algor_st_2 ;// L2

