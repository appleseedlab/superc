#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__len_and_sockaddr_12", "len_and_sockaddr");
__static_renaming("__main_13", "main");


};
union __anonymous_tag_3 {
};
union __anonymous_tag_4 {
struct __forward_tag_reference_0  __sa_5;
struct __forward_tag_reference_1  __sin_6;
struct __forward_tag_reference_2  __sin6_7;
};
struct __len_and_sockaddr_8 {
int  __len_9;
union __anonymous_tag_3  __u_10;
union __anonymous_tag_4  __u_11;
};
typedef struct __len_and_sockaddr_8  __len_and_sockaddr_12;

struct __forward_tag_reference_2 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_1 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
};
};

// typedef moved to top of scope
int  __main_13 () {
{
__builtin_offsetof ( __len_and_sockaddr_12   , u  ) ;

__builtin_offsetof ( int   , u  ) ;

}


}

