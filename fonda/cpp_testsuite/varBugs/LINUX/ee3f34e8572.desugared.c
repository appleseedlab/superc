#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_804;
extern const bool __static_condition_default_826;
extern const bool __static_condition_default_821;
extern const bool __static_condition_default_423;
extern const bool __static_condition_default_305;
extern const bool __static_condition_default_595;
extern const bool __static_condition_default_808;
extern const bool __static_condition_default_823;
extern const bool __static_condition_default_420;
extern const bool __static_condition_default_352;
extern const bool __static_condition_default_246;
extern const bool __static_condition_default_288;
extern const bool __static_condition_default_802;
extern const bool __static_condition_default_623;
extern const bool __static_condition_default_827;
extern const bool __static_condition_default_308;
extern const bool __static_condition_default_627;
extern const bool __static_condition_default_629;
extern const bool __static_condition_default_264;
extern const bool __static_condition_default_429;
extern const bool __static_condition_default_234;
extern const bool __static_condition_default_414;
extern const bool __static_condition_default_432;
extern const bool __static_condition_default_267;
extern const bool __static_condition_default_282;
extern const bool __static_condition_default_602;
extern const bool __static_condition_default_379;
extern const bool __static_condition_default_820;
extern const bool __static_condition_default_824;
extern const bool __static_condition_default_302;
extern const bool __static_condition_default_819;
extern const bool __static_condition_default_255;
extern const bool __static_condition_default_604;
extern const bool __static_condition_default_817;
extern const bool __static_condition_default_249;
extern const bool __static_condition_default_296;
extern const bool __static_condition_default_581;
extern const bool __static_condition_default_243;
extern const bool __static_condition_default_276;
extern const bool __static_condition_default_279;
extern const bool __static_condition_default_426;
extern const bool __static_condition_default_273;
extern const bool __static_condition_default_341;
extern const bool __static_condition_default_361;
extern const bool __static_condition_default_594;
extern const bool __static_condition_default_349;
extern const bool __static_condition_default_325;
extern const bool __static_condition_default_237;
extern const bool __static_condition_default_378;
extern const bool __static_condition_default_270;
extern const bool __static_condition_default_285;
extern const bool __static_condition_default_834;
extern const bool __static_condition_default_293;
extern const bool __static_condition_default_822;
extern const bool __static_condition_default_417;
extern const bool __static_condition_default_813;
extern const bool __static_condition_default_803;
extern const bool __static_condition_default_832;
extern const bool __static_condition_default_299;
extern const bool __static_condition_default_258;
extern const bool __static_condition_default_811;
extern const bool __static_condition_default_815;
extern const bool __static_condition_default_736;
extern const bool __static_condition_default_828;
extern const bool __static_condition_default_829;
extern const bool __static_condition_default_833;
extern const bool __static_condition_default_252;
extern const bool __static_condition_default_579;
extern const bool __static_condition_default_818;
extern const bool __static_condition_default_261;
extern const bool __static_condition_default_240;
extern const bool __static_condition_default_394;
extern const bool __static_condition_default_621;
extern const bool __static_condition_default_807;
extern const bool __static_condition_default_67;
extern const bool __static_condition_default_215;
extern const bool __static_condition_default_60;
extern const bool __static_condition_default_395;
extern const bool __static_condition_default_825;
void __static_initializer_default() {
__static_renaming("__ptrdiff_t_0", "ptrdiff_t");
__static_renaming("__size_t_1", "size_t");
__static_renaming("__wchar_t_2", "wchar_t");
__static_renaming("__idtype_t_8", "idtype_t");
__static_renaming("____u_char_9", "__u_char");
__static_renaming("____u_short_10", "__u_short");
__static_renaming("____u_int_11", "__u_int");
__static_renaming("____u_long_12", "__u_long");
__static_renaming("____int8_t_13", "__int8_t");
__static_renaming("____uint8_t_14", "__uint8_t");
__static_renaming("____int16_t_15", "__int16_t");
__static_renaming("____uint16_t_16", "__uint16_t");
__static_renaming("____int32_t_17", "__int32_t");
__static_renaming("____uint32_t_18", "__uint32_t");
__static_renaming("____int64_t_19", "__int64_t");
__static_renaming("____uint64_t_20", "__uint64_t");
__static_renaming("____quad_t_21", "__quad_t");
__static_renaming("____u_quad_t_22", "__u_quad_t");
__static_renaming("____dev_t_23", "__dev_t");
__static_renaming("____uid_t_24", "__uid_t");
__static_renaming("____gid_t_25", "__gid_t");
__static_renaming("____ino_t_26", "__ino_t");
__static_renaming("____ino64_t_27", "__ino64_t");
__static_renaming("____mode_t_28", "__mode_t");
__static_renaming("____nlink_t_29", "__nlink_t");
__static_renaming("____off_t_30", "__off_t");
__static_renaming("____off64_t_31", "__off64_t");
__static_renaming("____pid_t_32", "__pid_t");
__static_renaming("____fsid_t_36", "__fsid_t");
__static_renaming("____clock_t_37", "__clock_t");
__static_renaming("____rlim_t_38", "__rlim_t");
__static_renaming("____rlim64_t_39", "__rlim64_t");
__static_renaming("____id_t_40", "__id_t");
__static_renaming("____time_t_41", "__time_t");
__static_renaming("____useconds_t_42", "__useconds_t");
__static_renaming("____suseconds_t_43", "__suseconds_t");
__static_renaming("____daddr_t_44", "__daddr_t");
__static_renaming("____key_t_45", "__key_t");
__static_renaming("____clockid_t_46", "__clockid_t");
__static_renaming("____timer_t_47", "__timer_t");
__static_renaming("____blksize_t_48", "__blksize_t");
__static_renaming("____blkcnt_t_49", "__blkcnt_t");
__static_renaming("____blkcnt64_t_50", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_51", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_52", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_53", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_54", "__fsfilcnt64_t");
__static_renaming("____fsword_t_55", "__fsword_t");
__static_renaming("____ssize_t_56", "__ssize_t");
__static_renaming("____syscall_slong_t_57", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_58", "__syscall_ulong_t");
__static_renaming("____loff_t_59", "__loff_t");
__static_renaming("____qaddr_t_61", "__qaddr_t");
__static_renaming("____caddr_t_62", "__caddr_t");
__static_renaming("____intptr_t_63", "__intptr_t");
__static_renaming("____socklen_t_64", "__socklen_t");
__static_renaming("____bswap_32_66", "__bswap_32");
__static_renaming("____bswap_64_69", "__bswap_64");
__static_renaming("____WAIT_STATUS_89", "__WAIT_STATUS");
__static_renaming("__div_t_94", "div_t");
__static_renaming("__ldiv_t_99", "ldiv_t");
__static_renaming("__lldiv_t_104", "lldiv_t");
__static_renaming("____ctype_get_mb_cur_max_105", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_106", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_107", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_108", "__ctype_get_mb_cur_max");
__static_renaming("__atof_110", "atof");
__static_renaming("__atof_111", "atof");
__static_renaming("__atoi_113", "atoi");
__static_renaming("__atoi_114", "atoi");
__static_renaming("__atol_116", "atol");
__static_renaming("__atol_117", "atol");
__static_renaming("__atoll_119", "atoll");
__static_renaming("__atoll_120", "atoll");
__static_renaming("__strtod_123", "strtod");
__static_renaming("__strtof_126", "strtof");
__static_renaming("__strtold_129", "strtold");
__static_renaming("__strtol_133", "strtol");
__static_renaming("__strtoul_137", "strtoul");
__static_renaming("__strtoq_141", "strtoq");
__static_renaming("__strtouq_145", "strtouq");
__static_renaming("__strtoll_149", "strtoll");
__static_renaming("__strtoll_150", "strtoll");
__static_renaming("__strtoull_154", "strtoull");
__static_renaming("__l64a_159", "l64a");
__static_renaming("__l64a_160", "l64a");
__static_renaming("__a64l_162", "a64l");
__static_renaming("__a64l_163", "a64l");
__static_renaming("____u_char_164", "__u_char");
__static_renaming("____u_short_165", "__u_short");
__static_renaming("____u_int_166", "__u_int");
__static_renaming("____u_long_167", "__u_long");
__static_renaming("____int8_t_168", "__int8_t");
__static_renaming("____uint8_t_169", "__uint8_t");
__static_renaming("____int16_t_170", "__int16_t");
__static_renaming("____uint16_t_171", "__uint16_t");
__static_renaming("____int32_t_172", "__int32_t");
__static_renaming("____uint32_t_173", "__uint32_t");
__static_renaming("____int64_t_174", "__int64_t");
__static_renaming("____uint64_t_175", "__uint64_t");
__static_renaming("____quad_t_176", "__quad_t");
__static_renaming("____u_quad_t_177", "__u_quad_t");
__static_renaming("____dev_t_178", "__dev_t");
__static_renaming("____uid_t_179", "__uid_t");
__static_renaming("____gid_t_180", "__gid_t");
__static_renaming("____ino_t_181", "__ino_t");
__static_renaming("____ino64_t_182", "__ino64_t");
__static_renaming("____mode_t_183", "__mode_t");
__static_renaming("____nlink_t_184", "__nlink_t");
__static_renaming("____off_t_185", "__off_t");
__static_renaming("____off64_t_186", "__off64_t");
__static_renaming("____pid_t_187", "__pid_t");
__static_renaming("____fsid_t_191", "__fsid_t");
__static_renaming("____clock_t_192", "__clock_t");
__static_renaming("____rlim_t_193", "__rlim_t");
__static_renaming("____rlim64_t_194", "__rlim64_t");
__static_renaming("____id_t_195", "__id_t");
__static_renaming("____time_t_196", "__time_t");
__static_renaming("____useconds_t_197", "__useconds_t");
__static_renaming("____suseconds_t_198", "__suseconds_t");
__static_renaming("____daddr_t_199", "__daddr_t");
__static_renaming("____key_t_200", "__key_t");
__static_renaming("____clockid_t_201", "__clockid_t");
__static_renaming("____timer_t_202", "__timer_t");
__static_renaming("____blksize_t_203", "__blksize_t");
__static_renaming("____blkcnt_t_204", "__blkcnt_t");
__static_renaming("____blkcnt64_t_205", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_206", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_207", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_208", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_209", "__fsfilcnt64_t");
__static_renaming("____fsword_t_210", "__fsword_t");
__static_renaming("____ssize_t_211", "__ssize_t");
__static_renaming("____syscall_slong_t_212", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_213", "__syscall_ulong_t");
__static_renaming("____loff_t_214", "__loff_t");
__static_renaming("____qaddr_t_216", "__qaddr_t");
__static_renaming("____caddr_t_217", "__caddr_t");
__static_renaming("____intptr_t_218", "__intptr_t");
__static_renaming("____socklen_t_219", "__socklen_t");
__static_renaming("__u_char_220", "u_char");
__static_renaming("__u_char_221", "u_char");
__static_renaming("__u_short_222", "u_short");
__static_renaming("__u_short_223", "u_short");
__static_renaming("__u_int_224", "u_int");
__static_renaming("__u_int_225", "u_int");
__static_renaming("__u_long_226", "u_long");
__static_renaming("__u_long_227", "u_long");
__static_renaming("__quad_t_228", "quad_t");
__static_renaming("__quad_t_229", "quad_t");
__static_renaming("__u_quad_t_230", "u_quad_t");
__static_renaming("__u_quad_t_231", "u_quad_t");
__static_renaming("__fsid_t_232", "fsid_t");
__static_renaming("__fsid_t_233", "fsid_t");
__static_renaming("__loff_t_235", "loff_t");
__static_renaming("__loff_t_236", "loff_t");
__static_renaming("__loff_t_238", "loff_t");
__static_renaming("__loff_t_239", "loff_t");
__static_renaming("__ino_t_241", "ino_t");
__static_renaming("__ino_t_242", "ino_t");
__static_renaming("__ino_t_244", "ino_t");
__static_renaming("__ino_t_245", "ino_t");
__static_renaming("__dev_t_247", "dev_t");
__static_renaming("__dev_t_248", "dev_t");
__static_renaming("__gid_t_250", "gid_t");
__static_renaming("__gid_t_251", "gid_t");
__static_renaming("__gid_t_253", "gid_t");
__static_renaming("__gid_t_254", "gid_t");
__static_renaming("__mode_t_256", "mode_t");
__static_renaming("__mode_t_257", "mode_t");
__static_renaming("__nlink_t_259", "nlink_t");
__static_renaming("__nlink_t_260", "nlink_t");
__static_renaming("__uid_t_262", "uid_t");
__static_renaming("__uid_t_263", "uid_t");
__static_renaming("__uid_t_265", "uid_t");
__static_renaming("__uid_t_266", "uid_t");
__static_renaming("__off_t_268", "off_t");
__static_renaming("__off_t_269", "off_t");
__static_renaming("__off_t_271", "off_t");
__static_renaming("__off_t_272", "off_t");
__static_renaming("__pid_t_274", "pid_t");
__static_renaming("__pid_t_275", "pid_t");
__static_renaming("__pid_t_277", "pid_t");
__static_renaming("__pid_t_278", "pid_t");
__static_renaming("__id_t_280", "id_t");
__static_renaming("__id_t_281", "id_t");
__static_renaming("__ssize_t_283", "ssize_t");
__static_renaming("__ssize_t_284", "ssize_t");
__static_renaming("__daddr_t_286", "daddr_t");
__static_renaming("__daddr_t_287", "daddr_t");
__static_renaming("__caddr_t_289", "caddr_t");
__static_renaming("__caddr_t_290", "caddr_t");
__static_renaming("__key_t_291", "key_t");
__static_renaming("__key_t_292", "key_t");
__static_renaming("__key_t_294", "key_t");
__static_renaming("__key_t_295", "key_t");
__static_renaming("__clock_t_297", "clock_t");
__static_renaming("__clock_t_298", "clock_t");
__static_renaming("__time_t_300", "time_t");
__static_renaming("__time_t_301", "time_t");
__static_renaming("__clockid_t_303", "clockid_t");
__static_renaming("__clockid_t_304", "clockid_t");
__static_renaming("__timer_t_306", "timer_t");
__static_renaming("__timer_t_307", "timer_t");
__static_renaming("__ulong_309", "ulong");
__static_renaming("__ulong_310", "ulong");
__static_renaming("__ulong_311", "ulong");
__static_renaming("__ushort_312", "ushort");
__static_renaming("__uint_313", "uint");
__static_renaming("__int8_t_314", "int8_t");
__static_renaming("__int16_t_315", "int16_t");
__static_renaming("__int32_t_316", "int32_t");
__static_renaming("__int64_t_317", "int64_t");
__static_renaming("__u_int8_t_318", "u_int8_t");
__static_renaming("__u_int16_t_319", "u_int16_t");
__static_renaming("__u_int32_t_320", "u_int32_t");
__static_renaming("__u_int64_t_321", "u_int64_t");
__static_renaming("__register_t_322", "register_t");
__static_renaming("____bswap_32_324", "__bswap_32");
__static_renaming("____bswap_64_327", "__bswap_64");
__static_renaming("____sig_atomic_t_328", "__sig_atomic_t");
__static_renaming("____sigset_t_332", "__sigset_t");
__static_renaming("__sigset_t_333", "sigset_t");
__static_renaming("__suseconds_t_350", "suseconds_t");
__static_renaming("__suseconds_t_351", "suseconds_t");
__static_renaming("____fd_mask_353", "__fd_mask");
__static_renaming("____fd_mask_354", "__fd_mask");
__static_renaming("__fd_set_362", "fd_set");
__static_renaming("__fd_mask_363", "fd_mask");
__static_renaming("__fd_mask_364", "fd_mask");
__static_renaming("__select_376", "select");
__static_renaming("__select_377", "select");
__static_renaming("__pselect_392", "pselect");
__static_renaming("__pselect_393", "pselect");
__static_renaming("____fdelt_chk_397", "__fdelt_chk");
__static_renaming("____fdelt_warn_399", "__fdelt_warn");
__static_renaming("__gnu_dev_major_401", "gnu_dev_major");
__static_renaming("__gnu_dev_major_402", "gnu_dev_major");
__static_renaming("__gnu_dev_minor_404", "gnu_dev_minor");
__static_renaming("__gnu_dev_makedev_407", "gnu_dev_makedev");
__static_renaming("__blksize_t_412", "blksize_t");
__static_renaming("__blksize_t_413", "blksize_t");
__static_renaming("__blkcnt_t_415", "blkcnt_t");
__static_renaming("__blkcnt_t_416", "blkcnt_t");
__static_renaming("__fsblkcnt_t_418", "fsblkcnt_t");
__static_renaming("__fsblkcnt_t_419", "fsblkcnt_t");
__static_renaming("__blkcnt_t_421", "blkcnt_t");
__static_renaming("__blkcnt_t_422", "blkcnt_t");
__static_renaming("__fsblkcnt_t_424", "fsblkcnt_t");
__static_renaming("__fsblkcnt_t_425", "fsblkcnt_t");
__static_renaming("__fsfilcnt_t_427", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_428", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_430", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_431", "fsfilcnt_t");
__static_renaming("__pthread_t_433", "pthread_t");
__static_renaming("__pthread_attr_t_437", "pthread_attr_t");
__static_renaming("____pthread_list_t_442", "__pthread_list_t");
__static_renaming("____pthread_list_t_443", "__pthread_list_t");
__static_renaming("__pthread_mutex_t_459", "pthread_mutex_t");
__static_renaming("__pthread_mutexattr_t_464", "pthread_mutexattr_t");
__static_renaming("__rand_465", "rand");
__static_renaming("__srand_467", "srand");
__static_renaming("__rand_r_469", "rand_r");
__static_renaming("__drand48_470", "drand48");
__static_renaming("__erand48_472", "erand48");
__static_renaming("__lrand48_473", "lrand48");
__static_renaming("__nrand48_475", "nrand48");
__static_renaming("__mrand48_476", "mrand48");
__static_renaming("__jrand48_478", "jrand48");
__static_renaming("__srand48_480", "srand48");
__static_renaming("__seed48_482", "seed48");
__static_renaming("__lcong48_484", "lcong48");
__static_renaming("__malloc_486", "malloc");
__static_renaming("__malloc_487", "malloc");
__static_renaming("__calloc_490", "calloc");
__static_renaming("__calloc_491", "calloc");
__static_renaming("__realloc_494", "realloc");
__static_renaming("__free_496", "free");
__static_renaming("__cfree_498", "cfree");
__static_renaming("__alloca_500", "alloca");
__static_renaming("__valloc_502", "valloc");
__static_renaming("__valloc_503", "valloc");
__static_renaming("__posix_memalign_507", "posix_memalign");
__static_renaming("__posix_memalign_508", "posix_memalign");
__static_renaming("__aligned_alloc_511", "aligned_alloc");
__static_renaming("__aligned_alloc_512", "aligned_alloc");
__static_renaming("__aligned_alloc_513", "aligned_alloc");
__static_renaming("__aligned_alloc_514", "aligned_alloc");
__static_renaming("__abort_515", "abort");
__static_renaming("__atexit_517", "atexit");
__static_renaming("__at_quick_exit_519", "at_quick_exit");
__static_renaming("__on_exit_524", "on_exit");
__static_renaming("__exit_526", "exit");
__static_renaming("__exit_527", "exit");
__static_renaming("__quick_exit_529", "quick_exit");
__static_renaming("___Exit_531", "_Exit");
__static_renaming("__getenv_533", "getenv");
__static_renaming("__getenv_534", "getenv");
__static_renaming("__putenv_536", "putenv");
__static_renaming("__setenv_540", "setenv");
__static_renaming("__unsetenv_542", "unsetenv");
__static_renaming("__clearenv_543", "clearenv");
__static_renaming("__mktemp_545", "mktemp");
__static_renaming("__mkstemp_548", "mkstemp");
__static_renaming("__mkstemp_549", "mkstemp");
__static_renaming("__mkstemp_550", "mkstemp");
__static_renaming("__mkstemp_551", "mkstemp");
__static_renaming("__mkstemps_556", "mkstemps");
__static_renaming("__mkstemps_557", "mkstemps");
__static_renaming("__mkstemps_558", "mkstemps");
__static_renaming("__mkstemps_559", "mkstemps");
__static_renaming("__mkdtemp_561", "mkdtemp");
__static_renaming("__mkdtemp_562", "mkdtemp");
__static_renaming("__system_564", "system");
__static_renaming("__system_565", "system");
__static_renaming("__system_566", "system");
__static_renaming("__system_567", "system");
__static_renaming("__realpath_570", "realpath");
__static_renaming("__realpath_571", "realpath");
__static_renaming("____compar_fn_t_572", "__compar_fn_t");
__static_renaming("__bsearch_580", "bsearch");
__static_renaming("__bsearch_582", "bsearch");
__static_renaming("____l_589", "__l");
__static_renaming("____u_590", "__u");
__static_renaming("____idx_591", "__idx");
__static_renaming("____p_592", "__p");
__static_renaming("____comparison_593", "__comparison");
__static_renaming("__qsort_601", "qsort");
__static_renaming("__qsort_603", "qsort");
__static_renaming("__abs_606", "abs");
__static_renaming("__abs_607", "abs");
__static_renaming("__labs_609", "labs");
__static_renaming("__labs_610", "labs");
__static_renaming("__llabs_612", "llabs");
__static_renaming("__llabs_613", "llabs");
__static_renaming("__div_616", "div");
__static_renaming("__div_617", "div");
__static_renaming("__ldiv_620", "ldiv");
__static_renaming("__ldiv_622", "ldiv");
__static_renaming("__lldiv_626", "lldiv");
__static_renaming("__lldiv_628", "lldiv");
__static_renaming("__ecvt_634", "ecvt");
__static_renaming("__ecvt_635", "ecvt");
__static_renaming("__fcvt_640", "fcvt");
__static_renaming("__fcvt_641", "fcvt");
__static_renaming("__gcvt_645", "gcvt");
__static_renaming("__gcvt_646", "gcvt");
__static_renaming("__qecvt_651", "qecvt");
__static_renaming("__qecvt_652", "qecvt");
__static_renaming("__qfcvt_657", "qfcvt");
__static_renaming("__qfcvt_658", "qfcvt");
__static_renaming("__qgcvt_662", "qgcvt");
__static_renaming("__qgcvt_663", "qgcvt");
__static_renaming("__ecvt_r_670", "ecvt_r");
__static_renaming("__fcvt_r_677", "fcvt_r");
__static_renaming("__qecvt_r_684", "qecvt_r");
__static_renaming("__qfcvt_r_691", "qfcvt_r");
__static_renaming("__mblen_694", "mblen");
__static_renaming("__mblen_695", "mblen");
__static_renaming("__mbtowc_699", "mbtowc");
__static_renaming("__wctomb_702", "wctomb");
__static_renaming("__mbstowcs_706", "mbstowcs");
__static_renaming("__wcstombs_710", "wcstombs");
__static_renaming("__rpmatch_712", "rpmatch");
__static_renaming("__rpmatch_713", "rpmatch");
__static_renaming("__getsubopt_717", "getsubopt");
__static_renaming("__getsubopt_718", "getsubopt");
__static_renaming("__getloadavg_721", "getloadavg");
__static_renaming("____realpath_chk_726", "__realpath_chk");
__static_renaming("____realpath_alias_729", "__realpath_alias");
__static_renaming("____realpath_chk_warn_733", "__realpath_chk_warn");
__static_renaming("____ptsname_r_chk_741", "__ptsname_r_chk");
__static_renaming("____ptsname_r_alias_745", "__ptsname_r_alias");
__static_renaming("____ptsname_r_chk_warn_750", "__ptsname_r_chk_warn");
__static_renaming("____wctomb_chk_758", "__wctomb_chk");
__static_renaming("____wctomb_alias_761", "__wctomb_alias");
__static_renaming("____mbstowcs_chk_768", "__mbstowcs_chk");
__static_renaming("____mbstowcs_alias_772", "__mbstowcs_alias");
__static_renaming("____mbstowcs_chk_warn_777", "__mbstowcs_chk_warn");
__static_renaming("____wcstombs_chk_785", "__wcstombs_chk");
__static_renaming("____wcstombs_alias_789", "__wcstombs_alias");
__static_renaming("____wcstombs_chk_warn_794", "__wcstombs_chk_warn");
__static_renaming("__IS_ERR_799", "IS_ERR");
__static_renaming("__IS_ERR_800", "IS_ERR");
__static_renaming("__IS_ERR_801", "IS_ERR");
__static_renaming("__IS_ERR_OR_NULL_806", "IS_ERR_OR_NULL");
__static_renaming("__some_int_809", "some_int");
__static_renaming("__ip6_dst_lookup_flow_810", "ip6_dst_lookup_flow");
__static_renaming("__dst_812", "dst");
__static_renaming("__rt_814", "rt");
__static_renaming("__sctp_v6_get_dst_816", "sctp_v6_get_dst");
__static_renaming("__main_830", "main");
__static_renaming("__main_831", "main");

__static_condition_renaming("__static_condition_default_60", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && !(defined _SYS_WAIT_H) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_67", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && !(defined _SYS_WAIT_H)");
__static_condition_renaming("__static_condition_default_215", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _SYS_WAIT_H) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_234", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_237", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_240", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_243", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined)");
__static_condition_renaming("__static_condition_default_246", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined) || !(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined)");
__static_condition_renaming("__static_condition_default_249", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_252", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_255", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_258", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_261", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_264", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_267", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_270", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_273", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined) || !(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_276", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_279", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_282", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __id_t_defined)");
__static_condition_renaming("__static_condition_default_285", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ssize_t_defined)");
__static_condition_renaming("__static_condition_default_288", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_293", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_296", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_299", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __clock_t_defined)");
__static_condition_renaming("__static_condition_default_302", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __time_t_defined)");
__static_condition_renaming("__static_condition_default_305", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __clockid_t_defined)");
__static_condition_renaming("__static_condition_default_308", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timer_t_defined)");
__static_condition_renaming("__static_condition_default_325", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _SYS_WAIT_H)");
__static_condition_renaming("__static_condition_default_341", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_349", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_352", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __suseconds_t_defined)");
__static_condition_renaming("__static_condition_default_361", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_378", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_379", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_394", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_395", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_414", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blksize_t_defined)");
__static_condition_renaming("__static_condition_default_417", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined) || !(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined)");
__static_condition_renaming("__static_condition_default_420", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) || !(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_423", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined)");
__static_condition_renaming("__static_condition_default_426", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_429", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) || !(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_432", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_579", "!(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_581", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_594", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && !(defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_595", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_602", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && !(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_604", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_621", "!(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_623", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_627", "!(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_629", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_736", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_802", "!(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_803", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_804", "!(defined _STDLIB_H) && (defined __need_malloc_and_calloc) || (defined _STDLIB_H)");
__static_condition_renaming("__static_condition_default_807", "!(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_808", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_811", "(defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_813", "!(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || (defined _STDLIB_H) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_815", "!(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || (defined _STDLIB_H) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_817", "(defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_818", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_819", "!(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || (defined _STDLIB_H) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_820", "!(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_821", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_822", "!(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || (defined _STDLIB_H) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_823", "!(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_824", "!(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && !(defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && !SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && !(defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && !SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && !(defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && !SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && !(defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && !SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_825", "!(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && (defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && !(defined _FORTIFY_SOURCE) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && (defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && (defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && (defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_826", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_827", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && !(defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && !SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_828", "!(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && !(defined SCTP_DEBUG) && (defined CONFIG_SCTP_DBG_MSG) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || !(defined _STDLIB_H) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined __need_malloc_and_calloc) && (defined SCTP_DEBUG) && SCTP_DEBUG && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_829", "!(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6) || (defined _STDLIB_H) && (defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_832", "!(defined CONFIG_IP_SCTP) || (defined CONFIG_IP_SCTP) && !(defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_833", "(defined CONFIG_IP_SCTP) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_834", "!(defined _STDLIB_H) && !(defined __STRICT_ANSI__) && !(defined __need_malloc_and_calloc)");

if (__static_condition_default_834) {
__static_parse_error("Unable to parse");
}
};
typedef long int  __ptrdiff_t_0;// L143:L324
typedef long unsigned int  __size_t_1;// L177:L209
typedef int  __wchar_t_2;// L243:L321
enum ____anonymous_tag_6_7 {
__P_ALL_3,
__P_PID_4,
__P_PGID_5,
};
typedef enum ____anonymous_tag_6_7  __idtype_t_8;// L50:L55
typedef unsigned char  ____u_char_9;// L30
typedef unsigned short int  ____u_short_10;// L31
typedef unsigned int  ____u_int_11;// L32
typedef unsigned long int  ____u_long_12;// L33
typedef signed char  ____int8_t_13;// L36
typedef unsigned char  ____uint8_t_14;// L37
typedef signed short int  ____int16_t_15;// L38
typedef unsigned short int  ____uint16_t_16;// L39
typedef signed int  ____int32_t_17;// L40
typedef unsigned int  ____uint32_t_18;// L41
typedef signed long int  ____int64_t_19;// L43
typedef unsigned long int  ____uint64_t_20;// L44
typedef long int  ____quad_t_21;// L52
typedef unsigned long int  ____u_quad_t_22;// L53
typedef unsigned long int  ____dev_t_23;// L109:L124
typedef unsigned int  ____uid_t_24;// L92:L125
typedef unsigned int  ____gid_t_25;// L92:L126
typedef unsigned long int  ____ino_t_26;// L94:L127
typedef unsigned long int  ____ino64_t_27;// L109:L128
typedef unsigned int  ____mode_t_28;// L92:L129
typedef unsigned long int  ____nlink_t_29;// L94:L130
typedef long int  ____off_t_30;// L93:L131
typedef long int  ____off64_t_31;// L108:L132
typedef int  ____pid_t_32;// L91:L133
struct ____anonymous_tag_33_34 {
int  ____val_35[2];// L72
};
typedef struct ____anonymous_tag_33_34  ____fsid_t_36;// L72:L134
typedef long int  ____clock_t_37;// L93:L135
typedef unsigned long int  ____rlim_t_38;// L94:L136
typedef unsigned long int  ____rlim64_t_39;// L109:L137
typedef unsigned int  ____id_t_40;// L92:L138
typedef long int  ____time_t_41;// L93:L139
typedef unsigned int  ____useconds_t_42;// L92:L140
typedef long int  ____suseconds_t_43;// L93:L141
typedef int  ____daddr_t_44;// L91:L143
typedef int  ____key_t_45;// L91:L144
typedef int  ____clockid_t_46;// L91:L147
typedef void  * (____timer_t_47);// L70:L150
typedef long int  ____blksize_t_48;// L93:L153
typedef long int  ____blkcnt_t_49;// L93:L158
typedef long int  ____blkcnt64_t_50;// L108:L159
typedef unsigned long int  ____fsblkcnt_t_51;// L94:L162
typedef unsigned long int  ____fsblkcnt64_t_52;// L109:L163
typedef unsigned long int  ____fsfilcnt_t_53;// L94:L166
typedef unsigned long int  ____fsfilcnt64_t_54;// L109:L167
typedef long int  ____fsword_t_55;// L93:L170
typedef long int  ____ssize_t_56;// L110:L172
typedef long int  ____syscall_slong_t_57;// L93:L175
typedef unsigned long int  ____syscall_ulong_t_58;// L94:L177
typedef ____off64_t_31  ____loff_t_59;// L181
typedef ____quad_t_21  * (____qaddr_t_61);// L182
typedef char  * (____caddr_t_62);// L183
typedef long int  ____intptr_t_63;// L110:L186
typedef unsigned int  ____socklen_t_64;// L92:L189
struct ____anonymous_tag_70_71 {
unsigned int  ____w_termsig_72 : 7;// L72
unsigned int  ____w_coredump_73 : 1;// L73
unsigned int  ____w_retcode_74 : 8;// L74
unsigned int  __anon_id_0_75 : 16;// L75
};
struct ____anonymous_tag_76_77 {
unsigned int  ____w_stopval_78 : 8;// L87
unsigned int  ____w_stopsig_79 : 8;// L88
unsigned int  __anon_id_1_80 : 16;// L89
};
union __wait_81 {
int  __w_status_82;// L68
struct ____anonymous_tag_70_71  ____wait_terminated_83;// L69
struct ____anonymous_tag_76_77  ____wait_stopped_84;// L84
};
union ____anonymous_tag_85_86 {
union __wait_81  * (____uptr_87);// L69
int  * (____iptr_88);// L70
};
typedef union ____anonymous_tag_85_86  ____WAIT_STATUS_89;// L67:L71
struct ____anonymous_tag_90_91 {
int  __quot_92;// L99
int  __rem_93;// L100
};
typedef struct ____anonymous_tag_90_91  __div_t_94;// L97:L101
struct ____anonymous_tag_95_96 {
long int  __quot_97;// L107
long int  __rem_98;// L108
};
typedef struct ____anonymous_tag_95_96  __ldiv_t_99;// L105:L109
struct ____anonymous_tag_100_101 {
long long int  __quot_102;// L119
long long int  __rem_103;// L120
};
typedef struct ____anonymous_tag_100_101  __lldiv_t_104;// L117:L121
typedef unsigned char  ____u_char_164;// L30
typedef unsigned short int  ____u_short_165;// L31
typedef unsigned int  ____u_int_166;// L32
typedef unsigned long int  ____u_long_167;// L33
typedef signed char  ____int8_t_168;// L36
typedef unsigned char  ____uint8_t_169;// L37
typedef signed short int  ____int16_t_170;// L38
typedef unsigned short int  ____uint16_t_171;// L39
typedef signed int  ____int32_t_172;// L40
typedef unsigned int  ____uint32_t_173;// L41
typedef signed long int  ____int64_t_174;// L43
typedef unsigned long int  ____uint64_t_175;// L44
typedef long int  ____quad_t_176;// L52
typedef unsigned long int  ____u_quad_t_177;// L53
typedef unsigned long int  ____dev_t_178;// L109:L124
typedef unsigned int  ____uid_t_179;// L92:L125
typedef unsigned int  ____gid_t_180;// L92:L126
typedef unsigned long int  ____ino_t_181;// L94:L127
typedef unsigned long int  ____ino64_t_182;// L109:L128
typedef unsigned int  ____mode_t_183;// L92:L129
typedef unsigned long int  ____nlink_t_184;// L94:L130
typedef long int  ____off_t_185;// L93:L131
typedef long int  ____off64_t_186;// L108:L132
typedef int  ____pid_t_187;// L91:L133
struct ____anonymous_tag_188_189 {
int  ____val_190[2];// L72
};
typedef struct ____anonymous_tag_188_189  ____fsid_t_191;// L72:L134
typedef long int  ____clock_t_192;// L93:L135
typedef unsigned long int  ____rlim_t_193;// L94:L136
typedef unsigned long int  ____rlim64_t_194;// L109:L137
typedef unsigned int  ____id_t_195;// L92:L138
typedef long int  ____time_t_196;// L93:L139
typedef unsigned int  ____useconds_t_197;// L92:L140
typedef long int  ____suseconds_t_198;// L93:L141
typedef int  ____daddr_t_199;// L91:L143
typedef int  ____key_t_200;// L91:L144
typedef int  ____clockid_t_201;// L91:L147
typedef void  * (____timer_t_202);// L70:L150
typedef long int  ____blksize_t_203;// L93:L153
typedef long int  ____blkcnt_t_204;// L93:L158
typedef long int  ____blkcnt64_t_205;// L108:L159
typedef unsigned long int  ____fsblkcnt_t_206;// L94:L162
typedef unsigned long int  ____fsblkcnt64_t_207;// L109:L163
typedef unsigned long int  ____fsfilcnt_t_208;// L94:L166
typedef unsigned long int  ____fsfilcnt64_t_209;// L109:L167
typedef long int  ____fsword_t_210;// L93:L170
typedef long int  ____ssize_t_211;// L110:L172
typedef long int  ____syscall_slong_t_212;// L93:L175
typedef unsigned long int  ____syscall_ulong_t_213;// L94:L177
typedef ____off64_t_186  ____loff_t_214;// L181
typedef ____quad_t_176  * (____qaddr_t_216);// L182
typedef char  * (____caddr_t_217);// L183
typedef long int  ____intptr_t_218;// L110:L186
typedef unsigned int  ____socklen_t_219;// L92:L189
typedef ____u_char_9  __u_char_220;// L33
typedef ____u_char_164  __u_char_221;// L33
typedef ____u_short_10  __u_short_222;// L34
typedef ____u_short_165  __u_short_223;// L34
typedef ____u_int_11  __u_int_224;// L35
typedef ____u_int_166  __u_int_225;// L35
typedef ____u_long_12  __u_long_226;// L36
typedef ____u_long_167  __u_long_227;// L36
typedef ____quad_t_21  __quad_t_228;// L37
typedef ____quad_t_176  __quad_t_229;// L37
typedef ____u_quad_t_22  __u_quad_t_230;// L38
typedef ____u_quad_t_177  __u_quad_t_231;// L38
typedef ____fsid_t_36  __fsid_t_232;// L39
typedef ____fsid_t_191  __fsid_t_233;// L39
typedef ____loff_t_59  __loff_t_235;// L44
typedef ____loff_t_214  __loff_t_236;// L44
typedef ____loff_t_59  __loff_t_238;// L44
typedef ____loff_t_214  __loff_t_239;// L44
typedef ____ino64_t_27  __ino_t_241;// L50
typedef ____ino64_t_182  __ino_t_242;// L50
typedef ____ino_t_26  __ino_t_244;// L48
typedef ____ino_t_181  __ino_t_245;// L48
typedef ____dev_t_23  __dev_t_247;// L60
typedef ____dev_t_178  __dev_t_248;// L60
typedef ____gid_t_25  __gid_t_250;// L65
typedef ____gid_t_180  __gid_t_251;// L65
typedef ____gid_t_25  __gid_t_253;// L65
typedef ____gid_t_180  __gid_t_254;// L65
typedef ____mode_t_28  __mode_t_256;// L70
typedef ____mode_t_183  __mode_t_257;// L70
typedef ____nlink_t_29  __nlink_t_259;// L75
typedef ____nlink_t_184  __nlink_t_260;// L75
typedef ____uid_t_24  __uid_t_262;// L80
typedef ____uid_t_179  __uid_t_263;// L80
typedef ____uid_t_24  __uid_t_265;// L80
typedef ____uid_t_179  __uid_t_266;// L80
typedef ____off64_t_31  __off_t_268;// L88
typedef ____off64_t_186  __off_t_269;// L88
typedef ____off_t_30  __off_t_271;// L86
typedef ____off_t_185  __off_t_272;// L86
typedef ____pid_t_32  __pid_t_274;// L98
typedef ____pid_t_187  __pid_t_275;// L98
typedef ____pid_t_32  __pid_t_277;// L98
typedef ____pid_t_187  __pid_t_278;// L98
typedef ____id_t_40  __id_t_280;// L104
typedef ____id_t_195  __id_t_281;// L104
typedef ____ssize_t_56  __ssize_t_283;// L109
typedef ____ssize_t_211  __ssize_t_284;// L109
typedef ____daddr_t_44  __daddr_t_286;// L115
typedef ____daddr_t_199  __daddr_t_287;// L115
typedef ____caddr_t_62  __caddr_t_289;// L116
typedef ____caddr_t_217  __caddr_t_290;// L116
typedef ____key_t_45  __key_t_291;// L122
typedef ____key_t_200  __key_t_292;// L122
typedef ____key_t_45  __key_t_294;// L122
typedef ____key_t_200  __key_t_295;// L122
typedef ____clock_t_37  __clock_t_297;// L59
typedef ____clock_t_192  __clock_t_298;// L59
typedef ____time_t_41  __time_t_300;// L75
typedef ____time_t_196  __time_t_301;// L75
typedef ____clockid_t_46  __clockid_t_303;// L91
typedef ____clockid_t_201  __clockid_t_304;// L91
typedef ____timer_t_47  __timer_t_306;// L103
typedef ____timer_t_202  __timer_t_307;// L103
typedef unsigned long int  __ulong_309;// L150
typedef unsigned long int  __ulong_310;// L150
typedef unsigned long int  __ulong_311;// L150
typedef unsigned short int  __ushort_312;// L151
typedef unsigned int  __uint_313;// L152
typedef int  __int8_t_314;// L188:L194
typedef int  __int16_t_315;// L188:L195
typedef int  __int32_t_316;// L188:L196
typedef int  __int64_t_317;// L188:L197
typedef unsigned int  __u_int8_t_318;// L190:L200
typedef unsigned int  __u_int16_t_319;// L190:L201
typedef unsigned int  __u_int32_t_320;// L190:L202
typedef unsigned int  __u_int64_t_321;// L190:L203
typedef int  __register_t_322;// L205
typedef int  ____sig_atomic_t_328;// L22
struct ____anonymous_tag_329_330 {
unsigned long int  ____val_331[( 1024 / ( 8 * sizeof(unsigned long) ) )];// L29
};
typedef struct ____anonymous_tag_329_330  ____sigset_t_332;// L27:L30
typedef ____sigset_t_332  __sigset_t_333;// L37
struct __timespec_334 {
____time_t_41  __tv_sec_335;// L0
____time_t_196  __tv_sec_336;// L0
____syscall_slong_t_57  __tv_nsec_338;// L0
____syscall_slong_t_212  __tv_nsec_339;// L0
};
struct __timeval_342 {
____time_t_41  __tv_sec_343;// L0
____time_t_196  __tv_sec_344;// L0
____suseconds_t_43  __tv_usec_346;// L0
____suseconds_t_198  __tv_usec_347;// L0
};
typedef ____suseconds_t_43  __suseconds_t_350;// L48
typedef ____suseconds_t_198  __suseconds_t_351;// L48
typedef long int  ____fd_mask_353;// L54
typedef long int  ____fd_mask_354;// L54
struct ____anonymous_tag_355_356 {
____fd_mask_353  ____fds_bits_357[1024 / ( 8 * ( int   ) sizeof(long) )];// L0
____fd_mask_354  ____fds_bits_359[1024 / ( 8 * ( int   ) sizeof(long) )];// L0
};
typedef struct ____anonymous_tag_355_356  __fd_set_362;// L64:L75
typedef ____fd_mask_353  __fd_mask_363;// L82
typedef ____fd_mask_354  __fd_mask_364;// L82
typedef ____blksize_t_48  __blksize_t_412;// L228
typedef ____blksize_t_203  __blksize_t_413;// L228
typedef ____blkcnt_t_49  __blkcnt_t_415;// L235
typedef ____blkcnt_t_204  __blkcnt_t_416;// L235
typedef ____fsblkcnt_t_51  __fsblkcnt_t_418;// L239
typedef ____fsblkcnt_t_206  __fsblkcnt_t_419;// L239
typedef ____blkcnt64_t_50  __blkcnt_t_421;// L248
typedef ____blkcnt64_t_205  __blkcnt_t_422;// L248
typedef ____fsblkcnt64_t_52  __fsblkcnt_t_424;// L252
typedef ____fsblkcnt64_t_207  __fsblkcnt_t_425;// L252
typedef ____fsfilcnt_t_53  __fsfilcnt_t_427;// L243
typedef ____fsfilcnt_t_208  __fsfilcnt_t_428;// L243
typedef ____fsfilcnt64_t_54  __fsfilcnt_t_430;// L256
typedef ____fsfilcnt64_t_209  __fsfilcnt_t_431;// L256
typedef unsigned long int  __pthread_t_433;// L60
union __pthread_attr_t_434 {
char  ____size_435[56];// L65
long int  ____align_436;// L66
};
typedef union __pthread_attr_t_434  __pthread_attr_t_437;// L69
struct ____pthread_internal_list_439 {
struct __forward_tag_reference_438  * (____prev_440);// L0
struct __forward_tag_reference_438  * (____next_441);// L0
};
typedef struct ____pthread_internal_list_439  ____pthread_list_t_442;// L75:L79
typedef struct ____pthread_internal_list_439  ____pthread_list_t_443;// L75:L79
struct ____pthread_mutex_s_444 {
int  ____lock_445;// L94
unsigned int  ____count_446;// L95
int  ____owner_447;// L96
unsigned int  ____nusers_448;// L98
int  ____kind_449;// L102
short  ____spins_450;// L104
short  ____elision_451;// L105
____pthread_list_t_442  ____list_452;// L0
____pthread_list_t_443  ____list_453;// L0
};
union ____anonymous_tag_454_455 {
struct ____pthread_mutex_s_444  ____data_456;// L92
char  ____size_457[40];// L126
long int  ____align_458;// L127
};
typedef union ____anonymous_tag_454_455  __pthread_mutex_t_459;// L90:L128
union ____anonymous_tag_460_461 {
char  ____size_462[4];// L132
int  ____align_463;// L133
};
typedef union ____anonymous_tag_460_461  __pthread_mutexattr_t_464;// L130:L134
typedef int  (* (____compar_fn_t_572)) (const void  *, const void  *);// L741

struct __forward_tag_reference_438 { // generated union of struct variations
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
// typedef moved to top of scope
static __inline unsigned int  (____bswap_32_66) (unsigned int  ____bsx_65) {

if (__static_condition_default_67) {

{// L46
{



__static_type_error("invalid type found in return expression");
}
}// L48


}
}
static __inline ____uint64_t_20  (____bswap_64_69) (____uint64_t_20  ____bsx_68) {

if (__static_condition_default_67) {

{// L110
{



__static_type_error("invalid type found in return expression");
}
}// L112


}
}
union __wait_81 ;// L66
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern __size_t_1  (____ctype_get_mb_cur_max_105) (void  );// L139
extern __size_t_1  (____ctype_get_mb_cur_max_106) (void  );// L139
extern __size_t_1  (____ctype_get_mb_cur_max_107) (void  );// L139
extern __size_t_1  (____ctype_get_mb_cur_max_108) (void  );// L139
extern double  (__atof_110) (const char  * (____nptr_109));// L144:L145
extern double  (__atof_111) (const char  * (____nptr_109));// L144:L145
extern int  (__atoi_113) (const char  * (____nptr_112));// L147:L148
extern int  (__atoi_114) (const char  * (____nptr_112));// L147:L148
extern long int  (__atol_116) (const char  * (____nptr_115));// L150:L151
extern long int  (__atol_117) (const char  * (____nptr_115));// L150:L151
extern long long int  (__atoll_119) (const char  * (____nptr_118));// L157:L158
extern long long int  (__atoll_120) (const char  * (____nptr_118));// L157:L158
extern double  (__strtod_123) (const char  * __restrict  ____nptr_121, char  * (* __restrict  ____endptr_122));// L164:L166
extern float  (__strtof_126) (const char  * __restrict  ____nptr_124, char  * (* __restrict  ____endptr_125));// L172:L173
extern long double  (__strtold_129) (const char  * __restrict  ____nptr_127, char  * (* __restrict  ____endptr_128));// L175:L177
extern long int  (__strtol_133) (const char  * __restrict  ____nptr_130, char  * (* __restrict  ____endptr_131), int  ____base_132);// L183:L185
extern unsigned long int  (__strtoul_137) (const char  * __restrict  ____nptr_134, char  * (* __restrict  ____endptr_135), int  ____base_136);// L187:L189
extern long long int  (__strtoq_141) (const char  * __restrict  ____nptr_138, char  * (* __restrict  ____endptr_139), int  ____base_140);// L195:L197
extern unsigned long long int  (__strtouq_145) (const char  * __restrict  ____nptr_142, char  * (* __restrict  ____endptr_143), int  ____base_144);// L200:L202
extern long long int  (__strtoll_149) (const char  * __restrict  ____nptr_146, char  * (* __restrict  ____endptr_147), int  ____base_148);// L209:L211
extern long long int  (__strtoll_150) (const char  * __restrict  ____nptr_146, char  * (* __restrict  ____endptr_147), int  ____base_148);// L209:L211
extern unsigned long long int  (__strtoull_154) (const char  * __restrict  ____nptr_151, char  * (* __restrict  ____endptr_152), int  ____base_153);// L214:L216
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
extern char  * ((__l64a_159) (long int  ____n_158));// L305
extern char  * ((__l64a_160) (long int  ____n_158));// L305
extern long int  (__a64l_162) (const char  * (____s_161));// L308:L309
extern long int  (__a64l_163) (const char  * (____s_161));// L308:L309
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
static __inline unsigned int  (____bswap_32_324) (unsigned int  ____bsx_323) {

if (__static_condition_default_325) {

{// L46
{



__static_type_error("invalid type found in return expression");
}
}// L48


}
}
static __inline ____uint64_t_175  (____bswap_64_327) (____uint64_t_175  ____bsx_326) {

if (__static_condition_default_325) {

{// L110
{



__static_type_error("invalid type found in return expression");
}
}// L112


}
}
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __timespec_334 ;// L120

struct __timeval_342 ;// L30

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__select_376) (int  ____nfds_365, __fd_set_362  * __restrict  ____readfds_366, __fd_set_362  * __restrict  ____writefds_368, __fd_set_362  * __restrict  ____exceptfds_370, struct __timeval_342  * __restrict  ____timeout_373);// L106:L109
extern int  (__select_377) (int  ____nfds_365, __fd_set_362  * __restrict  ____readfds_366, __fd_set_362  * __restrict  ____writefds_368, __fd_set_362  * __restrict  ____exceptfds_370, struct __forward_tag_reference_372  * __restrict  ____timeout_375);// L106:L109
extern int  (__pselect_392) (int  ____nfds_380, __fd_set_362  * __restrict  ____readfds_381, __fd_set_362  * __restrict  ____writefds_383, __fd_set_362  * __restrict  ____exceptfds_385, const struct __timespec_334  * __restrict  ____timeout_388, const ____sigset_t_332  * __restrict  ____sigmask_391);// L118:L122
extern int  (__pselect_393) (int  ____nfds_380, __fd_set_362  * __restrict  ____readfds_381, __fd_set_362  * __restrict  ____writefds_383, __fd_set_362  * __restrict  ____exceptfds_385, const struct __forward_tag_reference_387  * __restrict  ____timeout_390, const ____sigset_t_332  * __restrict  ____sigmask_391);// L118:L122
extern long int  (____fdelt_chk_397) (long int  ____d_396);// L24
extern long int  (____fdelt_warn_399) (long int  ____d_398);// L25:L26
extern unsigned int  (__gnu_dev_major_401) (unsigned long long int  ____dev_400);// L27:L28
extern unsigned int  (__gnu_dev_major_402) (unsigned long long int  ____dev_400);// L27:L28
extern unsigned int  (__gnu_dev_minor_404) (unsigned long long int  ____dev_403);// L30:L31
extern unsigned long long int  (__gnu_dev_makedev_407) (unsigned int  ____major_405, unsigned int  ____minor_406);// L33:L35
__extension__/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
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
union __pthread_attr_t_434 ;// L63
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__rand_465) (void  );// L374
extern void  (__srand_467) (unsigned int  ____seed_466);// L376
extern int  (__rand_r_469) (unsigned int  * (____seed_468));// L381
extern double  (__drand48_470) (void  );// L389
extern double  (__erand48_472) (unsigned short int  ____xsubi_471[3]);// L390
extern long int  (__lrand48_473) (void  );// L393
extern long int  (__nrand48_475) (unsigned short int  ____xsubi_474[3]);// L394:L395
extern long int  (__mrand48_476) (void  );// L398
extern long int  (__jrand48_478) (unsigned short int  ____xsubi_477[3]);// L399:L400
extern void  (__srand48_480) (long int  ____seedval_479);// L403
extern unsigned short int  * ((__seed48_482) (unsigned short int  ____seed16v_481[3]));// L404:L405
extern void  (__lcong48_484) (unsigned short int  ____param_483[7]);// L406
extern void  * ((__malloc_486) (__size_t_1  ____size_485));// L466
extern void  * ((__malloc_487) (__size_t_1  ____size_485));// L466
extern void  * ((__calloc_490) (__size_t_1  ____nmemb_488, __size_t_1  ____size_489));// L468:L469
extern void  * ((__calloc_491) (__size_t_1  ____nmemb_488, __size_t_1  ____size_489));// L468:L469
extern void  * ((__realloc_494) (void  * (____ptr_492), __size_t_1  ____size_493));// L480:L481
extern void  (__free_496) (void  * (____ptr_495));// L483
extern void  (__cfree_498) (void  * (____ptr_497));// L488
extern void  * ((__alloca_500) (__size_t_1  ____size_499));// L32
extern void  * ((__valloc_502) (__size_t_1  ____size_501));// L498
extern void  * ((__valloc_503) (__size_t_1  ____size_501));// L498
extern int  (__posix_memalign_507) (void  * (* (____memptr_504)), __size_t_1  ____alignment_505, __size_t_1  ____size_506);// L503:L504
extern int  (__posix_memalign_508) (void  * (* (____memptr_504)), __size_t_1  ____alignment_505, __size_t_1  ____size_506);// L503:L504
extern void  * ((__aligned_alloc_511) (__size_t_1  ____alignment_509, __size_t_1  ____size_510));// L509:L510
extern void  * ((__aligned_alloc_512) (__size_t_1  ____alignment_509, __size_t_1  ____size_510));// L509:L510
extern void  * ((__aligned_alloc_513) (__size_t_1  ____alignment_509, __size_t_1  ____size_510));// L509:L510
extern void  * ((__aligned_alloc_514) (__size_t_1  ____alignment_509, __size_t_1  ____size_510));// L509:L510
extern void  (__abort_515) (void  );// L515
extern int  (__atexit_517) (void  (* (____func_516)) (void  ));// L519
extern int  (__at_quick_exit_519) (void  (* (____func_518)) (void  ));// L527
extern int  (__on_exit_524) (void  (* (____func_522)) (int  ____status_520, void  * (____arg_521)), void  * (____arg_523));// L535:L536
extern void  (__exit_526) (int  ____status_525);// L543
extern void  (__exit_527) (int  ____status_525);// L543
extern void  (__quick_exit_529) (int  ____status_528);// L549
extern void  (___Exit_531) (int  ____status_530);// L557
extern char  * ((__getenv_533) (const char  * (____name_532)));// L564
extern char  * ((__getenv_534) (const char  * (____name_532)));// L564
extern int  (__putenv_536) (char  * (____string_535));// L578
extern int  (__setenv_540) (const char  * (____name_537), const char  * (____value_538), int  ____replace_539);// L584:L585
extern int  (__unsetenv_542) (const char  * (____name_541));// L588
extern int  (__clearenv_543) (void  );// L595
extern char  * ((__mktemp_545) (char  * (____template_544)));// L606
extern int  (__mkstemp_548) (char  * (____template_546));// L619
extern int  (__mkstemp_550) (char  * (____template_546));// L619
extern int  (__mkstemp_549) (char  * (____template_547));// L622:L623
extern int  (__mkstemp_551) (char  * (____template_547));// L622:L623
extern int  (__mkstemps_556) (char  * (____template_552), int  ____suffixlen_553);// L641
extern int  (__mkstemps_557) (char  * (____template_554), int  ____suffixlen_555);// L644:L645
extern int  (__mkstemps_558) (char  * (____template_552), int  ____suffixlen_553);// L641
extern int  (__mkstemps_559) (char  * (____template_554), int  ____suffixlen_555);// L644:L645
extern char  * ((__mkdtemp_561) (char  * (____template_560)));// L662
extern char  * ((__mkdtemp_562) (char  * (____template_560)));// L662
extern int  (__system_564) (const char  * (____command_563));// L716
extern int  (__system_565) (const char  * (____command_563));// L716
extern int  (__system_566) (const char  * (____command_563));// L716
extern int  (__system_567) (const char  * (____command_563));// L716
extern char  * ((__realpath_570) (const char  * __restrict  ____name_568, char  * __restrict  ____resolved_569));// L733:L734
extern char  * ((__realpath_571) (const char  * __restrict  ____name_568, char  * __restrict  ____resolved_569));// L733:L734
// typedef moved to top of scope
extern void  * ((__bsearch_580) (const void  * (____key_573), const void  * (____base_574), __size_t_1  ____nmemb_575, __size_t_1  ____size_576, ____compar_fn_t_572  ____compar_577));// L754:L756
extern void  * ((__bsearch_582) (const void  * (____key_573), const void  * (____base_574), __size_t_1  ____nmemb_575, __size_t_1  ____size_576, ____compar_fn_t_572  ____compar_577));// L754:L756
/* no function due to type errors in the function prototype */
extern void  (__qsort_601) (void  * (____base_596), __size_t_1  ____nmemb_597, __size_t_1  ____size_598, ____compar_fn_t_572  ____compar_599);// L764:L765
extern void  (__qsort_603) (void  * (____base_596), __size_t_1  ____nmemb_597, __size_t_1  ____size_598, ____compar_fn_t_572  ____compar_599);// L764:L765
extern int  (__abs_606) (int  ____x_605);// L774
extern int  (__abs_607) (int  ____x_605);// L774
extern long int  (__labs_609) (long int  ____x_608);// L775
extern long int  (__labs_610) (long int  ____x_608);// L775
extern long long int  (__llabs_612) (long long int  ____x_611);// L779:L780
extern long long int  (__llabs_613) (long long int  ____x_611);// L779:L780
extern __div_t_94  (__div_616) (int  ____numer_614, int  ____denom_615);// L788:L789
extern __div_t_94  (__div_617) (int  ____numer_614, int  ____denom_615);// L788:L789
extern __ldiv_t_99  (__ldiv_620) (long int  ____numer_618, long int  ____denom_619);// L790:L791
extern __ldiv_t_99  (__ldiv_622) (long int  ____numer_618, long int  ____denom_619);// L790:L791
extern __lldiv_t_104  (__lldiv_626) (long long int  ____numer_624, long long int  ____denom_625);// L796:L798
extern __lldiv_t_104  (__lldiv_628) (long long int  ____numer_624, long long int  ____denom_625);// L796:L798
extern char  * ((__ecvt_634) (double  ____value_630, int  ____ndigit_631, int  * __restrict  ____decpt_632, int  * __restrict  ____sign_633));// L811:L812
extern char  * ((__ecvt_635) (double  ____value_630, int  ____ndigit_631, int  * __restrict  ____decpt_632, int  * __restrict  ____sign_633));// L811:L812
extern char  * ((__fcvt_640) (double  ____value_636, int  ____ndigit_637, int  * __restrict  ____decpt_638, int  * __restrict  ____sign_639));// L817:L818
extern char  * ((__fcvt_641) (double  ____value_636, int  ____ndigit_637, int  * __restrict  ____decpt_638, int  * __restrict  ____sign_639));// L817:L818
extern char  * ((__gcvt_645) (double  ____value_642, int  ____ndigit_643, char  * (____buf_644)));// L823:L824
extern char  * ((__gcvt_646) (double  ____value_642, int  ____ndigit_643, char  * (____buf_644)));// L823:L824
extern char  * ((__qecvt_651) (long double  ____value_647, int  ____ndigit_648, int  * __restrict  ____decpt_649, int  * __restrict  ____sign_650));// L829:L831
extern char  * ((__qecvt_652) (long double  ____value_647, int  ____ndigit_648, int  * __restrict  ____decpt_649, int  * __restrict  ____sign_650));// L829:L831
extern char  * ((__qfcvt_657) (long double  ____value_653, int  ____ndigit_654, int  * __restrict  ____decpt_655, int  * __restrict  ____sign_656));// L832:L834
extern char  * ((__qfcvt_658) (long double  ____value_653, int  ____ndigit_654, int  * __restrict  ____decpt_655, int  * __restrict  ____sign_656));// L832:L834
extern char  * ((__qgcvt_662) (long double  ____value_659, int  ____ndigit_660, char  * (____buf_661)));// L835:L836
extern char  * ((__qgcvt_663) (long double  ____value_659, int  ____ndigit_660, char  * (____buf_661)));// L835:L836
extern int  (__ecvt_r_670) (double  ____value_664, int  ____ndigit_665, int  * __restrict  ____decpt_666, int  * __restrict  ____sign_667, char  * __restrict  ____buf_668, __size_t_1  ____len_669);// L841:L843
extern int  (__fcvt_r_677) (double  ____value_671, int  ____ndigit_672, int  * __restrict  ____decpt_673, int  * __restrict  ____sign_674, char  * __restrict  ____buf_675, __size_t_1  ____len_676);// L844:L846
extern int  (__qecvt_r_684) (long double  ____value_678, int  ____ndigit_679, int  * __restrict  ____decpt_680, int  * __restrict  ____sign_681, char  * __restrict  ____buf_682, __size_t_1  ____len_683);// L848:L851
extern int  (__qfcvt_r_691) (long double  ____value_685, int  ____ndigit_686, int  * __restrict  ____decpt_687, int  * __restrict  ____sign_688, char  * __restrict  ____buf_689, __size_t_1  ____len_690);// L852:L855
extern int  (__mblen_694) (const char  * (____s_692), __size_t_1  ____n_693);// L862
extern int  (__mblen_695) (const char  * (____s_692), __size_t_1  ____n_693);// L862
extern int  (__mbtowc_699) (__wchar_t_2  * __restrict  ____pwc_696, const char  * __restrict  ____s_697, __size_t_1  ____n_698);// L865:L866
extern int  (__wctomb_702) (char  * (____s_700), __wchar_t_2  ____wchar_701);// L869
extern __size_t_1  (__mbstowcs_706) (__wchar_t_2  * __restrict  ____pwcs_703, const char  * __restrict  ____s_704, __size_t_1  ____n_705);// L873:L874
extern __size_t_1  (__wcstombs_710) (char  * __restrict  ____s_707, const __wchar_t_2  * __restrict  ____pwcs_708, __size_t_1  ____n_709);// L876:L878
extern int  (__rpmatch_713) (const char  * (____response_711));// L887
extern int  (__rpmatch_712) (const char  * (____response_711));// L887
extern int  (__getsubopt_718) (char  * (* __restrict  ____optionp_714), char  * const  * __restrict  ____tokens_715, char  * (* __restrict  ____valuep_716));// L898:L901
extern int  (__getsubopt_717) (char  * (* __restrict  ____optionp_714), char  * const  * __restrict  ____tokens_715, char  * (* __restrict  ____valuep_716));// L898:L901
extern int  (__getloadavg_721) (double  ____loadavg_719[], int  ____nelem_720);// L950:L951
/* no function due to type errors in the function prototype */
extern char  * ((____realpath_chk_726) (const char  * __restrict  ____name_723, char  * __restrict  ____resolved_724, __size_t_1  ____resolvedlen_725));// L23:L25
extern char  * ((____realpath_alias_729) (const char  * __restrict  ____name_727, char  * __restrict  ____resolved_728));// L26:L28
extern char  * ((____realpath_chk_warn_733) (const char  * __restrict  ____name_730, char  * __restrict  ____resolved_731, __size_t_1  ____resolvedlen_732));// L29:L34
/* no function due to type errors in the function prototype */
extern int  (____ptsname_r_chk_741) (int  ____fd_737, char  * (____buf_738), __size_t_1  ____buflen_739, __size_t_1  ____nreal_740);// L52:L53
extern int  (____ptsname_r_alias_745) (int  ____fd_742, char  * (____buf_743), __size_t_1  ____buflen_744);// L54:L56
extern int  (____ptsname_r_chk_warn_750) (int  ____fd_746, char  * (____buf_747), __size_t_1  ____buflen_748, __size_t_1  ____nreal_749);// L57:L61
/* no function due to type errors in the function prototype */
extern int  (____wctomb_chk_758) (char  * (____s_755), __wchar_t_2  ____wchar_756, __size_t_1  ____buflen_757);// L77:L78
extern int  (____wctomb_alias_761) (char  * (____s_759), __wchar_t_2  ____wchar_760);// L79:L80
/* no function due to type errors in the function prototype */
extern __size_t_1  (____mbstowcs_chk_768) (__wchar_t_2  * __restrict  ____dst_764, const char  * __restrict  ____src_765, __size_t_1  ____len_766, __size_t_1  ____dstlen_767);// L98:L100
extern __size_t_1  (____mbstowcs_alias_772) (__wchar_t_2  * __restrict  ____dst_769, const char  * __restrict  ____src_770, __size_t_1  ____len_771);// L101:L104
extern __size_t_1  (____mbstowcs_chk_warn_777) (__wchar_t_2  * __restrict  ____dst_773, const char  * __restrict  ____src_774, __size_t_1  ____len_775, __size_t_1  ____dstlen_776);// L105:L110
/* no function due to type errors in the function prototype */
extern __size_t_1  (____wcstombs_chk_785) (char  * __restrict  ____dst_781, const __wchar_t_2  * __restrict  ____src_782, __size_t_1  ____len_783, __size_t_1  ____dstlen_784);// L130:L132
extern __size_t_1  (____wcstombs_alias_789) (char  * __restrict  ____dst_786, const __wchar_t_2  * __restrict  ____src_787, __size_t_1  ____len_788);// L133:L136
extern __size_t_1  (____wcstombs_chk_warn_794) (char  * __restrict  ____dst_790, const __wchar_t_2  * __restrict  ____src_791, __size_t_1  ____len_792, __size_t_1  ____dstlen_793);// L137:L141
/* no function due to type errors in the function prototype */
_Bool  (__IS_ERR_799) (const void  * (__ptr_798)) {

if (__static_condition_default_802) {

{// L13
{



return (  __ptr_798  == ( void  * ) - 1 ) ;// L14
}
}// L15


}
}
_Bool  (__IS_ERR_800) (const void  * (__ptr_798)) {

if (__static_condition_default_803) {

{// L13
{



return (  __ptr_798  == ( void  * ) - 1 ) ;// L14
}
}// L15


}
}
_Bool  (__IS_ERR_801) (const void  * (__ptr_798)) {

if (__static_condition_default_804) {

{// L13
{



return (  __ptr_798  == ( void  * ) - 1 ) ;// L14
}
}// L15


}
}
_Bool  (__IS_ERR_OR_NULL_806) (const void  * (__ptr_805)) {

{// L18
{



if (__static_condition_default_807) {
return !  __ptr_805  ||  __IS_ERR_799  ( __ptr_805 ) ;// L19
}
if (__static_condition_default_808) {
return !  __ptr_805  ||  __IS_ERR_800  ( __ptr_805 ) ;// L19
}
if (__static_condition_default_804) {
return !  __ptr_805  ||  __IS_ERR_801  ( __ptr_805 ) ;// L19
}
}
}// L20


}
static int  __some_int_809= 1;// L29
int  * ((__ip6_dst_lookup_flow_810) ()) {

if (__static_condition_default_811) {

{// L32
{



return &  __some_int_809  ;// L33
}
}// L34


}
}
void  (__sctp_v6_get_dst_816) () {

if (__static_condition_default_817) {

{// L37
{



int  * (__dst_812)= ( ( void  * ) 0 );// L38

if (__static_condition_default_813) {
__static_type_error("invalid declaration of dst under this presence condition");
}

if (__static_condition_default_818) {
 __dst_812  =  __ip6_dst_lookup_flow_810 ( ) ; // L39
}
if (__static_condition_default_819) {
__static_type_error("type error") ; // L39
}
if (__static_condition_default_820) {
if ( !  __IS_ERR_799  ( __dst_812 ) )// L40
{

{// L40
{



 __dst_812  = ( ( void  * ) 0 ) ; // L41:L395
}
}// L42
}
}
if (__static_condition_default_821) {
if ( !  __IS_ERR_800  ( __dst_812 ) )// L40
{

{// L40
{



 __dst_812  = ( ( void  * ) 0 ) ; // L41:L395
}
}// L42
}
}
if (__static_condition_default_822) {
__static_type_error("invalid type found in if statement");
}
if (__static_condition_default_823) {
if ( !  __IS_ERR_799  ( __dst_812 ) )// L43
{

{// L43
{



char  * (__rt_814)= ( char  * )  __dst_812 ;// L44

if (__static_condition_default_824) {
 ; // L45
}
if (__static_condition_default_825) {
( ( *  __rt_814  ) ++ ) ; // L23:L45
}
}
}// L46
}
}
if (__static_condition_default_826) {
if ( !  __IS_ERR_800  ( __dst_812 ) )// L43
{

{// L43
{



char  * (__rt_814)= ( char  * )  __dst_812 ;// L44

if (__static_condition_default_827) {
 ; // L45
}
if (__static_condition_default_828) {
( ( *  __rt_814  ) ++ ) ; // L23:L45
}
}
}// L46
}
}
if (__static_condition_default_829) {
__static_type_error("invalid type found in if statement");
}
}
}// L47


}
}
int  (__main_830) () {

if (__static_condition_default_832) {

{// L51
{



return 0 ;// L55
}
}// L56


}
}
int  (__main_831) () {

if (__static_condition_default_833) {

{// L51
{



 __sctp_v6_get_dst_816 ( ) ; // L53
return 0 ;// L55
}
}// L56


}
}

