#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__size_t_0", "size_t");
__static_renaming("____u_char_1", "__u_char");
__static_renaming("____u_short_2", "__u_short");
__static_renaming("____u_int_3", "__u_int");
__static_renaming("____u_long_4", "__u_long");
__static_renaming("____int8_t_5", "__int8_t");
__static_renaming("____uint8_t_6", "__uint8_t");
__static_renaming("____int16_t_7", "__int16_t");
__static_renaming("____uint16_t_8", "__uint16_t");
__static_renaming("____int32_t_9", "__int32_t");
__static_renaming("____uint32_t_10", "__uint32_t");
__static_renaming("____int64_t_11", "__int64_t");
__static_renaming("____uint64_t_12", "__uint64_t");
__static_renaming("____quad_t_13", "__quad_t");
__static_renaming("____u_quad_t_14", "__u_quad_t");
__static_renaming("____intmax_t_15", "__intmax_t");
__static_renaming("____uintmax_t_16", "__uintmax_t");
__static_renaming("____dev_t_17", "__dev_t");
__static_renaming("____uid_t_18", "__uid_t");
__static_renaming("____gid_t_19", "__gid_t");
__static_renaming("____ino_t_20", "__ino_t");
__static_renaming("____ino64_t_21", "__ino64_t");
__static_renaming("____mode_t_22", "__mode_t");
__static_renaming("____nlink_t_23", "__nlink_t");
__static_renaming("____off_t_24", "__off_t");
__static_renaming("____off64_t_25", "__off64_t");
__static_renaming("____pid_t_26", "__pid_t");
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
__static_renaming("____caddr_t_53", "__caddr_t");
__static_renaming("____intptr_t_54", "__intptr_t");
__static_renaming("____socklen_t_55", "__socklen_t");
__static_renaming("____sig_atomic_t_56", "__sig_atomic_t");
__static_renaming("____FILE_58", "__FILE");
__static_renaming("__FILE_59", "FILE");
__static_renaming("____mbstate_t_66", "__mbstate_t");
__static_renaming("___G_fpos_t_70", "_G_fpos_t");
__static_renaming("___G_fpos64_t_74", "_G_fpos64_t");
__static_renaming("____gnuc_va_list_75", "__gnuc_va_list");
__static_renaming("___IO_lock_t_77", "_IO_lock_t");
__static_renaming("___IO_FILE_117", "_IO_FILE");
__static_renaming("___IO_2_1_stdin__119", "_IO_2_1_stdin_");
__static_renaming("___IO_2_1_stdout__120", "_IO_2_1_stdout_");
__static_renaming("___IO_2_1_stderr__121", "_IO_2_1_stderr_");
__static_renaming("____io_read_fn_125", "__io_read_fn");
__static_renaming("____io_write_fn_129", "__io_write_fn");
__static_renaming("____io_seek_fn_133", "__io_seek_fn");
__static_renaming("____io_close_fn_135", "__io_close_fn");
__static_renaming("____underflow_136", "__underflow");
__static_renaming("____uflow_137", "__uflow");
__static_renaming("____overflow_138", "__overflow");
__static_renaming("___IO_getc_140", "_IO_getc");
__static_renaming("___IO_putc_143", "_IO_putc");
__static_renaming("___IO_feof_145", "_IO_feof");
__static_renaming("___IO_ferror_147", "_IO_ferror");
__static_renaming("___IO_peekc_locked_149", "_IO_peekc_locked");
__static_renaming("___IO_flockfile_150", "_IO_flockfile");
__static_renaming("___IO_funlockfile_151", "_IO_funlockfile");
__static_renaming("___IO_ftrylockfile_152", "_IO_ftrylockfile");
__static_renaming("___IO_vfscanf_153", "_IO_vfscanf");
__static_renaming("___IO_vfprintf_154", "_IO_vfprintf");
__static_renaming("___IO_padn_155", "_IO_padn");
__static_renaming("___IO_seekoff_156", "_IO_seekoff");
__static_renaming("___IO_seekpos_157", "_IO_seekpos");
__static_renaming("___IO_free_backup_area_158", "_IO_free_backup_area");
__static_renaming("__va_list_159", "va_list");
__static_renaming("__off_t_160", "off_t");
__static_renaming("__ssize_t_161", "ssize_t");
__static_renaming("__fpos_t_162", "fpos_t");
__static_renaming("__stdin_163", "stdin");
__static_renaming("__stdout_164", "stdout");
__static_renaming("__stderr_165", "stderr");
__static_renaming("__remove_167", "remove");
__static_renaming("__rename_170", "rename");
__static_renaming("__renameat_175", "renameat");
__static_renaming("__tmpfile_176", "tmpfile");
__static_renaming("__tmpnam_178", "tmpnam");
__static_renaming("__tmpnam_r_180", "tmpnam_r");
__static_renaming("__tempnam_183", "tempnam");
__static_renaming("__fclose_185", "fclose");
__static_renaming("__fflush_187", "fflush");
__static_renaming("__fflush_unlocked_189", "fflush_unlocked");
__static_renaming("__fopen_192", "fopen");
__static_renaming("__freopen_196", "freopen");
__static_renaming("__fdopen_199", "fdopen");
__static_renaming("__fmemopen_203", "fmemopen");
__static_renaming("__open_memstream_206", "open_memstream");
__static_renaming("__setbuf_209", "setbuf");
__static_renaming("__setvbuf_214", "setvbuf");
__static_renaming("__setbuffer_218", "setbuffer");
__static_renaming("__setlinebuf_220", "setlinebuf");
__static_renaming("__fprintf_223", "fprintf");
__static_renaming("__printf_225", "printf");
__static_renaming("__sprintf_228", "sprintf");
__static_renaming("__vfprintf_232", "vfprintf");
__static_renaming("__vprintf_235", "vprintf");
__static_renaming("__vsprintf_239", "vsprintf");
__static_renaming("__snprintf_243", "snprintf");
__static_renaming("__vsnprintf_248", "vsnprintf");
__static_renaming("__vdprintf_252", "vdprintf");
__static_renaming("__dprintf_255", "dprintf");
__static_renaming("__fscanf_258", "fscanf");
__static_renaming("__scanf_260", "scanf");
__static_renaming("__sscanf_263", "sscanf");
__static_renaming("__vfscanf_275", "vfscanf");
__static_renaming("__vscanf_278", "vscanf");
__static_renaming("__vsscanf_282", "vsscanf");
__static_renaming("__fgetc_295", "fgetc");
__static_renaming("__getc_297", "getc");
__static_renaming("__getchar_298", "getchar");
__static_renaming("__getc_unlocked_300", "getc_unlocked");
__static_renaming("__getchar_unlocked_301", "getchar_unlocked");
__static_renaming("__fgetc_unlocked_303", "fgetc_unlocked");
__static_renaming("__fputc_306", "fputc");
__static_renaming("__putc_309", "putc");
__static_renaming("__putchar_311", "putchar");
__static_renaming("__fputc_unlocked_314", "fputc_unlocked");
__static_renaming("__putc_unlocked_317", "putc_unlocked");
__static_renaming("__putchar_unlocked_319", "putchar_unlocked");
__static_renaming("__getw_321", "getw");
__static_renaming("__putw_324", "putw");
__static_renaming("__fgets_328", "fgets");
__static_renaming("____getdelim_333", "__getdelim");
__static_renaming("__getdelim_338", "getdelim");
__static_renaming("__getline_342", "getline");
__static_renaming("__fputs_345", "fputs");
__static_renaming("__puts_347", "puts");
__static_renaming("__ungetc_350", "ungetc");
__static_renaming("__fseek_370", "fseek");
__static_renaming("__ftell_372", "ftell");
__static_renaming("__rewind_374", "rewind");
__static_renaming("__fseeko_378", "fseeko");
__static_renaming("__ftello_380", "ftello");
__static_renaming("__fgetpos_383", "fgetpos");
__static_renaming("__fsetpos_386", "fsetpos");
__static_renaming("__clearerr_388", "clearerr");
__static_renaming("__feof_390", "feof");
__static_renaming("__ferror_392", "ferror");
__static_renaming("__clearerr_unlocked_394", "clearerr_unlocked");
__static_renaming("__feof_unlocked_396", "feof_unlocked");
__static_renaming("__ferror_unlocked_398", "ferror_unlocked");
__static_renaming("__perror_400", "perror");
__static_renaming("__sys_nerr_401", "sys_nerr");
__static_renaming("__sys_errlist_402", "sys_errlist");
__static_renaming("__fileno_404", "fileno");
__static_renaming("__fileno_unlocked_406", "fileno_unlocked");
__static_renaming("__popen_409", "popen");
__static_renaming("__pclose_411", "pclose");
__static_renaming("__ctermid_413", "ctermid");
__static_renaming("__flockfile_415", "flockfile");
__static_renaming("__ftrylockfile_417", "ftrylockfile");
__static_renaming("__funlockfile_419", "funlockfile");
__static_renaming("__decode_spi_frequency_425", "decode_spi_frequency");


};
enum __codecvt_result {
____codecvt_ok_83,
____codecvt_partial_84,
____codecvt_error_85,
____codecvt_noconv_86,
};
enum __anonymous_tag_423 {
__SPI_FREQUENCY_20MHZ_420,
__SPI_FREQUENCY_33MHZ_421,
__SPI_FREQUENCY_50MHZ_422,
};
typedef long unsigned int  __size_t_0;
typedef unsigned char  ____u_char_1;
typedef unsigned short int  ____u_short_2;
typedef unsigned int  ____u_int_3;
typedef unsigned long int  ____u_long_4;
typedef signed char  ____int8_t_5;
typedef unsigned char  ____uint8_t_6;
typedef signed short int  ____int16_t_7;
typedef unsigned short int  ____uint16_t_8;
typedef signed int  ____int32_t_9;
typedef unsigned int  ____uint32_t_10;
typedef signed long int  ____int64_t_11;
typedef unsigned long int  ____uint64_t_12;
typedef long int  ____quad_t_13;
typedef unsigned long int  ____u_quad_t_14;
typedef long int  ____intmax_t_15;
typedef unsigned long int  ____uintmax_t_16;
typedef unsigned long int  ____dev_t_17;
typedef unsigned int  ____uid_t_18;
typedef unsigned int  ____gid_t_19;
typedef unsigned long int  ____ino_t_20;
typedef unsigned long int  ____ino64_t_21;
typedef unsigned int  ____mode_t_22;
typedef unsigned long int  ____nlink_t_23;
typedef long int  ____off_t_24;
typedef long int  ____off64_t_25;
typedef int  ____pid_t_26;
struct __anonymous_tag_27 {
int  (____val_28[2]);
};
typedef struct __anonymous_tag_27  ____fsid_t_29;
typedef long int  ____clock_t_30;
typedef unsigned long int  ____rlim_t_31;
typedef unsigned long int  ____rlim64_t_32;
typedef unsigned int  ____id_t_33;
typedef long int  ____time_t_34;
typedef unsigned int  ____useconds_t_35;
typedef long int  ____suseconds_t_36;
typedef int  ____daddr_t_37;
typedef int  ____key_t_38;
typedef int  ____clockid_t_39;
typedef void  (* ____timer_t_40);
typedef long int  ____blksize_t_41;
typedef long int  ____blkcnt_t_42;
typedef long int  ____blkcnt64_t_43;
typedef unsigned long int  ____fsblkcnt_t_44;
typedef unsigned long int  ____fsblkcnt64_t_45;
typedef unsigned long int  ____fsfilcnt_t_46;
typedef unsigned long int  ____fsfilcnt64_t_47;
typedef long int  ____fsword_t_48;
typedef long int  ____ssize_t_49;
typedef long int  ____syscall_slong_t_50;
typedef unsigned long int  ____syscall_ulong_t_51;
typedef ____off64_t_25  ____loff_t_52;
typedef char  (* ____caddr_t_53);
typedef long int  ____intptr_t_54;
typedef unsigned int  ____socklen_t_55;
typedef int  ____sig_atomic_t_56;
typedef struct __forward_tag_reference_57  ____FILE_58;
typedef struct __forward_tag_reference_57  __FILE_59;
union __anonymous_tag_60 {
unsigned int  ____wch_61;
char  (____wchb_62[4]);
};
struct __anonymous_tag_63 {
int  ____count_64;
union __anonymous_tag_60  ____value_65;
};
typedef struct __anonymous_tag_63  ____mbstate_t_66;
struct __anonymous_tag_67 {
____off_t_24  ____pos_68;
____mbstate_t_66  ____state_69;
};
typedef struct __anonymous_tag_67  ___G_fpos_t_70;
struct __anonymous_tag_71 {
____off64_t_25  ____pos_72;
____mbstate_t_66  ____state_73;
};
typedef struct __anonymous_tag_71  ___G_fpos64_t_74;
typedef __builtin_va_list  ____gnuc_va_list_75;
typedef void  ___IO_lock_t_77;
struct ___IO_marker_79 {
struct __forward_tag_reference_78  (* ___next_80);
struct __forward_tag_reference_57  (* ___sbuf_81);
int  ___pos_82;
};
struct ___IO_FILE_87 {
int  ___flags_88;
char  (* ___IO_read_ptr_89);
char  (* ___IO_read_end_90);
char  (* ___IO_read_base_91);
char  (* ___IO_write_base_92);
char  (* ___IO_write_ptr_93);
char  (* ___IO_write_end_94);
char  (* ___IO_buf_base_95);
char  (* ___IO_buf_end_96);
char  (* ___IO_save_base_97);
char  (* ___IO_backup_base_98);
char  (* ___IO_save_end_99);
struct ___IO_marker_79  (* ___markers_100);
struct __forward_tag_reference_57  (* ___chain_101);
int  ___fileno_102;
int  ___flags2_103;
____off_t_24  ___old_offset_104;
unsigned short  ___cur_column_105;
signed char  ___vtable_offset_106;
char  (___shortbuf_107[1]);
___IO_lock_t_77  (* ___lock_108);
____off64_t_25  ___offset_109;
void  (* ____pad1_110);
void  (* ____pad2_111);
void  (* ____pad3_112);
void  (* ____pad4_113);
__size_t_0  ____pad5_114;
int  ___mode_115;
char  (___unused2_116[__static_type_error("no valid type found in expression")]);
};
typedef struct ___IO_FILE_87  ___IO_FILE_117;
typedef ____ssize_t_49  ____io_read_fn_125 (void  (* ____cookie_122), char  (* ____buf_123), __size_t_0  ____nbytes_124);
typedef ____ssize_t_49  ____io_write_fn_129 (void  (* ____cookie_126), const char  (* ____buf_127), __size_t_0  ____n_128);
typedef int  ____io_seek_fn_133 (void  (* ____cookie_130), ____off64_t_25  (* ____pos_131), int  ____w_132);
typedef int  ____io_close_fn_135 (void  (* ____cookie_134));
typedef ____gnuc_va_list_75  __va_list_159;
typedef ____off_t_24  __off_t_160;
typedef ____ssize_t_49  __ssize_t_161;
typedef ___G_fpos_t_70  __fpos_t_162;

struct __forward_tag_reference_78 { // generated union of struct variations
union {
struct ___IO_marker_79 ___IO_marker_79;
};
};

struct __forward_tag_reference_57 { // generated union of struct variations
union {
struct ___IO_FILE_87 ___IO_FILE_87;
};
};

struct __forward_tag_reference_76 { // generated union of struct variations
union {
};
};

struct __forward_tag_reference_118 { // generated union of struct variations
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
// typedef moved to top of scope
struct __forward_tag_reference_57 ;
// typedef moved to top of scope
struct __forward_tag_reference_57 ;
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __forward_tag_reference_76 ;
struct __forward_tag_reference_57 ;
// typedef moved to top of scope
struct ___IO_marker_79 ;
enum __codecvt_result ;
struct ___IO_FILE_87 ;
// typedef moved to top of scope
struct __forward_tag_reference_118 ;
extern struct __forward_tag_reference_118  ___IO_2_1_stdin__119;
extern struct __forward_tag_reference_118  ___IO_2_1_stdout__120;
extern struct __forward_tag_reference_118  ___IO_2_1_stderr__121;
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  ____underflow_136 (___IO_FILE_117  *);
extern int  ____uflow_137 (___IO_FILE_117  *);
extern int  ____overflow_138 (___IO_FILE_117  *, int  );
extern int  ___IO_getc_140 (___IO_FILE_117  (* ____fp_139));
extern int  ___IO_putc_143 (int  ____c_141, ___IO_FILE_117  (* ____fp_142));
extern int  ___IO_feof_145 (___IO_FILE_117  (* ____fp_144));
extern int  ___IO_ferror_147 (___IO_FILE_117  (* ____fp_146));
extern int  ___IO_peekc_locked_149 (___IO_FILE_117  (* ____fp_148));
extern void  ___IO_flockfile_150 (___IO_FILE_117  *);
extern void  ___IO_funlockfile_151 (___IO_FILE_117  *);
extern int  ___IO_ftrylockfile_152 (___IO_FILE_117  *);
extern int  ___IO_vfscanf_153 (___IO_FILE_117  * __restrict , const char  * __restrict , ____gnuc_va_list_75  , int  * __restrict );
extern int  ___IO_vfprintf_154 (___IO_FILE_117  * __restrict , const char  * __restrict , ____gnuc_va_list_75  );
extern ____ssize_t_49  ___IO_padn_155 (___IO_FILE_117  *, int  , ____ssize_t_49  );
extern ____off64_t_25  ___IO_seekoff_156 (___IO_FILE_117  *, ____off64_t_25  , int  , int  );
extern ____off64_t_25  ___IO_seekpos_157 (___IO_FILE_117  *, ____off64_t_25  , int  );
extern void  ___IO_free_backup_area_158 (___IO_FILE_117  *);
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern struct ___IO_FILE_87  (* __stdin_163);
extern struct ___IO_FILE_87  (* __stdout_164);
extern struct ___IO_FILE_87  (* __stderr_165);
extern int  __remove_167 (const char  (* ____filename_166));
extern int  __rename_170 (const char  (* ____old_168), const char  (* ____new_169));
extern int  __renameat_175 (int  ____oldfd_171, const char  (* ____old_172), int  ____newfd_173, const char  (* ____new_174));
extern __FILE_59  (* __tmpfile_176 (void  ));
extern char  (* __tmpnam_178 (char  (* ____s_177)));
extern char  (* __tmpnam_r_180 (char  (* ____s_179)));
extern char  (* __tempnam_183 (const char  (* ____dir_181), const char  (* ____pfx_182)));
extern int  __fclose_185 (__FILE_59  (* ____stream_184));
extern int  __fflush_187 (__FILE_59  (* ____stream_186));
extern int  __fflush_unlocked_189 (__FILE_59  (* ____stream_188));
extern __FILE_59  (* __fopen_192 (const char  (* __restrict  ____filename_190), const char  (* __restrict  ____modes_191)));
extern __FILE_59  (* __freopen_196 (const char  (* __restrict  ____filename_193), const char  (* __restrict  ____modes_194), __FILE_59  (* __restrict  ____stream_195)));
extern __FILE_59  (* __fdopen_199 (int  ____fd_197, const char  (* ____modes_198)));
extern __FILE_59  (* __fmemopen_203 (void  (* ____s_200), __size_t_0  ____len_201, const char  (* ____modes_202)));
extern __FILE_59  (* __open_memstream_206 (char  (* (* ____bufloc_204)), __size_t_0  (* ____sizeloc_205)));
extern void  __setbuf_209 (__FILE_59  (* __restrict  ____stream_207), char  (* __restrict  ____buf_208));
extern int  __setvbuf_214 (__FILE_59  (* __restrict  ____stream_210), char  (* __restrict  ____buf_211), int  ____modes_212, __size_t_0  ____n_213);
extern void  __setbuffer_218 (__FILE_59  (* __restrict  ____stream_215), char  (* __restrict  ____buf_216), __size_t_0  ____size_217);
extern void  __setlinebuf_220 (__FILE_59  (* ____stream_219));
extern int  __fprintf_223 (__FILE_59  (* __restrict  ____stream_221), const char  (* __restrict  ____format_222),  ... );
extern int  __printf_225 (const char  (* __restrict  ____format_224),  ... );
extern int  __sprintf_228 (char  (* __restrict  ____s_226), const char  (* __restrict  ____format_227),  ... );
extern int  __vfprintf_232 (__FILE_59  (* __restrict  ____s_229), const char  (* __restrict  ____format_230), ____gnuc_va_list_75  ____arg_231);
extern int  __vprintf_235 (const char  (* __restrict  ____format_233), ____gnuc_va_list_75  ____arg_234);
extern int  __vsprintf_239 (char  (* __restrict  ____s_236), const char  (* __restrict  ____format_237), ____gnuc_va_list_75  ____arg_238);
extern int  __snprintf_243 (char  (* __restrict  ____s_240), __size_t_0  ____maxlen_241, const char  (* __restrict  ____format_242),  ... );
extern int  __vsnprintf_248 (char  (* __restrict  ____s_244), __size_t_0  ____maxlen_245, const char  (* __restrict  ____format_246), ____gnuc_va_list_75  ____arg_247);
extern int  __vdprintf_252 (int  ____fd_249, const char  (* __restrict  ____fmt_250), ____gnuc_va_list_75  ____arg_251);
extern int  __dprintf_255 (int  ____fd_253, const char  (* __restrict  ____fmt_254),  ... );
extern int  __fscanf_258 (__FILE_59  (* __restrict  ____stream_256), const char  (* __restrict  ____format_257),  ... );
extern int  __scanf_260 (const char  (* __restrict  ____format_259),  ... );
extern int  __sscanf_263 (const char  (* __restrict  ____s_261), const char  (* __restrict  ____format_262),  ... );



extern int  __vfscanf_275 (__FILE_59  (* __restrict  ____s_272), const char  (* __restrict  ____format_273), ____gnuc_va_list_75  ____arg_274);
extern int  __vscanf_278 (const char  (* __restrict  ____format_276), ____gnuc_va_list_75  ____arg_277);
extern int  __vsscanf_282 (const char  (* __restrict  ____s_279), const char  (* __restrict  ____format_280), ____gnuc_va_list_75  ____arg_281);



extern int  __fgetc_295 (__FILE_59  (* ____stream_294));
extern int  __getc_297 (__FILE_59  (* ____stream_296));
extern int  __getchar_298 (void  );
extern int  __getc_unlocked_300 (__FILE_59  (* ____stream_299));
extern int  __getchar_unlocked_301 (void  );
extern int  __fgetc_unlocked_303 (__FILE_59  (* ____stream_302));
extern int  __fputc_306 (int  ____c_304, __FILE_59  (* ____stream_305));
extern int  __putc_309 (int  ____c_307, __FILE_59  (* ____stream_308));
extern int  __putchar_311 (int  ____c_310);
extern int  __fputc_unlocked_314 (int  ____c_312, __FILE_59  (* ____stream_313));
extern int  __putc_unlocked_317 (int  ____c_315, __FILE_59  (* ____stream_316));
extern int  __putchar_unlocked_319 (int  ____c_318);
extern int  __getw_321 (__FILE_59  (* ____stream_320));
extern int  __putw_324 (int  ____w_322, __FILE_59  (* ____stream_323));
extern char  (* __fgets_328 (char  (* __restrict  ____s_325), int  ____n_326, __FILE_59  (* __restrict  ____stream_327)));
extern ____ssize_t_49  ____getdelim_333 (char  (* (* __restrict  ____lineptr_329)), __size_t_0  (* __restrict  ____n_330), int  ____delimiter_331, __FILE_59  (* __restrict  ____stream_332));
extern ____ssize_t_49  __getdelim_338 (char  (* (* __restrict  ____lineptr_334)), __size_t_0  (* __restrict  ____n_335), int  ____delimiter_336, __FILE_59  (* __restrict  ____stream_337));
extern ____ssize_t_49  __getline_342 (char  (* (* __restrict  ____lineptr_339)), __size_t_0  (* __restrict  ____n_340), __FILE_59  (* __restrict  ____stream_341));
extern int  __fputs_345 (const char  (* __restrict  ____s_343), __FILE_59  (* __restrict  ____stream_344));
extern int  __puts_347 (const char  (* ____s_346));
extern int  __ungetc_350 (int  ____c_348, __FILE_59  (* ____stream_349));
extern int  __fseek_370 (__FILE_59  (* ____stream_367), long int  ____off_368, int  ____whence_369);
extern long int  __ftell_372 (__FILE_59  (* ____stream_371));
extern void  __rewind_374 (__FILE_59  (* ____stream_373));
extern int  __fseeko_378 (__FILE_59  (* ____stream_375), ____off_t_24  ____off_376, int  ____whence_377);
extern ____off_t_24  __ftello_380 (__FILE_59  (* ____stream_379));
extern int  __fgetpos_383 (__FILE_59  (* __restrict  ____stream_381), __fpos_t_162  (* __restrict  ____pos_382));
extern int  __fsetpos_386 (__FILE_59  (* ____stream_384), const __fpos_t_162  (* ____pos_385));
extern void  __clearerr_388 (__FILE_59  (* ____stream_387));
extern int  __feof_390 (__FILE_59  (* ____stream_389));
extern int  __ferror_392 (__FILE_59  (* ____stream_391));
extern void  __clearerr_unlocked_394 (__FILE_59  (* ____stream_393));
extern int  __feof_unlocked_396 (__FILE_59  (* ____stream_395));
extern int  __ferror_unlocked_398 (__FILE_59  (* ____stream_397));
extern void  __perror_400 (const char  (* ____s_399));
extern int  __sys_nerr_401;
extern const char  (* const  (__sys_errlist_402[]));
extern int  __fileno_404 (__FILE_59  (* ____stream_403));
extern int  __fileno_unlocked_406 (__FILE_59  (* ____stream_405));
extern __FILE_59  (* __popen_409 (const char  (* ____command_407), const char  (* ____modes_408)));
extern int  __pclose_411 (__FILE_59  (* ____stream_410));
extern char  (* __ctermid_413 (char  (* ____s_412)));
extern void  __flockfile_415 (__FILE_59  (* ____stream_414));
extern int  __ftrylockfile_417 (__FILE_59  (* ____stream_416));
extern void  __funlockfile_419 (__FILE_59  (* ____stream_418));
enum __anonymous_tag_423 ;
static void  __decode_spi_frequency_425 (unsigned int  __freq_424) {
{
switch (  __freq_424  ) { case  __SPI_FREQUENCY_20MHZ_420  : 
 __printf_225  ( "20MHz" ) ;

break ;


case  __SPI_FREQUENCY_33MHZ_421  : 
 __printf_225  ( "33MHz" ) ;

break ;


case  __SPI_FREQUENCY_50MHZ_422  : 
 __printf_225  ( "50MHz" ) ;

break ;


default : 
 __printf_225  ( "unknown<%x>MHz",  __freq_424  ) ;

 }

}


}

