#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__ptrdiff_t_0", "ptrdiff_t");
__static_renaming("__size_t_1", "size_t");
__static_renaming("__memmove_8", "memmove");
__static_renaming("__memset_16", "memset");
__static_renaming("__memcmp_20", "memcmp");
__static_renaming("__memchr_24", "memchr");
__static_renaming("__strcpy_27", "strcpy");
__static_renaming("__strncpy_31", "strncpy");
__static_renaming("__strcat_34", "strcat");
__static_renaming("__strncat_38", "strncat");
__static_renaming("__strcmp_41", "strcmp");
__static_renaming("__strncmp_45", "strncmp");
__static_renaming("__strcoll_48", "strcoll");
__static_renaming("__strxfrm_52", "strxfrm");
__static_renaming("____locale_t_60", "__locale_t");
__static_renaming("__locale_t_61", "locale_t");
__static_renaming("__strcoll_l_65", "strcoll_l");
__static_renaming("__strxfrm_l_70", "strxfrm_l");
__static_renaming("__strdup_72", "strdup");
__static_renaming("__strndup_75", "strndup");
__static_renaming("__strchr_78", "strchr");
__static_renaming("__strrchr_81", "strrchr");
__static_renaming("__strcspn_84", "strcspn");
__static_renaming("__strspn_87", "strspn");
__static_renaming("__strpbrk_90", "strpbrk");
__static_renaming("__strstr_93", "strstr");
__static_renaming("__strtok_96", "strtok");
__static_renaming("____strtok_r_100", "__strtok_r");
__static_renaming("__strtok_r_104", "strtok_r");
__static_renaming("__strlen_106", "strlen");
__static_renaming("__strnlen_109", "strnlen");
__static_renaming("__strerror_111", "strerror");
__static_renaming("__strerror_r_115", "strerror_r");
__static_renaming("__strerror_l_118", "strerror_l");
__static_renaming("____bzero_121", "__bzero");
__static_renaming("__bcopy_125", "bcopy");
__static_renaming("__bzero_128", "bzero");
__static_renaming("__bcmp_132", "bcmp");
__static_renaming("__index_135", "index");
__static_renaming("__rindex_138", "rindex");
__static_renaming("__ffs_140", "ffs");
__static_renaming("__strcasecmp_143", "strcasecmp");
__static_renaming("__strncasecmp_147", "strncasecmp");
__static_renaming("__strsep_150", "strsep");
__static_renaming("__strsignal_152", "strsignal");
__static_renaming("____stpcpy_155", "__stpcpy");
__static_renaming("__stpcpy_158", "stpcpy");
__static_renaming("____stpncpy_162", "__stpncpy");
__static_renaming("__stpncpy_166", "stpncpy");
__static_renaming("__main_169", "main");


};
typedef long int  __ptrdiff_t_0;// L143:L324
typedef long unsigned int  __size_t_1;// L177:L209
struct ____locale_struct_54 {
struct __forward_tag_reference_53  * (____locales_55[13]);// L0
const unsigned short int  * (____ctype_b_56);// L33
const int  * (____ctype_tolower_57);// L34
const int  * (____ctype_toupper_58);// L35
const char  * (____names_59[13]);// L38
};
typedef struct ____locale_struct_54  * (____locale_t_60);// L27:L39
typedef ____locale_t_60  __locale_t_61;// L42

struct __forward_tag_reference_53 { // generated union of struct variations
union {
};
};

// typedef moved to top of scope
// typedef moved to top of scope
extern void  * ((__memmove_8) (void  * (____dest_5), const void  * (____src_6), __size_t_1  ____n_7));// L46:L47
extern void  * ((__memset_16) (void  * (____s_13), int  ____c_14, __size_t_1  ____n_15));// L62
extern int  (__memcmp_20) (const void  * (____s1_17), const void  * (____s2_18), __size_t_1  ____n_19);// L65:L66
extern void  * ((__memchr_24) (const void  * (____s_21), int  ____c_22, __size_t_1  ____n_23));// L92:L93
extern char  * ((__strcpy_27) (char  * __restrict  ____dest_25, const char  * __restrict  ____src_26));// L125:L126
extern char  * ((__strncpy_31) (char  * __restrict  ____dest_28, const char  * __restrict  ____src_29, __size_t_1  ____n_30));// L128:L130
extern char  * ((__strcat_34) (char  * __restrict  ____dest_32, const char  * __restrict  ____src_33));// L133:L134
extern char  * ((__strncat_38) (char  * __restrict  ____dest_35, const char  * __restrict  ____src_36, __size_t_1  ____n_37));// L136:L137
extern int  (__strcmp_41) (const char  * (____s1_39), const char  * (____s2_40));// L140:L141
extern int  (__strncmp_45) (const char  * (____s1_42), const char  * (____s2_43), __size_t_1  ____n_44);// L143:L144
extern int  (__strcoll_48) (const char  * (____s1_46), const char  * (____s2_47));// L147:L148
extern __size_t_1  (__strxfrm_52) (char  * __restrict  ____dest_49, const char  * __restrict  ____src_50, __size_t_1  ____n_51);// L150:L152
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__strcoll_l_65) (const char  * (____s1_62), const char  * (____s2_63), ____locale_t_60  ____l_64);// L162:L163
extern __size_t_1  (__strxfrm_l_70) (char  * (____dest_66), const char  * (____src_67), __size_t_1  ____n_68, ____locale_t_60  ____l_69);// L165:L166
extern char  * ((__strdup_72) (const char  * (____s_71)));// L171:L172
extern char  * ((__strndup_75) (const char  * (____string_73), __size_t_1  ____n_74));// L179:L180
extern char  * ((__strchr_78) (const char  * (____s_76), int  ____c_77));// L231:L232
extern char  * ((__strrchr_81) (const char  * (____s_79), int  ____c_80));// L258:L259
extern __size_t_1  (__strcspn_84) (const char  * (____s_82), const char  * (____reject_83));// L280:L281
extern __size_t_1  (__strspn_87) (const char  * (____s_85), const char  * (____accept_86));// L284:L285
extern char  * ((__strpbrk_90) (const char  * (____s_88), const char  * (____accept_89)));// L310:L311
extern char  * ((__strstr_93) (const char  * (____haystack_91), const char  * (____needle_92)));// L337:L338
extern char  * ((__strtok_96) (char  * __restrict  ____s_94, const char  * __restrict  ____delim_95));// L343:L344
extern char  * ((____strtok_r_100) (char  * __restrict  ____s_97, const char  * __restrict  ____delim_98, char  * (* __restrict  ____save_ptr_99)));// L349:L352
extern char  * ((__strtok_r_104) (char  * __restrict  ____s_101, const char  * __restrict  ____delim_102, char  * (* __restrict  ____save_ptr_103)));// L354:L356
extern __size_t_1  (__strlen_106) (const char  * (____s_105));// L394:L395
extern __size_t_1  (__strnlen_109) (const char  * (____string_107), __size_t_1  ____maxlen_108);// L401:L402
extern char  * ((__strerror_111) (int  ____errnum_110));// L408
extern int  (__strerror_r_115) (int  ____errnum_112, char  * (____buf_113), __size_t_1  ____buflen_114);// L422:L424
extern char  * ((__strerror_l_118) (int  ____errnum_116, ____locale_t_60  ____l_117));// L440
extern void  (____bzero_121) (void  * (____s_119), __size_t_1  ____n_120);// L446
extern void  (__bcopy_125) (const void  * (____src_122), void  * (____dest_123), __size_t_1  ____n_124);// L450:L451
extern void  (__bzero_128) (void  * (____s_126), __size_t_1  ____n_127);// L454
extern int  (__bcmp_132) (const void  * (____s1_129), const void  * (____s2_130), __size_t_1  ____n_131);// L457:L458
extern char  * ((__index_135) (const char  * (____s_133), int  ____c_134));// L484:L485
extern char  * ((__rindex_138) (const char  * (____s_136), int  ____c_137));// L512:L513
extern int  (__ffs_140) (int  ____i_139);// L518
extern int  (__strcasecmp_143) (const char  * (____s1_141), const char  * (____s2_142));// L529:L530
extern int  (__strncasecmp_147) (const char  * (____s1_144), const char  * (____s2_145), __size_t_1  ____n_146);// L533:L534
extern char  * ((__strsep_150) (char  * (* __restrict  ____stringp_148), const char  * __restrict  ____delim_149));// L552:L554
extern char  * ((__strsignal_152) (int  ____sig_151));// L559
extern char  * ((____stpcpy_155) (char  * __restrict  ____dest_153, const char  * __restrict  ____src_154));// L562:L563
extern char  * ((__stpcpy_158) (char  * __restrict  ____dest_156, const char  * __restrict  ____src_157));// L564:L565
extern char  * ((____stpncpy_162) (char  * __restrict  ____dest_159, const char  * __restrict  ____src_160, __size_t_1  ____n_161));// L569:L571
extern char  * ((__stpncpy_166) (char  * __restrict  ____dest_163, const char  * __restrict  ____src_164, __size_t_1  ____n_165));// L572:L574
int  (__main_169) (int  __argc_167, char  * (* (__argv_168))) {

{
{



__static_type_error("type error : no valid expression"); // L31
return 0 ;// L32
}
}


}

