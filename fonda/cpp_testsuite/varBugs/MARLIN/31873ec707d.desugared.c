#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__ptrdiff_t_0", "ptrdiff_t");
__static_renaming("__size_t_1", "size_t");
__static_renaming("____u_char_2", "__u_char");
__static_renaming("____u_short_3", "__u_short");
__static_renaming("____u_int_4", "__u_int");
__static_renaming("____u_long_5", "__u_long");
__static_renaming("____int8_t_6", "__int8_t");
__static_renaming("____uint8_t_7", "__uint8_t");
__static_renaming("____int16_t_8", "__int16_t");
__static_renaming("____uint16_t_9", "__uint16_t");
__static_renaming("____int32_t_10", "__int32_t");
__static_renaming("____uint32_t_11", "__uint32_t");
__static_renaming("____int64_t_12", "__int64_t");
__static_renaming("____uint64_t_13", "__uint64_t");
__static_renaming("____quad_t_14", "__quad_t");
__static_renaming("____u_quad_t_15", "__u_quad_t");
__static_renaming("____dev_t_16", "__dev_t");
__static_renaming("____uid_t_17", "__uid_t");
__static_renaming("____gid_t_18", "__gid_t");
__static_renaming("____ino_t_19", "__ino_t");
__static_renaming("____ino64_t_20", "__ino64_t");
__static_renaming("____mode_t_21", "__mode_t");
__static_renaming("____nlink_t_22", "__nlink_t");
__static_renaming("____off_t_23", "__off_t");
__static_renaming("____off64_t_24", "__off64_t");
__static_renaming("____pid_t_25", "__pid_t");
__static_renaming("____fsid_t_29", "__fsid_t");
__static_renaming("____clock_t_30", "__clock_t");
__static_renaming("____rlim_t_31", "__rlim_t");
__static_renaming("____rlim64_t_32", "__rlim64_t");
__static_renaming("____id_t_33", "__id_t");
__static_renaming("____time_t_34", "__time_t");
__static_renaming("____useconds_t_35", "__useconds_t");
__static_renaming("____suseconds_t_36", "__suseconds_t");
__static_renaming("____daddr_t_37", "__daddr_t");
__static_renaming("____key_t_38", "__key_t");
__static_renaming("____clockid_t_39", "__clockid_t");
__static_renaming("____timer_t_40", "__timer_t");
__static_renaming("____blksize_t_41", "__blksize_t");
__static_renaming("____blkcnt_t_42", "__blkcnt_t");
__static_renaming("____blkcnt64_t_43", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_44", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_45", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_46", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_47", "__fsfilcnt64_t");
__static_renaming("____fsword_t_48", "__fsword_t");
__static_renaming("____ssize_t_49", "__ssize_t");
__static_renaming("____syscall_slong_t_50", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_51", "__syscall_ulong_t");
__static_renaming("____loff_t_52", "__loff_t");
__static_renaming("____qaddr_t_53", "__qaddr_t");
__static_renaming("____caddr_t_54", "__caddr_t");
__static_renaming("____intptr_t_55", "__intptr_t");
__static_renaming("____socklen_t_56", "__socklen_t");
__static_renaming("__FILE_58", "FILE");
__static_renaming("____FILE_59", "__FILE");
__static_renaming("____mbstate_t_68", "__mbstate_t");
__static_renaming("____mbstate_t_69", "__mbstate_t");
__static_renaming("___G_fpos_t_75", "_G_fpos_t");
__static_renaming("___G_fpos64_t_81", "_G_fpos64_t");
__static_renaming("____gnuc_va_list_82", "__gnuc_va_list");
__static_renaming("___IO_lock_t_84", "_IO_lock_t");
__static_renaming("___IO_FILE_125", "_IO_FILE");
__static_renaming("___IO_2_1_stdin__127", "_IO_2_1_stdin_");
__static_renaming("___IO_2_1_stdout__128", "_IO_2_1_stdout_");
__static_renaming("___IO_2_1_stderr__129", "_IO_2_1_stderr_");
__static_renaming("____io_read_fn_133", "__io_read_fn");
__static_renaming("____io_write_fn_137", "__io_write_fn");
__static_renaming("____io_seek_fn_141", "__io_seek_fn");
__static_renaming("____io_close_fn_143", "__io_close_fn");
__static_renaming("____underflow_144", "__underflow");
__static_renaming("____uflow_145", "__uflow");
__static_renaming("____overflow_146", "__overflow");
__static_renaming("___IO_getc_148", "_IO_getc");
__static_renaming("___IO_putc_151", "_IO_putc");
__static_renaming("___IO_feof_153", "_IO_feof");
__static_renaming("___IO_ferror_155", "_IO_ferror");
__static_renaming("___IO_peekc_locked_157", "_IO_peekc_locked");
__static_renaming("___IO_flockfile_158", "_IO_flockfile");
__static_renaming("___IO_funlockfile_159", "_IO_funlockfile");
__static_renaming("___IO_ftrylockfile_160", "_IO_ftrylockfile");
__static_renaming("___IO_vfscanf_161", "_IO_vfscanf");
__static_renaming("___IO_vfprintf_162", "_IO_vfprintf");
__static_renaming("___IO_padn_163", "_IO_padn");
__static_renaming("___IO_sgetn_164", "_IO_sgetn");
__static_renaming("___IO_seekoff_165", "_IO_seekoff");
__static_renaming("___IO_seekpos_166", "_IO_seekpos");
__static_renaming("___IO_free_backup_area_167", "_IO_free_backup_area");
__static_renaming("__va_list_168", "va_list");
__static_renaming("__off_t_169", "off_t");
__static_renaming("__ssize_t_170", "ssize_t");
__static_renaming("__fpos_t_171", "fpos_t");
__static_renaming("__stdin_172", "stdin");
__static_renaming("__stdout_173", "stdout");
__static_renaming("__stderr_174", "stderr");
__static_renaming("__remove_176", "remove");
__static_renaming("__rename_179", "rename");
__static_renaming("__renameat_184", "renameat");
__static_renaming("__tmpfile_185", "tmpfile");
__static_renaming("__tmpnam_187", "tmpnam");
__static_renaming("__tmpnam_r_189", "tmpnam_r");
__static_renaming("__tempnam_192", "tempnam");
__static_renaming("__fclose_194", "fclose");
__static_renaming("__fflush_196", "fflush");
__static_renaming("__fflush_unlocked_198", "fflush_unlocked");
__static_renaming("__fopen_201", "fopen");
__static_renaming("__freopen_205", "freopen");
__static_renaming("__fdopen_208", "fdopen");
__static_renaming("__fmemopen_212", "fmemopen");
__static_renaming("__open_memstream_215", "open_memstream");
__static_renaming("__setbuf_218", "setbuf");
__static_renaming("__setvbuf_223", "setvbuf");
__static_renaming("__setbuffer_227", "setbuffer");
__static_renaming("__setlinebuf_229", "setlinebuf");
__static_renaming("__fprintf_232", "fprintf");
__static_renaming("__printf_234", "printf");
__static_renaming("__sprintf_237", "sprintf");
__static_renaming("__vfprintf_241", "vfprintf");
__static_renaming("__vprintf_244", "vprintf");
__static_renaming("__vsprintf_248", "vsprintf");
__static_renaming("__snprintf_252", "snprintf");
__static_renaming("__vsnprintf_257", "vsnprintf");
__static_renaming("__vdprintf_261", "vdprintf");
__static_renaming("__dprintf_264", "dprintf");
__static_renaming("__fscanf_267", "fscanf");
__static_renaming("__scanf_269", "scanf");
__static_renaming("__sscanf_272", "sscanf");
__static_renaming("__vfscanf_284", "vfscanf");
__static_renaming("__vscanf_287", "vscanf");
__static_renaming("__vsscanf_291", "vsscanf");
__static_renaming("__fgetc_304", "fgetc");
__static_renaming("__getc_306", "getc");
__static_renaming("__getchar_307", "getchar");
__static_renaming("__getc_unlocked_309", "getc_unlocked");
__static_renaming("__getchar_unlocked_310", "getchar_unlocked");
__static_renaming("__fgetc_unlocked_312", "fgetc_unlocked");
__static_renaming("__fputc_315", "fputc");
__static_renaming("__putc_318", "putc");
__static_renaming("__putchar_320", "putchar");
__static_renaming("__fputc_unlocked_323", "fputc_unlocked");
__static_renaming("__putc_unlocked_326", "putc_unlocked");
__static_renaming("__putchar_unlocked_328", "putchar_unlocked");
__static_renaming("__getw_330", "getw");
__static_renaming("__putw_333", "putw");
__static_renaming("__fgets_337", "fgets");
__static_renaming("____getdelim_342", "__getdelim");
__static_renaming("__getdelim_347", "getdelim");
__static_renaming("__getline_351", "getline");
__static_renaming("__fputs_354", "fputs");
__static_renaming("__puts_356", "puts");
__static_renaming("__ungetc_359", "ungetc");
__static_renaming("__fseek_379", "fseek");
__static_renaming("__ftell_381", "ftell");
__static_renaming("__rewind_383", "rewind");
__static_renaming("__fseeko_387", "fseeko");
__static_renaming("__ftello_389", "ftello");
__static_renaming("__fgetpos_392", "fgetpos");
__static_renaming("__fsetpos_395", "fsetpos");
__static_renaming("__clearerr_397", "clearerr");
__static_renaming("__feof_399", "feof");
__static_renaming("__ferror_401", "ferror");
__static_renaming("__clearerr_unlocked_403", "clearerr_unlocked");
__static_renaming("__feof_unlocked_405", "feof_unlocked");
__static_renaming("__ferror_unlocked_407", "ferror_unlocked");
__static_renaming("__perror_409", "perror");
__static_renaming("__sys_nerr_410", "sys_nerr");
__static_renaming("__sys_errlist_411", "sys_errlist");
__static_renaming("__fileno_413", "fileno");
__static_renaming("__fileno_unlocked_415", "fileno_unlocked");
__static_renaming("__popen_418", "popen");
__static_renaming("__pclose_420", "pclose");
__static_renaming("__ctermid_422", "ctermid");
__static_renaming("__flockfile_424", "flockfile");
__static_renaming("__ftrylockfile_426", "ftrylockfile");
__static_renaming("__funlockfile_428", "funlockfile");
__static_renaming("__main_431", "main");


};
typedef long int  __ptrdiff_t_0;// L143:L324
typedef long unsigned int  __size_t_1;// L177:L209
typedef unsigned char  ____u_char_2;// L30
typedef unsigned short int  ____u_short_3;// L31
typedef unsigned int  ____u_int_4;// L32
typedef unsigned long int  ____u_long_5;// L33
typedef signed char  ____int8_t_6;// L36
typedef unsigned char  ____uint8_t_7;// L37
typedef signed short int  ____int16_t_8;// L38
typedef unsigned short int  ____uint16_t_9;// L39
typedef signed int  ____int32_t_10;// L40
typedef unsigned int  ____uint32_t_11;// L41
typedef signed long int  ____int64_t_12;// L43
typedef unsigned long int  ____uint64_t_13;// L44
typedef long int  ____quad_t_14;// L52
typedef unsigned long int  ____u_quad_t_15;// L53
typedef unsigned long int  ____dev_t_16;// L109:L124
typedef unsigned int  ____uid_t_17;// L92:L125
typedef unsigned int  ____gid_t_18;// L92:L126
typedef unsigned long int  ____ino_t_19;// L94:L127
typedef unsigned long int  ____ino64_t_20;// L109:L128
typedef unsigned int  ____mode_t_21;// L92:L129
typedef unsigned long int  ____nlink_t_22;// L94:L130
typedef long int  ____off_t_23;// L93:L131
typedef long int  ____off64_t_24;// L108:L132
typedef int  ____pid_t_25;// L91:L133
struct ____anonymous_tag_26_27 {
int  ____val_28[2];// L72
};
typedef struct ____anonymous_tag_26_27  ____fsid_t_29;// L72:L134
typedef long int  ____clock_t_30;// L93:L135
typedef unsigned long int  ____rlim_t_31;// L94:L136
typedef unsigned long int  ____rlim64_t_32;// L109:L137
typedef unsigned int  ____id_t_33;// L92:L138
typedef long int  ____time_t_34;// L93:L139
typedef unsigned int  ____useconds_t_35;// L92:L140
typedef long int  ____suseconds_t_36;// L93:L141
typedef int  ____daddr_t_37;// L91:L143
typedef int  ____key_t_38;// L91:L144
typedef int  ____clockid_t_39;// L91:L147
typedef void  * (____timer_t_40);// L70:L150
typedef long int  ____blksize_t_41;// L93:L153
typedef long int  ____blkcnt_t_42;// L93:L158
typedef long int  ____blkcnt64_t_43;// L108:L159
typedef unsigned long int  ____fsblkcnt_t_44;// L94:L162
typedef unsigned long int  ____fsblkcnt64_t_45;// L109:L163
typedef unsigned long int  ____fsfilcnt_t_46;// L94:L166
typedef unsigned long int  ____fsfilcnt64_t_47;// L109:L167
typedef long int  ____fsword_t_48;// L93:L170
typedef long int  ____ssize_t_49;// L110:L172
typedef long int  ____syscall_slong_t_50;// L93:L175
typedef unsigned long int  ____syscall_ulong_t_51;// L94:L177
typedef ____off64_t_24  ____loff_t_52;// L181
typedef ____quad_t_14  * (____qaddr_t_53);// L182
typedef char  * (____caddr_t_54);// L183
typedef long int  ____intptr_t_55;// L110:L186
typedef unsigned int  ____socklen_t_56;// L92:L189
typedef struct __forward_tag_reference_57  __FILE_58;// L48
typedef struct __forward_tag_reference_57  ____FILE_59;// L64
union ____anonymous_tag_60_61 {
unsigned int  ____wch_62;// L265
char  ____wchb_63[4];// L92
};
struct ____anonymous_tag_64_65 {
int  ____count_66;// L84
union ____anonymous_tag_60_61  ____value_67;// L85
};
typedef struct ____anonymous_tag_64_65  ____mbstate_t_68;// L82:L94
typedef struct ____anonymous_tag_64_65  ____mbstate_t_69;// L82:L94
struct ____anonymous_tag_70_71 {
____off_t_23  ____pos_72;// L0
____mbstate_t_68  ____state_73;// L0
____mbstate_t_69  ____state_74;// L0
};
typedef struct ____anonymous_tag_70_71  ___G_fpos_t_75;// L21:L25
struct ____anonymous_tag_76_77 {
____off64_t_24  ____pos_78;// L0
____mbstate_t_68  ____state_79;// L0
____mbstate_t_69  ____state_80;// L0
};
typedef struct ____anonymous_tag_76_77  ___G_fpos64_t_81;// L26:L30
typedef __builtin_va_list  ____gnuc_va_list_82;// L40
typedef void  ___IO_lock_t_84;// L150
struct ___IO_marker_86 {
struct __forward_tag_reference_85  * (___next_87);// L0
struct __forward_tag_reference_57  * (___sbuf_88);// L0
int  ___pos_89;// L162
};
enum ____codecvt_result_94 {
____codecvt_ok_90,
____codecvt_partial_91,
____codecvt_error_92,
____codecvt_noconv_93,
};
struct ___IO_FILE_95 {
int  ___flags_96;// L242
char  * (___IO_read_ptr_97);// L247
char  * (___IO_read_end_98);// L248
char  * (___IO_read_base_99);// L249
char  * (___IO_write_base_100);// L250
char  * (___IO_write_ptr_101);// L251
char  * (___IO_write_end_102);// L252
char  * (___IO_buf_base_103);// L253
char  * (___IO_buf_end_104);// L254
char  * (___IO_save_base_105);// L256
char  * (___IO_backup_base_106);// L257
char  * (___IO_save_end_107);// L258
struct ___IO_marker_86  * (___markers_108);// L260
struct __forward_tag_reference_57  * (___chain_109);// L0
int  ___fileno_110;// L264
int  ___flags2_111;// L268
____off_t_23  ___old_offset_112;// L0
unsigned short  ___cur_column_113;// L274
signed char  ___vtable_offset_114;// L275
char  ___shortbuf_115[1];// L276
___IO_lock_t_84  * (___lock_116);// L0
____off64_t_24  ___offset_117;// L0
void  * (____pad1_118);// L297
void  * (____pad2_119);// L298
void  * (____pad3_120);// L299
void  * (____pad4_121);// L300
__size_t_1  ____pad5_122;// L0
int  ___mode_123;// L303
char  ___unused2_124[15 * sizeof(int) - 4 * sizeof(void*) - sizeof(unsigned long)];// L305
};
typedef struct ___IO_FILE_95  ___IO_FILE_125;// L310
typedef ____ssize_t_49  (____io_read_fn_133) (void  * (____cookie_130), char  * (____buf_131), __size_t_1  ____nbytes_132);// L333
typedef ____ssize_t_49  (____io_write_fn_137) (void  * (____cookie_134), const char  * (____buf_135), __size_t_1  ____n_136);// L341:L342
typedef int  (____io_seek_fn_141) (void  * (____cookie_138), ____off64_t_24  * (____pos_139), int  ____w_140);// L350
typedef int  (____io_close_fn_143) (void  * (____cookie_142));// L353
typedef ____gnuc_va_list_82  __va_list_168;// L79
typedef ____off_t_23  __off_t_169;// L90
typedef ____ssize_t_49  __ssize_t_170;// L102
typedef ___G_fpos_t_75  __fpos_t_171;// L110
extern const char  * const  __sys_errlist_411[];// L27

struct __forward_tag_reference_126 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_57 { // generated union of struct variations
union {
struct ___IO_FILE_95 ___IO_FILE_95;
};
};

struct __forward_tag_reference_85 { // generated union of struct variations
union {
struct ___IO_marker_86 ___IO_marker_86;
};
};

struct __forward_tag_reference_83 { // generated union of struct variations
union {
};
};

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __forward_tag_reference_57 ;// L0
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __forward_tag_reference_83 ;// L0
struct __forward_tag_reference_57 ;// L0
// typedef moved to top of scope
struct ___IO_marker_86 ;// L156
enum ____codecvt_result_94 ;// L176
struct ___IO_FILE_95 ;// L241
// typedef moved to top of scope
struct __forward_tag_reference_126 ;// L0
extern struct __forward_tag_reference_126  ___IO_2_1_stdin__127;// L315
extern struct __forward_tag_reference_126  ___IO_2_1_stdout__128;// L316
extern struct __forward_tag_reference_126  ___IO_2_1_stderr__129;// L317
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (____underflow_144) (___IO_FILE_125  *);// L385
extern int  (____uflow_145) (___IO_FILE_125  *);// L386
extern int  (____overflow_146) (___IO_FILE_125  *, int  );// L387
extern int  (___IO_getc_148) (___IO_FILE_125  * (____fp_147));// L429
extern int  (___IO_putc_151) (int  ____c_149, ___IO_FILE_125  * (____fp_150));// L430
extern int  (___IO_feof_153) (___IO_FILE_125  * (____fp_152));// L431
extern int  (___IO_ferror_155) (___IO_FILE_125  * (____fp_154));// L432
extern int  (___IO_peekc_locked_157) (___IO_FILE_125  * (____fp_156));// L434
extern void  (___IO_flockfile_158) (___IO_FILE_125  *);// L440
extern void  (___IO_funlockfile_159) (___IO_FILE_125  *);// L441
extern int  (___IO_ftrylockfile_160) (___IO_FILE_125  *);// L442
extern int  (___IO_vfscanf_161) (___IO_FILE_125  * __restrict , const char  * __restrict , ____gnuc_va_list_82  , int  * __restrict );// L459:L460
extern int  (___IO_vfprintf_162) (___IO_FILE_125  * __restrict , const char  * __restrict , ____gnuc_va_list_82  );// L461:L462
extern ____ssize_t_49  (___IO_padn_163) (___IO_FILE_125  *, int  , ____ssize_t_49  );// L463
extern __size_t_1  (___IO_sgetn_164) (___IO_FILE_125  *, void  *, __size_t_1  );// L464
extern ____off64_t_24  (___IO_seekoff_165) (___IO_FILE_125  *, ____off64_t_24  , int  , int  );// L466
extern ____off64_t_24  (___IO_seekpos_166) (___IO_FILE_125  *, ____off64_t_24  , int  );// L467
extern void  (___IO_free_backup_area_167) (___IO_FILE_125  *);// L469
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern struct ___IO_FILE_95  * (__stdin_172);// L168
extern struct ___IO_FILE_95  * (__stdout_173);// L169
extern struct ___IO_FILE_95  * (__stderr_174);// L170
extern int  (__remove_176) (const char  * (____filename_175));// L178
extern int  (__rename_179) (const char  * (____old_177), const char  * (____new_178));// L180
extern int  (__renameat_184) (int  ____oldfd_180, const char  * (____old_181), int  ____newfd_182, const char  * (____new_183));// L185:L186
extern __FILE_58  * ((__tmpfile_185) (void  ));// L195
extern char  * ((__tmpnam_187) (char  * (____s_186)));// L209
extern char  * ((__tmpnam_r_189) (char  * (____s_188)));// L215
extern char  * ((__tempnam_192) (const char  * (____dir_190), const char  * (____pfx_191)));// L227:L228
extern int  (__fclose_194) (__FILE_58  * (____stream_193));// L237
extern int  (__fflush_196) (__FILE_58  * (____stream_195));// L242
extern int  (__fflush_unlocked_198) (__FILE_58  * (____stream_197));// L252
extern __FILE_58  * ((__fopen_201) (const char  * __restrict  ____filename_199, const char  * __restrict  ____modes_200));// L272:L273
extern __FILE_58  * ((__freopen_205) (const char  * __restrict  ____filename_202, const char  * __restrict  ____modes_203, __FILE_58  * __restrict  ____stream_204));// L278:L280
extern __FILE_58  * ((__fdopen_208) (int  ____fd_206, const char  * (____modes_207)));// L306
extern __FILE_58  * ((__fmemopen_212) (void  * (____s_209), __size_t_1  ____len_210, const char  * (____modes_211)));// L319:L320
extern __FILE_58  * ((__open_memstream_215) (char  * (* (____bufloc_213)), __size_t_1  * (____sizeloc_214)));// L325
extern void  (__setbuf_218) (__FILE_58  * __restrict  ____stream_216, char  * __restrict  ____buf_217);// L332
extern int  (__setvbuf_223) (__FILE_58  * __restrict  ____stream_219, char  * __restrict  ____buf_220, int  ____modes_221, __size_t_1  ____n_222);// L336:L337
extern void  (__setbuffer_227) (__FILE_58  * __restrict  ____stream_224, char  * __restrict  ____buf_225, __size_t_1  ____size_226);// L343:L344
extern void  (__setlinebuf_229) (__FILE_58  * (____stream_228));// L347
extern int  (__fprintf_232) (__FILE_58  * __restrict  ____stream_230, const char  * __restrict  ____format_231,  ... );// L356:L357
extern int  (__printf_234) (const char  * __restrict  ____format_233,  ... );// L362
extern int  (__sprintf_237) (char  * __restrict  ____s_235, const char  * __restrict  ____format_236,  ... );// L364:L365
extern int  (__vfprintf_241) (__FILE_58  * __restrict  ____s_238, const char  * __restrict  ____format_239, ____gnuc_va_list_82  ____arg_240);// L371:L372
extern int  (__vprintf_244) (const char  * __restrict  ____format_242, ____gnuc_va_list_82  ____arg_243);// L377
extern int  (__vsprintf_248) (char  * __restrict  ____s_245, const char  * __restrict  ____format_246, ____gnuc_va_list_82  ____arg_247);// L379:L380
extern int  (__snprintf_252) (char  * __restrict  ____s_249, __size_t_1  ____maxlen_250, const char  * __restrict  ____format_251,  ... );// L386:L388
extern int  (__vsnprintf_257) (char  * __restrict  ____s_253, __size_t_1  ____maxlen_254, const char  * __restrict  ____format_255, ____gnuc_va_list_82  ____arg_256);// L390:L392
extern int  (__vdprintf_261) (int  ____fd_258, const char  * __restrict  ____fmt_259, ____gnuc_va_list_82  ____arg_260);// L412:L414
extern int  (__dprintf_264) (int  ____fd_262, const char  * __restrict  ____fmt_263,  ... );// L415:L416
extern int  (__fscanf_267) (__FILE_58  * __restrict  ____stream_265, const char  * __restrict  ____format_266,  ... );// L425:L426
extern int  (__scanf_269) (const char  * __restrict  ____format_268,  ... );// L431
extern int  (__sscanf_272) (const char  * __restrict  ____s_270, const char  * __restrict  ____format_271,  ... );// L433:L434



extern int  (__vfscanf_284) (__FILE_58  * __restrict  ____s_281, const char  * __restrict  ____format_282, ____gnuc_va_list_82  ____arg_283);// L471:L473
extern int  (__vscanf_287) (const char  * __restrict  ____format_285, ____gnuc_va_list_82  ____arg_286);// L479:L480
extern int  (__vsscanf_291) (const char  * __restrict  ____s_288, const char  * __restrict  ____format_289, ____gnuc_va_list_82  ____arg_290);// L483:L485



extern int  (__fgetc_304) (__FILE_58  * (____stream_303));// L531
extern int  (__getc_306) (__FILE_58  * (____stream_305));// L532
extern int  (__getchar_307) (void  );// L538
extern int  (__getc_unlocked_309) (__FILE_58  * (____stream_308));// L550
extern int  (__getchar_unlocked_310) (void  );// L551
extern int  (__fgetc_unlocked_312) (__FILE_58  * (____stream_311));// L561
extern int  (__fputc_315) (int  ____c_313, __FILE_58  * (____stream_314));// L573
extern int  (__putc_318) (int  ____c_316, __FILE_58  * (____stream_317));// L574
extern int  (__putchar_320) (int  ____c_319);// L580
extern int  (__fputc_unlocked_323) (int  ____c_321, __FILE_58  * (____stream_322));// L594
extern int  (__putc_unlocked_326) (int  ____c_324, __FILE_58  * (____stream_325));// L602
extern int  (__putchar_unlocked_328) (int  ____c_327);// L603
extern int  (__getw_330) (__FILE_58  * (____stream_329));// L610
extern int  (__putw_333) (int  ____w_331, __FILE_58  * (____stream_332));// L613
extern char  * ((__fgets_337) (char  * __restrict  ____s_334, int  ____n_335, __FILE_58  * __restrict  ____stream_336));// L622:L623
extern ____ssize_t_49  (____getdelim_342) (char  * (* __restrict  ____lineptr_338), __size_t_1  * __restrict  ____n_339, int  ____delimiter_340, __FILE_58  * __restrict  ____stream_341);// L665:L667
extern ____ssize_t_49  (__getdelim_347) (char  * (* __restrict  ____lineptr_343), __size_t_1  * __restrict  ____n_344, int  ____delimiter_345, __FILE_58  * __restrict  ____stream_346);// L668:L670
extern ____ssize_t_49  (__getline_351) (char  * (* __restrict  ____lineptr_348), __size_t_1  * __restrict  ____n_349, __FILE_58  * __restrict  ____stream_350);// L678:L680
extern int  (__fputs_354) (const char  * __restrict  ____s_352, __FILE_58  * __restrict  ____stream_353);// L689
extern int  (__puts_356) (const char  * (____s_355));// L695
extern int  (__ungetc_359) (int  ____c_357, __FILE_58  * (____stream_358));// L702
extern int  (__fseek_379) (__FILE_58  * (____stream_376), long int  ____off_377, int  ____whence_378);// L749
extern long int  (__ftell_381) (__FILE_58  * (____stream_380));// L754
extern void  (__rewind_383) (__FILE_58  * (____stream_382));// L759
extern int  (__fseeko_387) (__FILE_58  * (____stream_384), ____off_t_23  ____off_385, int  ____whence_386);// L773
extern ____off_t_23  (__ftello_389) (__FILE_58  * (____stream_388));// L778
extern int  (__fgetpos_392) (__FILE_58  * __restrict  ____stream_390, __fpos_t_171  * __restrict  ____pos_391);// L798
extern int  (__fsetpos_395) (__FILE_58  * (____stream_393), const __fpos_t_171  * (____pos_394));// L803
extern void  (__clearerr_397) (__FILE_58  * (____stream_396));// L826
extern int  (__feof_399) (__FILE_58  * (____stream_398));// L828
extern int  (__ferror_401) (__FILE_58  * (____stream_400));// L830
extern void  (__clearerr_unlocked_403) (__FILE_58  * (____stream_402));// L835
extern int  (__feof_unlocked_405) (__FILE_58  * (____stream_404));// L836
extern int  (__ferror_unlocked_407) (__FILE_58  * (____stream_406));// L837
extern void  (__perror_409) (const char  * (____s_408));// L846
extern int  __sys_nerr_410;// L26

extern int  (__fileno_413) (__FILE_58  * (____stream_412));// L858
extern int  (__fileno_unlocked_415) (__FILE_58  * (____stream_414));// L863
extern __FILE_58  * ((__popen_418) (const char  * (____command_416), const char  * (____modes_417)));// L872
extern int  (__pclose_420) (__FILE_58  * (____stream_419));// L878
extern char  * ((__ctermid_422) (char  * (____s_421)));// L884
extern void  (__flockfile_424) (__FILE_58  * (____stream_423));// L912
extern int  (__ftrylockfile_426) (__FILE_58  * (____stream_425));// L916
extern void  (__funlockfile_428) (__FILE_58  * (____stream_427));// L919
int  (__main_431) (int  __argc_429, char  * (* (__argv_430))) {

{
{



__static_type_error("type error : no valid expression"); // L23
return 0 ;// L24
}
}


}

