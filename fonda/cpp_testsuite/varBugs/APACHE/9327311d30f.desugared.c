#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_183;
extern const bool __static_condition_default_221;
extern const bool __static_condition_default_209;
extern const bool __static_condition_default_223;
extern const bool __static_condition_default_192;
extern const bool __static_condition_default_212;
extern const bool __static_condition_default_222;
extern const bool __static_condition_default_229;
extern const bool __static_condition_default_224;
extern const bool __static_condition_default_228;
extern const bool __static_condition_default_191;
extern const bool __static_condition_default_216;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_196;
extern const bool __static_condition_default_176;
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
__static_renaming("__strchr_81", "strchr");
__static_renaming("__strrchr_84", "strrchr");
__static_renaming("__strcspn_87", "strcspn");
__static_renaming("__strspn_90", "strspn");
__static_renaming("__strpbrk_93", "strpbrk");
__static_renaming("__strstr_96", "strstr");
__static_renaming("__strtok_99", "strtok");
__static_renaming("____strtok_r_103", "__strtok_r");
__static_renaming("__strtok_r_107", "strtok_r");
__static_renaming("__strlen_109", "strlen");
__static_renaming("__strlen_110", "strlen");
__static_renaming("__strnlen_113", "strnlen");
__static_renaming("__strerror_115", "strerror");
__static_renaming("__strerror_116", "strerror");
__static_renaming("__strerror_r_120", "strerror_r");
__static_renaming("__strerror_l_123", "strerror_l");
__static_renaming("____bzero_126", "__bzero");
__static_renaming("____bzero_127", "__bzero");
__static_renaming("__bcopy_131", "bcopy");
__static_renaming("__bzero_134", "bzero");
__static_renaming("__bcmp_138", "bcmp");
__static_renaming("__index_141", "index");
__static_renaming("__rindex_144", "rindex");
__static_renaming("__ffs_146", "ffs");
__static_renaming("__strcasecmp_149", "strcasecmp");
__static_renaming("__strncasecmp_153", "strncasecmp");
__static_renaming("__strsep_156", "strsep");
__static_renaming("__strsignal_158", "strsignal");
__static_renaming("____stpcpy_161", "__stpcpy");
__static_renaming("__stpcpy_164", "stpcpy");
__static_renaming("____stpncpy_168", "__stpncpy");
__static_renaming("__stpncpy_172", "stpncpy");
__static_renaming("____stpncpy_chk_201", "__stpncpy_chk");
__static_renaming("____stpncpy_alias_205", "__stpncpy_alias");
__static_renaming("__rmm_addr_217", "rmm_addr");
__static_renaming("__rmm_addr_218", "rmm_addr");
__static_renaming("__util_ald_create_cache_220", "util_ald_create_cache");
__static_renaming("__util_ald_create_caches_226", "util_ald_create_caches");
__static_renaming("__main_227", "main");

__static_condition_renaming("__static_condition_default_13", "!(defined __STRICT_ANSI__)");
__static_condition_renaming("__static_condition_default_176", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_183", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_191", "(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_192", "!(defined __STRICT_ANSI__) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_196", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_209", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_212", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_216", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_221", "!APR_HAS_SHARED_MEMORY");
__static_condition_renaming("__static_condition_default_222", "APR_HAS_SHARED_MEMORY");
__static_condition_renaming("__static_condition_default_223", "!(defined _FORTIFY_SOURCE) && APR_HAS_SHARED_MEMORY || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && APR_HAS_SHARED_MEMORY || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && APR_HAS_SHARED_MEMORY || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && APR_HAS_SHARED_MEMORY");
__static_condition_renaming("__static_condition_default_224", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && APR_HAS_SHARED_MEMORY");
__static_condition_renaming("__static_condition_default_228", "!(defined _FORTIFY_SOURCE) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0)");
__static_condition_renaming("__static_condition_default_229", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0)");

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
extern char  * ((__strchr_81) (const char  * (____s_78), int  ____c_79));// L231:L232
extern char  * ((__strrchr_84) (const char  * (____s_82), int  ____c_83));// L258:L259
extern __size_t_1  (__strcspn_87) (const char  * (____s_85), const char  * (____reject_86));// L280:L281
extern __size_t_1  (__strspn_90) (const char  * (____s_88), const char  * (____accept_89));// L284:L285
extern char  * ((__strpbrk_93) (const char  * (____s_91), const char  * (____accept_92)));// L310:L311
extern char  * ((__strstr_96) (const char  * (____haystack_94), const char  * (____needle_95)));// L337:L338
extern char  * ((__strtok_99) (char  * __restrict  ____s_97, const char  * __restrict  ____delim_98));// L343:L344
extern char  * ((____strtok_r_103) (char  * __restrict  ____s_100, const char  * __restrict  ____delim_101, char  * (* __restrict  ____save_ptr_102)));// L349:L352
extern char  * ((__strtok_r_107) (char  * __restrict  ____s_104, const char  * __restrict  ____delim_105, char  * (* __restrict  ____save_ptr_106)));// L354:L356
extern __size_t_1  (__strlen_109) (const char  * (____s_108));// L394:L395
extern __size_t_1  (__strlen_110) (const char  * (____s_108));// L394:L395
extern __size_t_1  (__strnlen_113) (const char  * (____string_111), __size_t_1  ____maxlen_112);// L401:L402
extern char  * ((__strerror_115) (int  ____errnum_114));// L408
extern char  * ((__strerror_116) (int  ____errnum_114));// L408
extern int  (__strerror_r_120) (int  ____errnum_117, char  * (____buf_118), __size_t_1  ____buflen_119);// L422:L424
extern char  * ((__strerror_l_123) (int  ____errnum_121, ____locale_t_62  ____l_122));// L440
extern void  (____bzero_126) (void  * (____s_124), __size_t_1  ____n_125);// L446
extern void  (____bzero_127) (void  * (____s_124), __size_t_1  ____n_125);// L446
extern void  (__bcopy_131) (const void  * (____src_128), void  * (____dest_129), __size_t_1  ____n_130);// L450:L451
extern void  (__bzero_134) (void  * (____s_132), __size_t_1  ____n_133);// L454
extern int  (__bcmp_138) (const void  * (____s1_135), const void  * (____s2_136), __size_t_1  ____n_137);// L457:L458
extern char  * ((__index_141) (const char  * (____s_139), int  ____c_140));// L484:L485
extern char  * ((__rindex_144) (const char  * (____s_142), int  ____c_143));// L512:L513
extern int  (__ffs_146) (int  ____i_145);// L518
extern int  (__strcasecmp_149) (const char  * (____s1_147), const char  * (____s2_148));// L529:L530
extern int  (__strncasecmp_153) (const char  * (____s1_150), const char  * (____s2_151), __size_t_1  ____n_152);// L533:L534
extern char  * ((__strsep_156) (char  * (* __restrict  ____stringp_154), const char  * __restrict  ____delim_155));// L552:L554
extern char  * ((__strsignal_158) (int  ____sig_157));// L559
extern char  * ((____stpcpy_161) (char  * __restrict  ____dest_159, const char  * __restrict  ____src_160));// L562:L563
extern char  * ((__stpcpy_164) (char  * __restrict  ____dest_162, const char  * __restrict  ____src_163));// L564:L565
extern char  * ((____stpncpy_168) (char  * __restrict  ____dest_165, const char  * __restrict  ____src_166, __size_t_1  ____n_167));// L569:L571
extern char  * ((__stpncpy_172) (char  * __restrict  ____dest_169, const char  * __restrict  ____src_170, __size_t_1  ____n_171));// L572:L574
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
extern char  * ((____stpncpy_chk_201) (char  * (____dest_197), const char  * (____src_198), __size_t_1  ____n_199, __size_t_1  ____destlen_200));// L130:L131
extern char  * ((____stpncpy_alias_205) (char  * (____dest_202), const char  * (____src_203), __size_t_1  ____n_204));// L132:L133
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
char  * (__rmm_addr_217);// L3
char  * (__rmm_addr_218);// L3
void  (__util_ald_create_cache_220) (char  * (__rmm_addr_219)) {

{
if (__static_condition_default_221) {

{
{



}
}


}

if (__static_condition_default_222) {

{
{



if (__static_condition_default_223) {
 __strcat_36  ( __rmm_addr_219 ,"something") ; // L8
}
if (__static_condition_default_224) {
__static_type_error("type error") ; // L8
}
}
}


}

}}
void  (__util_ald_create_caches_226) (char  * (__rmm_addr_225)) {

{
{



 __util_ald_create_cache_220  ( __rmm_addr_225 ) ; // L16
}
}


}
int  (__main_227) (void  ) {

{
{



if (__static_condition_default_228) {
 __util_ald_create_caches_226  ( __rmm_addr_217 ) ; // L21
}
if (__static_condition_default_229) {
 __util_ald_create_caches_226  ( __rmm_addr_218 ) ; // L21
}
return 0 ;// L22
}
}


}

