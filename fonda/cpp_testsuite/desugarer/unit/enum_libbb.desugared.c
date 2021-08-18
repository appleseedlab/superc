#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {


};
enum ____anonymous_tag_18_19 {
__FILEUTILS_PRESERVE_STATUS_0 = 1 << 0,
__FILEUTILS_DEREFERENCE_1 = 1 << 1,
__FILEUTILS_RECUR_2 = 1 << 2,
__FILEUTILS_FORCE_3 = 1 << 3,
__FILEUTILS_INTERACTIVE_4 = 1 << 4,
__FILEUTILS_MAKE_HARDLINK_5 = 1 << 5,
__FILEUTILS_MAKE_SOFTLINK_6 = 1 << 6,
__FILEUTILS_DEREF_SOFTLINK_7 = 1 << 7,
__FILEUTILS_DEREFERENCE_L0_8 = 1 << 8,
__FILEUTILS_VERBOSE_9 = ( 1 << 12 ) * 1,
__FILEUTILS_VERBOSE_10 = ( 1 << 12 ) * 0,
__FILEUTILS_UPDATE_11 = 1 << 13,
__FILEUTILS_PRESERVE_SECURITY_CONTEXT_12 = 1 << 14,
__FILEUTILS_RMDEST_13 = 1 << ( 15 - ! 1 ),
__FILEUTILS_RMDEST_14 = 1 << ( 15 - ! 0 ),
__FILEUTILS_SET_SECURITY_CONTEXT_15 = 1 << 30,
__FILEUTILS_IGNORE_CHMOD_ERR_16 = 1 << 31,
__FILEUTILS_IGNORE_CHMOD_ERR_17 = 1 << 31,
};

enum ____anonymous_tag_18_19 ;// L33

