#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_190;
extern const bool __static_condition_default_221;
extern const bool __static_condition_default_220;
extern const bool __static_condition_default_195;
extern const bool __static_condition_default_208;
extern const bool __static_condition_default_211;
extern const bool __static_condition_default_227;
extern const bool __static_condition_default_223;
extern const bool __static_condition_default_175;
extern const bool __static_condition_default_215;
extern const bool __static_condition_default_222;
extern const bool __static_condition_default_191;
extern const bool __static_condition_default_182;
extern const bool __static_condition_default_13;
void __static_initializer_default() {
__static_renaming("__ptrdiff_t_0", "ptrdiff_t");
__static_renaming("__size_t_1", "size_t");
__static_renaming("__memmove_8", "memmove");
__static_renaming("__memset_17", "memset");
__static_renaming("__memset_18", "memset");
__static_renaming("__memcmp_22", "memcmp");
__static_renaming("__memchr_26", "memchr");
__static_renaming("__strcpy_29", "strcpy");
__static_renaming("__strncpy_33", "strncpy");
__static_renaming("__strcat_36", "strcat");
__static_renaming("__strncat_40", "strncat");
__static_renaming("__strcmp_43", "strcmp");
__static_renaming("__strncmp_47", "strncmp");
__static_renaming("__strcoll_50", "strcoll");
__static_renaming("__strxfrm_54", "strxfrm");
__static_renaming("____locale_t_62", "__locale_t");
__static_renaming("__locale_t_63", "locale_t");
__static_renaming("__strcoll_l_67", "strcoll_l");
__static_renaming("__strxfrm_l_72", "strxfrm_l");
__static_renaming("__strdup_74", "strdup");
__static_renaming("__strndup_77", "strndup");
__static_renaming("__strchr_80", "strchr");
__static_renaming("__strrchr_83", "strrchr");
__static_renaming("__strcspn_86", "strcspn");
__static_renaming("__strspn_89", "strspn");
__static_renaming("__strpbrk_92", "strpbrk");
__static_renaming("__strstr_95", "strstr");
__static_renaming("__strtok_98", "strtok");
__static_renaming("____strtok_r_102", "__strtok_r");
__static_renaming("__strtok_r_106", "strtok_r");
__static_renaming("__strlen_108", "strlen");
__static_renaming("__strlen_109", "strlen");
__static_renaming("__strnlen_112", "strnlen");
__static_renaming("__strerror_114", "strerror");
__static_renaming("__strerror_115", "strerror");
__static_renaming("__strerror_r_119", "strerror_r");
__static_renaming("__strerror_l_122", "strerror_l");
__static_renaming("____bzero_125", "__bzero");
__static_renaming("____bzero_126", "__bzero");
__static_renaming("__bcopy_130", "bcopy");
__static_renaming("__bzero_133", "bzero");
__static_renaming("__bcmp_137", "bcmp");
__static_renaming("__index_140", "index");
__static_renaming("__rindex_143", "rindex");
__static_renaming("__ffs_145", "ffs");
__static_renaming("__strcasecmp_148", "strcasecmp");
__static_renaming("__strncasecmp_152", "strncasecmp");
__static_renaming("__strsep_155", "strsep");
__static_renaming("__strsignal_157", "strsignal");
__static_renaming("____stpcpy_160", "__stpcpy");
__static_renaming("__stpcpy_163", "stpcpy");
__static_renaming("____stpncpy_167", "__stpncpy");
__static_renaming("__stpncpy_171", "stpncpy");
__static_renaming("____stpncpy_chk_200", "__stpncpy_chk");
__static_renaming("____stpncpy_alias_204", "__stpncpy_alias");
__static_renaming("__strchr_pointer_216", "strchr_pointer");
__static_renaming("__strchr_pointer_217", "strchr_pointer");
__static_renaming("__starpos_218", "starpos");
__static_renaming("__process_commands_219", "process_commands");
__static_renaming("__main_226", "main");

__static_condition_renaming("__static_condition_default_13", "!(defined __STRICT_ANSI__)");
__static_condition_renaming("__static_condition_default_175", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_182", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_190", "(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_191", "!(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_195", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_208", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_211", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_215", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_220", "!(defined SDSUPPORT)");
__static_condition_renaming("__static_condition_default_221", "(defined SDSUPPORT)");
__static_condition_renaming("__static_condition_default_222", "!(defined _FORTIFY_SOURCE) && !(defined __CORRECT_ISO_CPP_STRING_H_PROTO) && (defined SDSUPPORT) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __CORRECT_ISO_CPP_STRING_H_PROTO) && (defined SDSUPPORT) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __CORRECT_ISO_CPP_STRING_H_PROTO) && (defined SDSUPPORT) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __CORRECT_ISO_CPP_STRING_H_PROTO) && (defined SDSUPPORT)");
__static_condition_renaming("__static_condition_default_223", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __CORRECT_ISO_CPP_STRING_H_PROTO) && (defined SDSUPPORT)");
__static_condition_renaming("__static_condition_default_227", "(defined __CORRECT_ISO_CPP_STRING_H_PROTO)");

if (__static_condition_default_227) {
__static_parse_error("Unable to parse");
}
};
typedef long int  __ptrdiff_t_0;// L143:L324
typedef long unsigned int  __size_t_1;// L177:L209
struct ____locale_struct_56 {
struct __forward_tag_reference_55  * (____locales_57[13]);// L0
const unsigned short int  * (____ctype_b_58);// L33
const int  * (____ctype_tolower_59);// L34
const int  * (____ctype_toupper_60);// L35
const char  * (____names_61[13]);// L38
};
typedef struct ____locale_struct_56  * (____locale_t_62);// L27:L39
typedef ____locale_t_62  __locale_t_63;// L42

struct __forward_tag_reference_55 { // generated union of struct variations
union {
};
};

// typedef moved to top of scope
// typedef moved to top of scope
extern void  * ((__memmove_8) (void  * (____dest_5), const void  * (____src_6), __size_t_1  ____n_7));// L46:L47
extern void  * ((__memset_17) (void  * (____s_14), int  ____c_15, __size_t_1  ____n_16));// L62
extern void  * ((__memset_18) (void  * (____s_14), int  ____c_15, __size_t_1  ____n_16));// L62
extern int  (__memcmp_22) (const void  * (____s1_19), const void  * (____s2_20), __size_t_1  ____n_21);// L65:L66
extern void  * ((__memchr_26) (const void  * (____s_23), int  ____c_24, __size_t_1  ____n_25));// L92:L93
extern char  * ((__strcpy_29) (char  * __restrict  ____dest_27, const char  * __restrict  ____src_28));// L125:L126
extern char  * ((__strncpy_33) (char  * __restrict  ____dest_30, const char  * __restrict  ____src_31, __size_t_1  ____n_32));// L128:L130
extern char  * ((__strcat_36) (char  * __restrict  ____dest_34, const char  * __restrict  ____src_35));// L133:L134
extern char  * ((__strncat_40) (char  * __restrict  ____dest_37, const char  * __restrict  ____src_38, __size_t_1  ____n_39));// L136:L137
extern int  (__strcmp_43) (const char  * (____s1_41), const char  * (____s2_42));// L140:L141
extern int  (__strncmp_47) (const char  * (____s1_44), const char  * (____s2_45), __size_t_1  ____n_46);// L143:L144
extern int  (__strcoll_50) (const char  * (____s1_48), const char  * (____s2_49));// L147:L148
extern __size_t_1  (__strxfrm_54) (char  * __restrict  ____dest_51, const char  * __restrict  ____src_52, __size_t_1  ____n_53);// L150:L152
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__strcoll_l_67) (const char  * (____s1_64), const char  * (____s2_65), ____locale_t_62  ____l_66);// L162:L163
extern __size_t_1  (__strxfrm_l_72) (char  * (____dest_68), const char  * (____src_69), __size_t_1  ____n_70, ____locale_t_62  ____l_71);// L165:L166
extern char  * ((__strdup_74) (const char  * (____s_73)));// L171:L172
extern char  * ((__strndup_77) (const char  * (____string_75), __size_t_1  ____n_76));// L179:L180
extern char  * ((__strchr_80) (const char  * (____s_78), int  ____c_79));// L231:L232
extern char  * ((__strrchr_83) (const char  * (____s_81), int  ____c_82));// L258:L259
extern __size_t_1  (__strcspn_86) (const char  * (____s_84), const char  * (____reject_85));// L280:L281
extern __size_t_1  (__strspn_89) (const char  * (____s_87), const char  * (____accept_88));// L284:L285
extern char  * ((__strpbrk_92) (const char  * (____s_90), const char  * (____accept_91)));// L310:L311
extern char  * ((__strstr_95) (const char  * (____haystack_93), const char  * (____needle_94)));// L337:L338
extern char  * ((__strtok_98) (char  * __restrict  ____s_96, const char  * __restrict  ____delim_97));// L343:L344
extern char  * ((____strtok_r_102) (char  * __restrict  ____s_99, const char  * __restrict  ____delim_100, char  * (* __restrict  ____save_ptr_101)));// L349:L352
extern char  * ((__strtok_r_106) (char  * __restrict  ____s_103, const char  * __restrict  ____delim_104, char  * (* __restrict  ____save_ptr_105)));// L354:L356
extern __size_t_1  (__strlen_108) (const char  * (____s_107));// L394:L395
extern __size_t_1  (__strlen_109) (const char  * (____s_107));// L394:L395
extern __size_t_1  (__strnlen_112) (const char  * (____string_110), __size_t_1  ____maxlen_111);// L401:L402
extern char  * ((__strerror_114) (int  ____errnum_113));// L408
extern char  * ((__strerror_115) (int  ____errnum_113));// L408
extern int  (__strerror_r_119) (int  ____errnum_116, char  * (____buf_117), __size_t_1  ____buflen_118);// L422:L424
extern char  * ((__strerror_l_122) (int  ____errnum_120, ____locale_t_62  ____l_121));// L440
extern void  (____bzero_125) (void  * (____s_123), __size_t_1  ____n_124);// L446
extern void  (____bzero_126) (void  * (____s_123), __size_t_1  ____n_124);// L446
extern void  (__bcopy_130) (const void  * (____src_127), void  * (____dest_128), __size_t_1  ____n_129);// L450:L451
extern void  (__bzero_133) (void  * (____s_131), __size_t_1  ____n_132);// L454
extern int  (__bcmp_137) (const void  * (____s1_134), const void  * (____s2_135), __size_t_1  ____n_136);// L457:L458
extern char  * ((__index_140) (const char  * (____s_138), int  ____c_139));// L484:L485
extern char  * ((__rindex_143) (const char  * (____s_141), int  ____c_142));// L512:L513
extern int  (__ffs_145) (int  ____i_144);// L518
extern int  (__strcasecmp_148) (const char  * (____s1_146), const char  * (____s2_147));// L529:L530
extern int  (__strncasecmp_152) (const char  * (____s1_149), const char  * (____s2_150), __size_t_1  ____n_151);// L533:L534
extern char  * ((__strsep_155) (char  * (* __restrict  ____stringp_153), const char  * __restrict  ____delim_154));// L552:L554
extern char  * ((__strsignal_157) (int  ____sig_156));// L559
extern char  * ((____stpcpy_160) (char  * __restrict  ____dest_158, const char  * __restrict  ____src_159));// L562:L563
extern char  * ((__stpcpy_163) (char  * __restrict  ____dest_161, const char  * __restrict  ____src_162));// L564:L565
extern char  * ((____stpncpy_167) (char  * __restrict  ____dest_164, const char  * __restrict  ____src_165, __size_t_1  ____n_166));// L569:L571
extern char  * ((__stpncpy_171) (char  * __restrict  ____dest_168, const char  * __restrict  ____src_169, __size_t_1  ____n_170));// L572:L574
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
extern char  * ((____stpncpy_chk_200) (char  * (____dest_196), const char  * (____src_197), __size_t_1  ____n_198, __size_t_1  ____destlen_199));// L130:L131
extern char  * ((____stpncpy_alias_204) (char  * (____dest_201), const char  * (____src_202), __size_t_1  ____n_203));// L132:L133
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
static char  * (__strchr_pointer_216)= "eiffel~1.gco*57";// L3
static char  * (__strchr_pointer_217)= "eiffel~1.gco*57";// L3
void  (__process_commands_219) () {

{
if (__static_condition_default_220) {

{// L6
{



char  * (__starpos_218)= ( ( void  * ) 0 );// L7

}
}// L14


}

if (__static_condition_default_221) {

{// L6
{



char  * (__starpos_218)= ( ( void  * ) 0 );// L7

if (__static_condition_default_222) {
 __starpos_218  = (  __strchr_80  ( __strchr_pointer_216  + 4,'*') ) ; // L9
}
if (__static_condition_default_223) {
 __starpos_218  = (  __strchr_80  ( __strchr_pointer_217  + 4,'*') ) ; // L9
}
if (  __starpos_218  != ( ( void  * ) 0 ) )// L10
{
* (  __starpos_218  - 1 ) = '\0' ; // L11
}
__static_type_error("type error : no valid expression"); // L12
}
}// L14


}

}}
int  (__main_226) (int  __argc_224, char  * (* (__argv_225))) {

{// L17
{



 __process_commands_219 ( ) ; // L18
return 0 ;// L19
}
}// L20


}

