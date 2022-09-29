#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_409;
extern const bool __static_condition_default_824;
extern const bool __static_condition_default_307;
extern const bool __static_condition_default_593;
extern const bool __static_condition_default_643;
extern const bool __static_condition_default_825;
extern const bool __static_condition_default_281;
extern const bool __static_condition_default_339;
extern const bool __static_condition_default_302;
extern const bool __static_condition_default_440;
extern const bool __static_condition_default_832;
extern const bool __static_condition_default_635;
extern const bool __static_condition_default_431;
extern const bool __static_condition_default_831;
extern const bool __static_condition_default_641;
extern const bool __static_condition_default_813;
extern const bool __static_condition_default_263;
extern const bool __static_condition_default_322;
extern const bool __static_condition_default_618;
extern const bool __static_condition_default_820;
extern const bool __static_condition_default_826;
extern const bool __static_condition_default_446;
extern const bool __static_condition_default_616;
extern const bool __static_condition_default_814;
extern const bool __static_condition_default_375;
extern const bool __static_condition_default_363;
extern const bool __static_condition_default_816;
extern const bool __static_condition_default_257;
extern const bool __static_condition_default_293;
extern const bool __static_condition_default_319;
extern const bool __static_condition_default_74;
extern const bool __static_condition_default_392;
extern const bool __static_condition_default_251;
extern const bool __static_condition_default_266;
extern const bool __static_condition_default_818;
extern const bool __static_condition_default_822;
extern const bool __static_condition_default_272;
extern const bool __static_condition_default_443;
extern const bool __static_condition_default_248;
extern const bool __static_condition_default_275;
extern const bool __static_condition_default_821;
extern const bool __static_condition_default_637;
extern const bool __static_condition_default_278;
extern const bool __static_condition_default_608;
extern const bool __static_condition_default_833;
extern const bool __static_condition_default_81;
extern const bool __static_condition_default_290;
extern const bool __static_condition_default_408;
extern const bool __static_condition_default_434;
extern const bool __static_condition_default_437;
extern const bool __static_condition_default_750;
extern const bool __static_condition_default_313;
extern const bool __static_condition_default_296;
extern const bool __static_condition_default_393;
extern const bool __static_condition_default_284;
extern const bool __static_condition_default_428;
extern const bool __static_condition_default_229;
extern const bool __static_condition_default_310;
extern const bool __static_condition_default_355;
extern const bool __static_condition_default_260;
extern const bool __static_condition_default_299;
extern const bool __static_condition_default_609;
extern const bool __static_condition_default_817;
extern const bool __static_condition_default_254;
extern const bool __static_condition_default_269;
extern const bool __static_condition_default_287;
extern const bool __static_condition_default_366;
extern const bool __static_condition_default_815;
extern const bool __static_condition_default_595;
extern const bool __static_condition_default_316;
void __static_initializer_default() {
__static_renaming("____assert_fail_4", "__assert_fail");
__static_renaming("____assert_perror_fail_9", "__assert_perror_fail");
__static_renaming("____assert_13", "__assert");
__static_renaming("__ptrdiff_t_14", "ptrdiff_t");
__static_renaming("__size_t_15", "size_t");
__static_renaming("__wchar_t_16", "wchar_t");
__static_renaming("__idtype_t_22", "idtype_t");
__static_renaming("____u_char_23", "__u_char");
__static_renaming("____u_short_24", "__u_short");
__static_renaming("____u_int_25", "__u_int");
__static_renaming("____u_long_26", "__u_long");
__static_renaming("____int8_t_27", "__int8_t");
__static_renaming("____uint8_t_28", "__uint8_t");
__static_renaming("____int16_t_29", "__int16_t");
__static_renaming("____uint16_t_30", "__uint16_t");
__static_renaming("____int32_t_31", "__int32_t");
__static_renaming("____uint32_t_32", "__uint32_t");
__static_renaming("____int64_t_33", "__int64_t");
__static_renaming("____uint64_t_34", "__uint64_t");
__static_renaming("____quad_t_35", "__quad_t");
__static_renaming("____u_quad_t_36", "__u_quad_t");
__static_renaming("____dev_t_37", "__dev_t");
__static_renaming("____uid_t_38", "__uid_t");
__static_renaming("____gid_t_39", "__gid_t");
__static_renaming("____ino_t_40", "__ino_t");
__static_renaming("____ino64_t_41", "__ino64_t");
__static_renaming("____mode_t_42", "__mode_t");
__static_renaming("____nlink_t_43", "__nlink_t");
__static_renaming("____off_t_44", "__off_t");
__static_renaming("____off64_t_45", "__off64_t");
__static_renaming("____pid_t_46", "__pid_t");
__static_renaming("____fsid_t_50", "__fsid_t");
__static_renaming("____clock_t_51", "__clock_t");
__static_renaming("____rlim_t_52", "__rlim_t");
__static_renaming("____rlim64_t_53", "__rlim64_t");
__static_renaming("____id_t_54", "__id_t");
__static_renaming("____time_t_55", "__time_t");
__static_renaming("____useconds_t_56", "__useconds_t");
__static_renaming("____suseconds_t_57", "__suseconds_t");
__static_renaming("____daddr_t_58", "__daddr_t");
__static_renaming("____key_t_59", "__key_t");
__static_renaming("____clockid_t_60", "__clockid_t");
__static_renaming("____timer_t_61", "__timer_t");
__static_renaming("____blksize_t_62", "__blksize_t");
__static_renaming("____blkcnt_t_63", "__blkcnt_t");
__static_renaming("____blkcnt64_t_64", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_65", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_66", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_67", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_68", "__fsfilcnt64_t");
__static_renaming("____fsword_t_69", "__fsword_t");
__static_renaming("____ssize_t_70", "__ssize_t");
__static_renaming("____syscall_slong_t_71", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_72", "__syscall_ulong_t");
__static_renaming("____loff_t_73", "__loff_t");
__static_renaming("____qaddr_t_75", "__qaddr_t");
__static_renaming("____caddr_t_76", "__caddr_t");
__static_renaming("____intptr_t_77", "__intptr_t");
__static_renaming("____socklen_t_78", "__socklen_t");
__static_renaming("____bswap_32_80", "__bswap_32");
__static_renaming("____bswap_64_83", "__bswap_64");
__static_renaming("____WAIT_STATUS_103", "__WAIT_STATUS");
__static_renaming("__div_t_108", "div_t");
__static_renaming("__ldiv_t_113", "ldiv_t");
__static_renaming("__lldiv_t_118", "lldiv_t");
__static_renaming("____ctype_get_mb_cur_max_119", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_120", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_121", "__ctype_get_mb_cur_max");
__static_renaming("____ctype_get_mb_cur_max_122", "__ctype_get_mb_cur_max");
__static_renaming("__atof_124", "atof");
__static_renaming("__atof_125", "atof");
__static_renaming("__atoi_127", "atoi");
__static_renaming("__atoi_128", "atoi");
__static_renaming("__atol_130", "atol");
__static_renaming("__atol_131", "atol");
__static_renaming("__atoll_133", "atoll");
__static_renaming("__atoll_134", "atoll");
__static_renaming("__strtod_137", "strtod");
__static_renaming("__strtof_140", "strtof");
__static_renaming("__strtold_143", "strtold");
__static_renaming("__strtol_147", "strtol");
__static_renaming("__strtoul_151", "strtoul");
__static_renaming("__strtoq_155", "strtoq");
__static_renaming("__strtouq_159", "strtouq");
__static_renaming("__strtoll_163", "strtoll");
__static_renaming("__strtoll_164", "strtoll");
__static_renaming("__strtoull_168", "strtoull");
__static_renaming("__l64a_173", "l64a");
__static_renaming("__l64a_174", "l64a");
__static_renaming("__a64l_176", "a64l");
__static_renaming("__a64l_177", "a64l");
__static_renaming("____u_char_178", "__u_char");
__static_renaming("____u_short_179", "__u_short");
__static_renaming("____u_int_180", "__u_int");
__static_renaming("____u_long_181", "__u_long");
__static_renaming("____int8_t_182", "__int8_t");
__static_renaming("____uint8_t_183", "__uint8_t");
__static_renaming("____int16_t_184", "__int16_t");
__static_renaming("____uint16_t_185", "__uint16_t");
__static_renaming("____int32_t_186", "__int32_t");
__static_renaming("____uint32_t_187", "__uint32_t");
__static_renaming("____int64_t_188", "__int64_t");
__static_renaming("____uint64_t_189", "__uint64_t");
__static_renaming("____quad_t_190", "__quad_t");
__static_renaming("____u_quad_t_191", "__u_quad_t");
__static_renaming("____dev_t_192", "__dev_t");
__static_renaming("____uid_t_193", "__uid_t");
__static_renaming("____gid_t_194", "__gid_t");
__static_renaming("____ino_t_195", "__ino_t");
__static_renaming("____ino64_t_196", "__ino64_t");
__static_renaming("____mode_t_197", "__mode_t");
__static_renaming("____nlink_t_198", "__nlink_t");
__static_renaming("____off_t_199", "__off_t");
__static_renaming("____off64_t_200", "__off64_t");
__static_renaming("____pid_t_201", "__pid_t");
__static_renaming("____fsid_t_205", "__fsid_t");
__static_renaming("____clock_t_206", "__clock_t");
__static_renaming("____rlim_t_207", "__rlim_t");
__static_renaming("____rlim64_t_208", "__rlim64_t");
__static_renaming("____id_t_209", "__id_t");
__static_renaming("____time_t_210", "__time_t");
__static_renaming("____useconds_t_211", "__useconds_t");
__static_renaming("____suseconds_t_212", "__suseconds_t");
__static_renaming("____daddr_t_213", "__daddr_t");
__static_renaming("____key_t_214", "__key_t");
__static_renaming("____clockid_t_215", "__clockid_t");
__static_renaming("____timer_t_216", "__timer_t");
__static_renaming("____blksize_t_217", "__blksize_t");
__static_renaming("____blkcnt_t_218", "__blkcnt_t");
__static_renaming("____blkcnt64_t_219", "__blkcnt64_t");
__static_renaming("____fsblkcnt_t_220", "__fsblkcnt_t");
__static_renaming("____fsblkcnt64_t_221", "__fsblkcnt64_t");
__static_renaming("____fsfilcnt_t_222", "__fsfilcnt_t");
__static_renaming("____fsfilcnt64_t_223", "__fsfilcnt64_t");
__static_renaming("____fsword_t_224", "__fsword_t");
__static_renaming("____ssize_t_225", "__ssize_t");
__static_renaming("____syscall_slong_t_226", "__syscall_slong_t");
__static_renaming("____syscall_ulong_t_227", "__syscall_ulong_t");
__static_renaming("____loff_t_228", "__loff_t");
__static_renaming("____qaddr_t_230", "__qaddr_t");
__static_renaming("____caddr_t_231", "__caddr_t");
__static_renaming("____intptr_t_232", "__intptr_t");
__static_renaming("____socklen_t_233", "__socklen_t");
__static_renaming("__u_char_234", "u_char");
__static_renaming("__u_char_235", "u_char");
__static_renaming("__u_short_236", "u_short");
__static_renaming("__u_short_237", "u_short");
__static_renaming("__u_int_238", "u_int");
__static_renaming("__u_int_239", "u_int");
__static_renaming("__u_long_240", "u_long");
__static_renaming("__u_long_241", "u_long");
__static_renaming("__quad_t_242", "quad_t");
__static_renaming("__quad_t_243", "quad_t");
__static_renaming("__u_quad_t_244", "u_quad_t");
__static_renaming("__u_quad_t_245", "u_quad_t");
__static_renaming("__fsid_t_246", "fsid_t");
__static_renaming("__fsid_t_247", "fsid_t");
__static_renaming("__loff_t_249", "loff_t");
__static_renaming("__loff_t_250", "loff_t");
__static_renaming("__loff_t_252", "loff_t");
__static_renaming("__loff_t_253", "loff_t");
__static_renaming("__ino_t_255", "ino_t");
__static_renaming("__ino_t_256", "ino_t");
__static_renaming("__ino_t_258", "ino_t");
__static_renaming("__ino_t_259", "ino_t");
__static_renaming("__dev_t_261", "dev_t");
__static_renaming("__dev_t_262", "dev_t");
__static_renaming("__gid_t_264", "gid_t");
__static_renaming("__gid_t_265", "gid_t");
__static_renaming("__gid_t_267", "gid_t");
__static_renaming("__gid_t_268", "gid_t");
__static_renaming("__mode_t_270", "mode_t");
__static_renaming("__mode_t_271", "mode_t");
__static_renaming("__nlink_t_273", "nlink_t");
__static_renaming("__nlink_t_274", "nlink_t");
__static_renaming("__uid_t_276", "uid_t");
__static_renaming("__uid_t_277", "uid_t");
__static_renaming("__uid_t_279", "uid_t");
__static_renaming("__uid_t_280", "uid_t");
__static_renaming("__off_t_282", "off_t");
__static_renaming("__off_t_283", "off_t");
__static_renaming("__off_t_285", "off_t");
__static_renaming("__off_t_286", "off_t");
__static_renaming("__pid_t_288", "pid_t");
__static_renaming("__pid_t_289", "pid_t");
__static_renaming("__pid_t_291", "pid_t");
__static_renaming("__pid_t_292", "pid_t");
__static_renaming("__id_t_294", "id_t");
__static_renaming("__id_t_295", "id_t");
__static_renaming("__ssize_t_297", "ssize_t");
__static_renaming("__ssize_t_298", "ssize_t");
__static_renaming("__daddr_t_300", "daddr_t");
__static_renaming("__daddr_t_301", "daddr_t");
__static_renaming("__caddr_t_303", "caddr_t");
__static_renaming("__caddr_t_304", "caddr_t");
__static_renaming("__key_t_305", "key_t");
__static_renaming("__key_t_306", "key_t");
__static_renaming("__key_t_308", "key_t");
__static_renaming("__key_t_309", "key_t");
__static_renaming("__clock_t_311", "clock_t");
__static_renaming("__clock_t_312", "clock_t");
__static_renaming("__time_t_314", "time_t");
__static_renaming("__time_t_315", "time_t");
__static_renaming("__clockid_t_317", "clockid_t");
__static_renaming("__clockid_t_318", "clockid_t");
__static_renaming("__timer_t_320", "timer_t");
__static_renaming("__timer_t_321", "timer_t");
__static_renaming("__ulong_323", "ulong");
__static_renaming("__ulong_324", "ulong");
__static_renaming("__ulong_325", "ulong");
__static_renaming("__ushort_326", "ushort");
__static_renaming("__uint_327", "uint");
__static_renaming("__int8_t_328", "int8_t");
__static_renaming("__int16_t_329", "int16_t");
__static_renaming("__int32_t_330", "int32_t");
__static_renaming("__int64_t_331", "int64_t");
__static_renaming("__u_int8_t_332", "u_int8_t");
__static_renaming("__u_int16_t_333", "u_int16_t");
__static_renaming("__u_int32_t_334", "u_int32_t");
__static_renaming("__u_int64_t_335", "u_int64_t");
__static_renaming("__register_t_336", "register_t");
__static_renaming("____bswap_32_338", "__bswap_32");
__static_renaming("____bswap_64_341", "__bswap_64");
__static_renaming("____sig_atomic_t_342", "__sig_atomic_t");
__static_renaming("____sigset_t_346", "__sigset_t");
__static_renaming("__sigset_t_347", "sigset_t");
__static_renaming("__suseconds_t_364", "suseconds_t");
__static_renaming("__suseconds_t_365", "suseconds_t");
__static_renaming("____fd_mask_367", "__fd_mask");
__static_renaming("____fd_mask_368", "__fd_mask");
__static_renaming("__fd_set_376", "fd_set");
__static_renaming("__fd_mask_377", "fd_mask");
__static_renaming("__fd_mask_378", "fd_mask");
__static_renaming("__select_390", "select");
__static_renaming("__select_391", "select");
__static_renaming("__pselect_406", "pselect");
__static_renaming("__pselect_407", "pselect");
__static_renaming("____fdelt_chk_411", "__fdelt_chk");
__static_renaming("____fdelt_warn_413", "__fdelt_warn");
__static_renaming("__gnu_dev_major_415", "gnu_dev_major");
__static_renaming("__gnu_dev_major_416", "gnu_dev_major");
__static_renaming("__gnu_dev_minor_418", "gnu_dev_minor");
__static_renaming("__gnu_dev_makedev_421", "gnu_dev_makedev");
__static_renaming("__blksize_t_426", "blksize_t");
__static_renaming("__blksize_t_427", "blksize_t");
__static_renaming("__blkcnt_t_429", "blkcnt_t");
__static_renaming("__blkcnt_t_430", "blkcnt_t");
__static_renaming("__fsblkcnt_t_432", "fsblkcnt_t");
__static_renaming("__fsblkcnt_t_433", "fsblkcnt_t");
__static_renaming("__blkcnt_t_435", "blkcnt_t");
__static_renaming("__blkcnt_t_436", "blkcnt_t");
__static_renaming("__fsblkcnt_t_438", "fsblkcnt_t");
__static_renaming("__fsblkcnt_t_439", "fsblkcnt_t");
__static_renaming("__fsfilcnt_t_441", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_442", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_444", "fsfilcnt_t");
__static_renaming("__fsfilcnt_t_445", "fsfilcnt_t");
__static_renaming("__pthread_t_447", "pthread_t");
__static_renaming("__pthread_attr_t_451", "pthread_attr_t");
__static_renaming("____pthread_list_t_456", "__pthread_list_t");
__static_renaming("____pthread_list_t_457", "__pthread_list_t");
__static_renaming("__pthread_mutex_t_473", "pthread_mutex_t");
__static_renaming("__pthread_mutexattr_t_478", "pthread_mutexattr_t");
__static_renaming("__rand_479", "rand");
__static_renaming("__srand_481", "srand");
__static_renaming("__rand_r_483", "rand_r");
__static_renaming("__drand48_484", "drand48");
__static_renaming("__erand48_486", "erand48");
__static_renaming("__lrand48_487", "lrand48");
__static_renaming("__nrand48_489", "nrand48");
__static_renaming("__mrand48_490", "mrand48");
__static_renaming("__jrand48_492", "jrand48");
__static_renaming("__srand48_494", "srand48");
__static_renaming("__seed48_496", "seed48");
__static_renaming("__lcong48_498", "lcong48");
__static_renaming("__malloc_500", "malloc");
__static_renaming("__malloc_501", "malloc");
__static_renaming("__calloc_504", "calloc");
__static_renaming("__calloc_505", "calloc");
__static_renaming("__realloc_508", "realloc");
__static_renaming("__free_510", "free");
__static_renaming("__cfree_512", "cfree");
__static_renaming("__alloca_514", "alloca");
__static_renaming("__valloc_516", "valloc");
__static_renaming("__valloc_517", "valloc");
__static_renaming("__posix_memalign_521", "posix_memalign");
__static_renaming("__posix_memalign_522", "posix_memalign");
__static_renaming("__aligned_alloc_525", "aligned_alloc");
__static_renaming("__aligned_alloc_526", "aligned_alloc");
__static_renaming("__aligned_alloc_527", "aligned_alloc");
__static_renaming("__aligned_alloc_528", "aligned_alloc");
__static_renaming("__abort_529", "abort");
__static_renaming("__atexit_531", "atexit");
__static_renaming("__at_quick_exit_533", "at_quick_exit");
__static_renaming("__on_exit_538", "on_exit");
__static_renaming("__exit_540", "exit");
__static_renaming("__exit_541", "exit");
__static_renaming("__quick_exit_543", "quick_exit");
__static_renaming("___Exit_545", "_Exit");
__static_renaming("__getenv_547", "getenv");
__static_renaming("__getenv_548", "getenv");
__static_renaming("__putenv_550", "putenv");
__static_renaming("__setenv_554", "setenv");
__static_renaming("__unsetenv_556", "unsetenv");
__static_renaming("__clearenv_557", "clearenv");
__static_renaming("__mktemp_559", "mktemp");
__static_renaming("__mkstemp_562", "mkstemp");
__static_renaming("__mkstemp_563", "mkstemp");
__static_renaming("__mkstemp_564", "mkstemp");
__static_renaming("__mkstemp_565", "mkstemp");
__static_renaming("__mkstemps_570", "mkstemps");
__static_renaming("__mkstemps_571", "mkstemps");
__static_renaming("__mkstemps_572", "mkstemps");
__static_renaming("__mkstemps_573", "mkstemps");
__static_renaming("__mkdtemp_575", "mkdtemp");
__static_renaming("__mkdtemp_576", "mkdtemp");
__static_renaming("__system_578", "system");
__static_renaming("__system_579", "system");
__static_renaming("__system_580", "system");
__static_renaming("__system_581", "system");
__static_renaming("__realpath_584", "realpath");
__static_renaming("__realpath_585", "realpath");
__static_renaming("____compar_fn_t_586", "__compar_fn_t");
__static_renaming("__bsearch_594", "bsearch");
__static_renaming("__bsearch_596", "bsearch");
__static_renaming("____l_603", "__l");
__static_renaming("____u_604", "__u");
__static_renaming("____idx_605", "__idx");
__static_renaming("____p_606", "__p");
__static_renaming("____comparison_607", "__comparison");
__static_renaming("__qsort_615", "qsort");
__static_renaming("__qsort_617", "qsort");
__static_renaming("__abs_620", "abs");
__static_renaming("__abs_621", "abs");
__static_renaming("__labs_623", "labs");
__static_renaming("__labs_624", "labs");
__static_renaming("__llabs_626", "llabs");
__static_renaming("__llabs_627", "llabs");
__static_renaming("__div_630", "div");
__static_renaming("__div_631", "div");
__static_renaming("__ldiv_634", "ldiv");
__static_renaming("__ldiv_636", "ldiv");
__static_renaming("__lldiv_640", "lldiv");
__static_renaming("__lldiv_642", "lldiv");
__static_renaming("__ecvt_648", "ecvt");
__static_renaming("__ecvt_649", "ecvt");
__static_renaming("__fcvt_654", "fcvt");
__static_renaming("__fcvt_655", "fcvt");
__static_renaming("__gcvt_659", "gcvt");
__static_renaming("__gcvt_660", "gcvt");
__static_renaming("__qecvt_665", "qecvt");
__static_renaming("__qecvt_666", "qecvt");
__static_renaming("__qfcvt_671", "qfcvt");
__static_renaming("__qfcvt_672", "qfcvt");
__static_renaming("__qgcvt_676", "qgcvt");
__static_renaming("__qgcvt_677", "qgcvt");
__static_renaming("__ecvt_r_684", "ecvt_r");
__static_renaming("__fcvt_r_691", "fcvt_r");
__static_renaming("__qecvt_r_698", "qecvt_r");
__static_renaming("__qfcvt_r_705", "qfcvt_r");
__static_renaming("__mblen_708", "mblen");
__static_renaming("__mblen_709", "mblen");
__static_renaming("__mbtowc_713", "mbtowc");
__static_renaming("__wctomb_716", "wctomb");
__static_renaming("__mbstowcs_720", "mbstowcs");
__static_renaming("__wcstombs_724", "wcstombs");
__static_renaming("__rpmatch_726", "rpmatch");
__static_renaming("__rpmatch_727", "rpmatch");
__static_renaming("__getsubopt_731", "getsubopt");
__static_renaming("__getsubopt_732", "getsubopt");
__static_renaming("__getloadavg_735", "getloadavg");
__static_renaming("____realpath_chk_740", "__realpath_chk");
__static_renaming("____realpath_alias_743", "__realpath_alias");
__static_renaming("____realpath_chk_warn_747", "__realpath_chk_warn");
__static_renaming("____ptsname_r_chk_755", "__ptsname_r_chk");
__static_renaming("____ptsname_r_alias_759", "__ptsname_r_alias");
__static_renaming("____ptsname_r_chk_warn_764", "__ptsname_r_chk_warn");
__static_renaming("____wctomb_chk_772", "__wctomb_chk");
__static_renaming("____wctomb_alias_775", "__wctomb_alias");
__static_renaming("____mbstowcs_chk_782", "__mbstowcs_chk");
__static_renaming("____mbstowcs_alias_786", "__mbstowcs_alias");
__static_renaming("____mbstowcs_chk_warn_791", "__mbstowcs_chk_warn");
__static_renaming("____wcstombs_chk_799", "__wcstombs_chk");
__static_renaming("____wcstombs_alias_803", "__wcstombs_alias");
__static_renaming("____wcstombs_chk_warn_808", "__wcstombs_chk_warn");
__static_renaming("__vlan_dev_real_dev_812", "vlan_dev_real_dev");
__static_renaming("__vlan_dev_real_dev_819", "vlan_dev_real_dev");
__static_renaming("__ocrdma_inet6addr_event_823", "ocrdma_inet6addr_event");
__static_renaming("__main_829", "main");
__static_renaming("__main_830", "main");

__static_condition_renaming("__static_condition_default_74", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && !(defined _SYS_WAIT_H) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_81", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && !(defined _SYS_WAIT_H)");
__static_condition_renaming("__static_condition_default_229", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _SYS_WAIT_H) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_248", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_251", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_254", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __u_char_defined)");
__static_condition_renaming("__static_condition_default_257", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined)");
__static_condition_renaming("__static_condition_default_260", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ino_t_defined)");
__static_condition_renaming("__static_condition_default_263", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_266", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_269", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __dev_t_defined)");
__static_condition_renaming("__static_condition_default_272", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_275", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_278", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_281", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __nlink_t_defined)");
__static_condition_renaming("__static_condition_default_284", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_287", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_290", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_293", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __off_t_defined)");
__static_condition_renaming("__static_condition_default_296", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __id_t_defined)");
__static_condition_renaming("__static_condition_default_299", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __ssize_t_defined)");
__static_condition_renaming("__static_condition_default_302", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_307", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_310", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __daddr_t_defined)");
__static_condition_renaming("__static_condition_default_313", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __clock_t_defined)");
__static_condition_renaming("__static_condition_default_316", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __time_t_defined)");
__static_condition_renaming("__static_condition_default_319", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __clockid_t_defined)");
__static_condition_renaming("__static_condition_default_322", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timer_t_defined)");
__static_condition_renaming("__static_condition_default_339", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _SYS_WAIT_H)");
__static_condition_renaming("__static_condition_default_355", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_363", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_366", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __suseconds_t_defined)");
__static_condition_renaming("__static_condition_default_375", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_392", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_393", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined _STRUCT_TIMEVAL)");
__static_condition_renaming("__static_condition_default_408", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_409", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && (defined __timespec_defined)");
__static_condition_renaming("__static_condition_default_428", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blksize_t_defined)");
__static_condition_renaming("__static_condition_default_431", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined)");
__static_condition_renaming("__static_condition_default_434", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_437", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) && !(defined __blkcnt_t_defined)");
__static_condition_renaming("__static_condition_default_440", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_443", "!(defined __STRICT_ANSI__) && !(defined _FILE_OFFSET_BITS) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H) || !(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && !(_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_446", "!(defined __STRICT_ANSI__) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined _BITS_TYPESIZES_H)");
__static_condition_renaming("__static_condition_default_593", "!(defined _FORTIFY_SOURCE) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_595", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_608", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && !(defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_609", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_616", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && !(defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_618", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __USE_EXTERN_INLINES) && (defined __COMPAR_FN_T)");
__static_condition_renaming("__static_condition_default_635", "!(defined _FORTIFY_SOURCE) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_637", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __ldiv_t_defined)");
__static_condition_renaming("__static_condition_default_641", "!(defined _FORTIFY_SOURCE) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && !(_FORTIFY_SOURCE > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && !(defined __OPTIMIZE__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined) || (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && !(__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_643", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined __lldiv_t_defined)");
__static_condition_renaming("__static_condition_default_750", "(defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc)");
__static_condition_renaming("__static_condition_default_813", "!(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_814", "(defined NDEBUG) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_815", "!(defined NDEBUG) && !(defined _ASSERT_H_DECLS) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_816", "!(defined NDEBUG) && (defined _ASSERT_H_DECLS) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_817", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_818", "!(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && !(defined CONFIG_VLAN_8021Q) || (defined _STDLIB_H) && !(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_820", "(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_821", "!(defined _STDLIB_H) && !(defined __need_malloc_and_calloc) && (defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_822", "!(defined _STDLIB_H) && (defined __need_malloc_and_calloc) && (defined CONFIG_VLAN_8021Q) || (defined _STDLIB_H) && (defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_824", "!(defined CONFIG_VLAN_8021Q) && (defined CONFIG_IPV6) || (defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_825", "!(defined CONFIG_VLAN_8021Q) && (defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_826", "(defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_831", "!(defined CONFIG_VLAN_8021Q) && !(defined CONFIG_IPV6)");
__static_condition_renaming("__static_condition_default_832", "!(defined CONFIG_VLAN_8021Q) && (defined CONFIG_IPV6) || (defined CONFIG_VLAN_8021Q)");
__static_condition_renaming("__static_condition_default_833", "!(defined __STRICT_ANSI__) && !(defined _STDLIB_H) && !(defined __need_malloc_and_calloc)");

if (__static_condition_default_833) {
__static_parse_error("Unable to parse");
}
};
typedef long int  __ptrdiff_t_14;// L143:L324
typedef long unsigned int  __size_t_15;// L177:L209
typedef int  __wchar_t_16;// L243:L321
enum ____anonymous_tag_20_21 {
__P_ALL_17,
__P_PID_18,
__P_PGID_19,
};
typedef enum ____anonymous_tag_20_21  __idtype_t_22;// L50:L55
typedef unsigned char  ____u_char_23;// L30
typedef unsigned short int  ____u_short_24;// L31
typedef unsigned int  ____u_int_25;// L32
typedef unsigned long int  ____u_long_26;// L33
typedef signed char  ____int8_t_27;// L36
typedef unsigned char  ____uint8_t_28;// L37
typedef signed short int  ____int16_t_29;// L38
typedef unsigned short int  ____uint16_t_30;// L39
typedef signed int  ____int32_t_31;// L40
typedef unsigned int  ____uint32_t_32;// L41
typedef signed long int  ____int64_t_33;// L43
typedef unsigned long int  ____uint64_t_34;// L44
typedef long int  ____quad_t_35;// L52
typedef unsigned long int  ____u_quad_t_36;// L53
typedef unsigned long int  ____dev_t_37;// L109:L124
typedef unsigned int  ____uid_t_38;// L92:L125
typedef unsigned int  ____gid_t_39;// L92:L126
typedef unsigned long int  ____ino_t_40;// L94:L127
typedef unsigned long int  ____ino64_t_41;// L109:L128
typedef unsigned int  ____mode_t_42;// L92:L129
typedef unsigned long int  ____nlink_t_43;// L94:L130
typedef long int  ____off_t_44;// L93:L131
typedef long int  ____off64_t_45;// L108:L132
typedef int  ____pid_t_46;// L91:L133
struct ____anonymous_tag_47_48 {
int  ____val_49[2];// L72
};
typedef struct ____anonymous_tag_47_48  ____fsid_t_50;// L72:L134
typedef long int  ____clock_t_51;// L93:L135
typedef unsigned long int  ____rlim_t_52;// L94:L136
typedef unsigned long int  ____rlim64_t_53;// L109:L137
typedef unsigned int  ____id_t_54;// L92:L138
typedef long int  ____time_t_55;// L93:L139
typedef unsigned int  ____useconds_t_56;// L92:L140
typedef long int  ____suseconds_t_57;// L93:L141
typedef int  ____daddr_t_58;// L91:L143
typedef int  ____key_t_59;// L91:L144
typedef int  ____clockid_t_60;// L91:L147
typedef void  * (____timer_t_61);// L70:L150
typedef long int  ____blksize_t_62;// L93:L153
typedef long int  ____blkcnt_t_63;// L93:L158
typedef long int  ____blkcnt64_t_64;// L108:L159
typedef unsigned long int  ____fsblkcnt_t_65;// L94:L162
typedef unsigned long int  ____fsblkcnt64_t_66;// L109:L163
typedef unsigned long int  ____fsfilcnt_t_67;// L94:L166
typedef unsigned long int  ____fsfilcnt64_t_68;// L109:L167
typedef long int  ____fsword_t_69;// L93:L170
typedef long int  ____ssize_t_70;// L110:L172
typedef long int  ____syscall_slong_t_71;// L93:L175
typedef unsigned long int  ____syscall_ulong_t_72;// L94:L177
typedef ____off64_t_45  ____loff_t_73;// L181
typedef ____quad_t_35  * (____qaddr_t_75);// L182
typedef char  * (____caddr_t_76);// L183
typedef long int  ____intptr_t_77;// L110:L186
typedef unsigned int  ____socklen_t_78;// L92:L189
struct ____anonymous_tag_84_85 {
unsigned int  ____w_termsig_86 : 7;// L72
unsigned int  ____w_coredump_87 : 1;// L73
unsigned int  ____w_retcode_88 : 8;// L74
unsigned int  __anon_id_0_89 : 16;// L75
};
struct ____anonymous_tag_90_91 {
unsigned int  ____w_stopval_92 : 8;// L87
unsigned int  ____w_stopsig_93 : 8;// L88
unsigned int  __anon_id_1_94 : 16;// L89
};
union __wait_95 {
int  __w_status_96;// L68
struct ____anonymous_tag_84_85  ____wait_terminated_97;// L69
struct ____anonymous_tag_90_91  ____wait_stopped_98;// L84
};
union ____anonymous_tag_99_100 {
union __wait_95  * (____uptr_101);// L69
int  * (____iptr_102);// L70
};
typedef union ____anonymous_tag_99_100  ____WAIT_STATUS_103;// L67:L71
struct ____anonymous_tag_104_105 {
int  __quot_106;// L99
int  __rem_107;// L100
};
typedef struct ____anonymous_tag_104_105  __div_t_108;// L97:L101
struct ____anonymous_tag_109_110 {
long int  __quot_111;// L107
long int  __rem_112;// L108
};
typedef struct ____anonymous_tag_109_110  __ldiv_t_113;// L105:L109
struct ____anonymous_tag_114_115 {
long long int  __quot_116;// L119
long long int  __rem_117;// L120
};
typedef struct ____anonymous_tag_114_115  __lldiv_t_118;// L117:L121
typedef unsigned char  ____u_char_178;// L30
typedef unsigned short int  ____u_short_179;// L31
typedef unsigned int  ____u_int_180;// L32
typedef unsigned long int  ____u_long_181;// L33
typedef signed char  ____int8_t_182;// L36
typedef unsigned char  ____uint8_t_183;// L37
typedef signed short int  ____int16_t_184;// L38
typedef unsigned short int  ____uint16_t_185;// L39
typedef signed int  ____int32_t_186;// L40
typedef unsigned int  ____uint32_t_187;// L41
typedef signed long int  ____int64_t_188;// L43
typedef unsigned long int  ____uint64_t_189;// L44
typedef long int  ____quad_t_190;// L52
typedef unsigned long int  ____u_quad_t_191;// L53
typedef unsigned long int  ____dev_t_192;// L109:L124
typedef unsigned int  ____uid_t_193;// L92:L125
typedef unsigned int  ____gid_t_194;// L92:L126
typedef unsigned long int  ____ino_t_195;// L94:L127
typedef unsigned long int  ____ino64_t_196;// L109:L128
typedef unsigned int  ____mode_t_197;// L92:L129
typedef unsigned long int  ____nlink_t_198;// L94:L130
typedef long int  ____off_t_199;// L93:L131
typedef long int  ____off64_t_200;// L108:L132
typedef int  ____pid_t_201;// L91:L133
struct ____anonymous_tag_202_203 {
int  ____val_204[2];// L72
};
typedef struct ____anonymous_tag_202_203  ____fsid_t_205;// L72:L134
typedef long int  ____clock_t_206;// L93:L135
typedef unsigned long int  ____rlim_t_207;// L94:L136
typedef unsigned long int  ____rlim64_t_208;// L109:L137
typedef unsigned int  ____id_t_209;// L92:L138
typedef long int  ____time_t_210;// L93:L139
typedef unsigned int  ____useconds_t_211;// L92:L140
typedef long int  ____suseconds_t_212;// L93:L141
typedef int  ____daddr_t_213;// L91:L143
typedef int  ____key_t_214;// L91:L144
typedef int  ____clockid_t_215;// L91:L147
typedef void  * (____timer_t_216);// L70:L150
typedef long int  ____blksize_t_217;// L93:L153
typedef long int  ____blkcnt_t_218;// L93:L158
typedef long int  ____blkcnt64_t_219;// L108:L159
typedef unsigned long int  ____fsblkcnt_t_220;// L94:L162
typedef unsigned long int  ____fsblkcnt64_t_221;// L109:L163
typedef unsigned long int  ____fsfilcnt_t_222;// L94:L166
typedef unsigned long int  ____fsfilcnt64_t_223;// L109:L167
typedef long int  ____fsword_t_224;// L93:L170
typedef long int  ____ssize_t_225;// L110:L172
typedef long int  ____syscall_slong_t_226;// L93:L175
typedef unsigned long int  ____syscall_ulong_t_227;// L94:L177
typedef ____off64_t_200  ____loff_t_228;// L181
typedef ____quad_t_190  * (____qaddr_t_230);// L182
typedef char  * (____caddr_t_231);// L183
typedef long int  ____intptr_t_232;// L110:L186
typedef unsigned int  ____socklen_t_233;// L92:L189
typedef ____u_char_23  __u_char_234;// L33
typedef ____u_char_178  __u_char_235;// L33
typedef ____u_short_24  __u_short_236;// L34
typedef ____u_short_179  __u_short_237;// L34
typedef ____u_int_25  __u_int_238;// L35
typedef ____u_int_180  __u_int_239;// L35
typedef ____u_long_26  __u_long_240;// L36
typedef ____u_long_181  __u_long_241;// L36
typedef ____quad_t_35  __quad_t_242;// L37
typedef ____quad_t_190  __quad_t_243;// L37
typedef ____u_quad_t_36  __u_quad_t_244;// L38
typedef ____u_quad_t_191  __u_quad_t_245;// L38
typedef ____fsid_t_50  __fsid_t_246;// L39
typedef ____fsid_t_205  __fsid_t_247;// L39
typedef ____loff_t_73  __loff_t_249;// L44
typedef ____loff_t_228  __loff_t_250;// L44
typedef ____loff_t_73  __loff_t_252;// L44
typedef ____loff_t_228  __loff_t_253;// L44
typedef ____ino64_t_41  __ino_t_255;// L50
typedef ____ino64_t_196  __ino_t_256;// L50
typedef ____ino_t_40  __ino_t_258;// L48
typedef ____ino_t_195  __ino_t_259;// L48
typedef ____dev_t_37  __dev_t_261;// L60
typedef ____dev_t_192  __dev_t_262;// L60
typedef ____gid_t_39  __gid_t_264;// L65
typedef ____gid_t_194  __gid_t_265;// L65
typedef ____gid_t_39  __gid_t_267;// L65
typedef ____gid_t_194  __gid_t_268;// L65
typedef ____mode_t_42  __mode_t_270;// L70
typedef ____mode_t_197  __mode_t_271;// L70
typedef ____nlink_t_43  __nlink_t_273;// L75
typedef ____nlink_t_198  __nlink_t_274;// L75
typedef ____uid_t_38  __uid_t_276;// L80
typedef ____uid_t_193  __uid_t_277;// L80
typedef ____uid_t_38  __uid_t_279;// L80
typedef ____uid_t_193  __uid_t_280;// L80
typedef ____off64_t_45  __off_t_282;// L88
typedef ____off64_t_200  __off_t_283;// L88
typedef ____off_t_44  __off_t_285;// L86
typedef ____off_t_199  __off_t_286;// L86
typedef ____pid_t_46  __pid_t_288;// L98
typedef ____pid_t_201  __pid_t_289;// L98
typedef ____pid_t_46  __pid_t_291;// L98
typedef ____pid_t_201  __pid_t_292;// L98
typedef ____id_t_54  __id_t_294;// L104
typedef ____id_t_209  __id_t_295;// L104
typedef ____ssize_t_70  __ssize_t_297;// L109
typedef ____ssize_t_225  __ssize_t_298;// L109
typedef ____daddr_t_58  __daddr_t_300;// L115
typedef ____daddr_t_213  __daddr_t_301;// L115
typedef ____caddr_t_76  __caddr_t_303;// L116
typedef ____caddr_t_231  __caddr_t_304;// L116
typedef ____key_t_59  __key_t_305;// L122
typedef ____key_t_214  __key_t_306;// L122
typedef ____key_t_59  __key_t_308;// L122
typedef ____key_t_214  __key_t_309;// L122
typedef ____clock_t_51  __clock_t_311;// L59
typedef ____clock_t_206  __clock_t_312;// L59
typedef ____time_t_55  __time_t_314;// L75
typedef ____time_t_210  __time_t_315;// L75
typedef ____clockid_t_60  __clockid_t_317;// L91
typedef ____clockid_t_215  __clockid_t_318;// L91
typedef ____timer_t_61  __timer_t_320;// L103
typedef ____timer_t_216  __timer_t_321;// L103
typedef unsigned long int  __ulong_323;// L150
typedef unsigned long int  __ulong_324;// L150
typedef unsigned long int  __ulong_325;// L150
typedef unsigned short int  __ushort_326;// L151
typedef unsigned int  __uint_327;// L152
typedef int  __int8_t_328;// L188:L194
typedef int  __int16_t_329;// L188:L195
typedef int  __int32_t_330;// L188:L196
typedef int  __int64_t_331;// L188:L197
typedef unsigned int  __u_int8_t_332;// L190:L200
typedef unsigned int  __u_int16_t_333;// L190:L201
typedef unsigned int  __u_int32_t_334;// L190:L202
typedef unsigned int  __u_int64_t_335;// L190:L203
typedef int  __register_t_336;// L205
typedef int  ____sig_atomic_t_342;// L22
struct ____anonymous_tag_343_344 {
unsigned long int  ____val_345[( 1024 / ( 8 * sizeof(unsigned long) ) )];// L29
};
typedef struct ____anonymous_tag_343_344  ____sigset_t_346;// L27:L30
typedef ____sigset_t_346  __sigset_t_347;// L37
struct __timespec_348 {
____time_t_55  __tv_sec_349;// L0
____time_t_210  __tv_sec_350;// L0
____syscall_slong_t_71  __tv_nsec_352;// L0
____syscall_slong_t_226  __tv_nsec_353;// L0
};
struct __timeval_356 {
____time_t_55  __tv_sec_357;// L0
____time_t_210  __tv_sec_358;// L0
____suseconds_t_57  __tv_usec_360;// L0
____suseconds_t_212  __tv_usec_361;// L0
};
typedef ____suseconds_t_57  __suseconds_t_364;// L48
typedef ____suseconds_t_212  __suseconds_t_365;// L48
typedef long int  ____fd_mask_367;// L54
typedef long int  ____fd_mask_368;// L54
struct ____anonymous_tag_369_370 {
____fd_mask_367  ____fds_bits_371[1024 / ( 8 * ( int   ) sizeof(long) )];// L0
____fd_mask_368  ____fds_bits_373[1024 / ( 8 * ( int   ) sizeof(long) )];// L0
};
typedef struct ____anonymous_tag_369_370  __fd_set_376;// L64:L75
typedef ____fd_mask_367  __fd_mask_377;// L82
typedef ____fd_mask_368  __fd_mask_378;// L82
typedef ____blksize_t_62  __blksize_t_426;// L228
typedef ____blksize_t_217  __blksize_t_427;// L228
typedef ____blkcnt_t_63  __blkcnt_t_429;// L235
typedef ____blkcnt_t_218  __blkcnt_t_430;// L235
typedef ____fsblkcnt_t_65  __fsblkcnt_t_432;// L239
typedef ____fsblkcnt_t_220  __fsblkcnt_t_433;// L239
typedef ____blkcnt64_t_64  __blkcnt_t_435;// L248
typedef ____blkcnt64_t_219  __blkcnt_t_436;// L248
typedef ____fsblkcnt64_t_66  __fsblkcnt_t_438;// L252
typedef ____fsblkcnt64_t_221  __fsblkcnt_t_439;// L252
typedef ____fsfilcnt_t_67  __fsfilcnt_t_441;// L243
typedef ____fsfilcnt_t_222  __fsfilcnt_t_442;// L243
typedef ____fsfilcnt64_t_68  __fsfilcnt_t_444;// L256
typedef ____fsfilcnt64_t_223  __fsfilcnt_t_445;// L256
typedef unsigned long int  __pthread_t_447;// L60
union __pthread_attr_t_448 {
char  ____size_449[56];// L65
long int  ____align_450;// L66
};
typedef union __pthread_attr_t_448  __pthread_attr_t_451;// L69
struct ____pthread_internal_list_453 {
struct __forward_tag_reference_452  * (____prev_454);// L0
struct __forward_tag_reference_452  * (____next_455);// L0
};
typedef struct ____pthread_internal_list_453  ____pthread_list_t_456;// L75:L79
typedef struct ____pthread_internal_list_453  ____pthread_list_t_457;// L75:L79
struct ____pthread_mutex_s_458 {
int  ____lock_459;// L94
unsigned int  ____count_460;// L95
int  ____owner_461;// L96
unsigned int  ____nusers_462;// L98
int  ____kind_463;// L102
short  ____spins_464;// L104
short  ____elision_465;// L105
____pthread_list_t_456  ____list_466;// L0
____pthread_list_t_457  ____list_467;// L0
};
union ____anonymous_tag_468_469 {
struct ____pthread_mutex_s_458  ____data_470;// L92
char  ____size_471[40];// L126
long int  ____align_472;// L127
};
typedef union ____anonymous_tag_468_469  __pthread_mutex_t_473;// L90:L128
union ____anonymous_tag_474_475 {
char  ____size_476[4];// L132
int  ____align_477;// L133
};
typedef union ____anonymous_tag_474_475  __pthread_mutexattr_t_478;// L130:L134
typedef int  (* (____compar_fn_t_586)) (const void  *, const void  *);// L741

struct __forward_tag_reference_452 { // generated union of struct variations
union {
};
};

extern void  (____assert_fail_4) (const char  * (____assertion_0), const char  * (____file_1), unsigned int  ____line_2, const char  * (____function_3));// L69:L71
extern void  (____assert_perror_fail_9) (int  ____errnum_5, const char  * (____file_6), unsigned int  ____line_7, const char  * (____function_8));// L74:L76
extern void  (____assert_13) (const char  * (____assertion_10), const char  * (____file_11), int  ____line_12);// L81:L82
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
static __inline unsigned int  (____bswap_32_80) (unsigned int  ____bsx_79) {

if (__static_condition_default_81) {

{// L46
{



__static_type_error("invalid type found in return expression");
}
}// L48


}
}
static __inline ____uint64_t_34  (____bswap_64_83) (____uint64_t_34  ____bsx_82) {

if (__static_condition_default_81) {

{// L110
{



__static_type_error("invalid type found in return expression");
}
}// L112


}
}
union __wait_95 ;// L66
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern __size_t_15  (____ctype_get_mb_cur_max_119) (void  );// L139
extern __size_t_15  (____ctype_get_mb_cur_max_120) (void  );// L139
extern __size_t_15  (____ctype_get_mb_cur_max_121) (void  );// L139
extern __size_t_15  (____ctype_get_mb_cur_max_122) (void  );// L139
extern double  (__atof_124) (const char  * (____nptr_123));// L144:L145
extern double  (__atof_125) (const char  * (____nptr_123));// L144:L145
extern int  (__atoi_127) (const char  * (____nptr_126));// L147:L148
extern int  (__atoi_128) (const char  * (____nptr_126));// L147:L148
extern long int  (__atol_130) (const char  * (____nptr_129));// L150:L151
extern long int  (__atol_131) (const char  * (____nptr_129));// L150:L151
extern long long int  (__atoll_133) (const char  * (____nptr_132));// L157:L158
extern long long int  (__atoll_134) (const char  * (____nptr_132));// L157:L158
extern double  (__strtod_137) (const char  * __restrict  ____nptr_135, char  * (* __restrict  ____endptr_136));// L164:L166
extern float  (__strtof_140) (const char  * __restrict  ____nptr_138, char  * (* __restrict  ____endptr_139));// L172:L173
extern long double  (__strtold_143) (const char  * __restrict  ____nptr_141, char  * (* __restrict  ____endptr_142));// L175:L177
extern long int  (__strtol_147) (const char  * __restrict  ____nptr_144, char  * (* __restrict  ____endptr_145), int  ____base_146);// L183:L185
extern unsigned long int  (__strtoul_151) (const char  * __restrict  ____nptr_148, char  * (* __restrict  ____endptr_149), int  ____base_150);// L187:L189
extern long long int  (__strtoq_155) (const char  * __restrict  ____nptr_152, char  * (* __restrict  ____endptr_153), int  ____base_154);// L195:L197
extern unsigned long long int  (__strtouq_159) (const char  * __restrict  ____nptr_156, char  * (* __restrict  ____endptr_157), int  ____base_158);// L200:L202
extern long long int  (__strtoll_163) (const char  * __restrict  ____nptr_160, char  * (* __restrict  ____endptr_161), int  ____base_162);// L209:L211
extern long long int  (__strtoll_164) (const char  * __restrict  ____nptr_160, char  * (* __restrict  ____endptr_161), int  ____base_162);// L209:L211
extern unsigned long long int  (__strtoull_168) (const char  * __restrict  ____nptr_165, char  * (* __restrict  ____endptr_166), int  ____base_167);// L214:L216
/* no function due to type errors in the function prototype */
/* no function due to type errors in the function prototype */
__extension__/* no function due to type errors in the function prototype */
extern char  * ((__l64a_173) (long int  ____n_172));// L305
extern char  * ((__l64a_174) (long int  ____n_172));// L305
extern long int  (__a64l_176) (const char  * (____s_175));// L308:L309
extern long int  (__a64l_177) (const char  * (____s_175));// L308:L309
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
static __inline unsigned int  (____bswap_32_338) (unsigned int  ____bsx_337) {

if (__static_condition_default_339) {

{// L46
{



__static_type_error("invalid type found in return expression");
}
}// L48


}
}
static __inline ____uint64_t_189  (____bswap_64_341) (____uint64_t_189  ____bsx_340) {

if (__static_condition_default_339) {

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
struct __timespec_348 ;// L120

struct __timeval_356 ;// L30

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__select_390) (int  ____nfds_379, __fd_set_376  * __restrict  ____readfds_380, __fd_set_376  * __restrict  ____writefds_382, __fd_set_376  * __restrict  ____exceptfds_384, struct __timeval_356  * __restrict  ____timeout_387);// L106:L109
extern int  (__select_391) (int  ____nfds_379, __fd_set_376  * __restrict  ____readfds_380, __fd_set_376  * __restrict  ____writefds_382, __fd_set_376  * __restrict  ____exceptfds_384, struct __forward_tag_reference_386  * __restrict  ____timeout_389);// L106:L109
extern int  (__pselect_406) (int  ____nfds_394, __fd_set_376  * __restrict  ____readfds_395, __fd_set_376  * __restrict  ____writefds_397, __fd_set_376  * __restrict  ____exceptfds_399, const struct __timespec_348  * __restrict  ____timeout_402, const ____sigset_t_346  * __restrict  ____sigmask_405);// L118:L122
extern int  (__pselect_407) (int  ____nfds_394, __fd_set_376  * __restrict  ____readfds_395, __fd_set_376  * __restrict  ____writefds_397, __fd_set_376  * __restrict  ____exceptfds_399, const struct __forward_tag_reference_401  * __restrict  ____timeout_404, const ____sigset_t_346  * __restrict  ____sigmask_405);// L118:L122
extern long int  (____fdelt_chk_411) (long int  ____d_410);// L24
extern long int  (____fdelt_warn_413) (long int  ____d_412);// L25:L26
extern unsigned int  (__gnu_dev_major_415) (unsigned long long int  ____dev_414);// L27:L28
extern unsigned int  (__gnu_dev_major_416) (unsigned long long int  ____dev_414);// L27:L28
extern unsigned int  (__gnu_dev_minor_418) (unsigned long long int  ____dev_417);// L30:L31
extern unsigned long long int  (__gnu_dev_makedev_421) (unsigned int  ____major_419, unsigned int  ____minor_420);// L33:L35
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
union __pthread_attr_t_448 ;// L63
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
extern int  (__rand_479) (void  );// L374
extern void  (__srand_481) (unsigned int  ____seed_480);// L376
extern int  (__rand_r_483) (unsigned int  * (____seed_482));// L381
extern double  (__drand48_484) (void  );// L389
extern double  (__erand48_486) (unsigned short int  ____xsubi_485[3]);// L390
extern long int  (__lrand48_487) (void  );// L393
extern long int  (__nrand48_489) (unsigned short int  ____xsubi_488[3]);// L394:L395
extern long int  (__mrand48_490) (void  );// L398
extern long int  (__jrand48_492) (unsigned short int  ____xsubi_491[3]);// L399:L400
extern void  (__srand48_494) (long int  ____seedval_493);// L403
extern unsigned short int  * ((__seed48_496) (unsigned short int  ____seed16v_495[3]));// L404:L405
extern void  (__lcong48_498) (unsigned short int  ____param_497[7]);// L406
extern void  * ((__malloc_500) (__size_t_15  ____size_499));// L466
extern void  * ((__malloc_501) (__size_t_15  ____size_499));// L466
extern void  * ((__calloc_504) (__size_t_15  ____nmemb_502, __size_t_15  ____size_503));// L468:L469
extern void  * ((__calloc_505) (__size_t_15  ____nmemb_502, __size_t_15  ____size_503));// L468:L469
extern void  * ((__realloc_508) (void  * (____ptr_506), __size_t_15  ____size_507));// L480:L481
extern void  (__free_510) (void  * (____ptr_509));// L483
extern void  (__cfree_512) (void  * (____ptr_511));// L488
extern void  * ((__alloca_514) (__size_t_15  ____size_513));// L32
extern void  * ((__valloc_516) (__size_t_15  ____size_515));// L498
extern void  * ((__valloc_517) (__size_t_15  ____size_515));// L498
extern int  (__posix_memalign_521) (void  * (* (____memptr_518)), __size_t_15  ____alignment_519, __size_t_15  ____size_520);// L503:L504
extern int  (__posix_memalign_522) (void  * (* (____memptr_518)), __size_t_15  ____alignment_519, __size_t_15  ____size_520);// L503:L504
extern void  * ((__aligned_alloc_525) (__size_t_15  ____alignment_523, __size_t_15  ____size_524));// L509:L510
extern void  * ((__aligned_alloc_526) (__size_t_15  ____alignment_523, __size_t_15  ____size_524));// L509:L510
extern void  * ((__aligned_alloc_527) (__size_t_15  ____alignment_523, __size_t_15  ____size_524));// L509:L510
extern void  * ((__aligned_alloc_528) (__size_t_15  ____alignment_523, __size_t_15  ____size_524));// L509:L510
extern void  (__abort_529) (void  );// L515
extern int  (__atexit_531) (void  (* (____func_530)) (void  ));// L519
extern int  (__at_quick_exit_533) (void  (* (____func_532)) (void  ));// L527
extern int  (__on_exit_538) (void  (* (____func_536)) (int  ____status_534, void  * (____arg_535)), void  * (____arg_537));// L535:L536
extern void  (__exit_540) (int  ____status_539);// L543
extern void  (__exit_541) (int  ____status_539);// L543
extern void  (__quick_exit_543) (int  ____status_542);// L549
extern void  (___Exit_545) (int  ____status_544);// L557
extern char  * ((__getenv_547) (const char  * (____name_546)));// L564
extern char  * ((__getenv_548) (const char  * (____name_546)));// L564
extern int  (__putenv_550) (char  * (____string_549));// L578
extern int  (__setenv_554) (const char  * (____name_551), const char  * (____value_552), int  ____replace_553);// L584:L585
extern int  (__unsetenv_556) (const char  * (____name_555));// L588
extern int  (__clearenv_557) (void  );// L595
extern char  * ((__mktemp_559) (char  * (____template_558)));// L606
extern int  (__mkstemp_562) (char  * (____template_560));// L619
extern int  (__mkstemp_564) (char  * (____template_560));// L619
extern int  (__mkstemp_563) (char  * (____template_561));// L622:L623
extern int  (__mkstemp_565) (char  * (____template_561));// L622:L623
extern int  (__mkstemps_570) (char  * (____template_566), int  ____suffixlen_567);// L641
extern int  (__mkstemps_571) (char  * (____template_568), int  ____suffixlen_569);// L644:L645
extern int  (__mkstemps_572) (char  * (____template_566), int  ____suffixlen_567);// L641
extern int  (__mkstemps_573) (char  * (____template_568), int  ____suffixlen_569);// L644:L645
extern char  * ((__mkdtemp_575) (char  * (____template_574)));// L662
extern char  * ((__mkdtemp_576) (char  * (____template_574)));// L662
extern int  (__system_578) (const char  * (____command_577));// L716
extern int  (__system_579) (const char  * (____command_577));// L716
extern int  (__system_580) (const char  * (____command_577));// L716
extern int  (__system_581) (const char  * (____command_577));// L716
extern char  * ((__realpath_584) (const char  * __restrict  ____name_582, char  * __restrict  ____resolved_583));// L733:L734
extern char  * ((__realpath_585) (const char  * __restrict  ____name_582, char  * __restrict  ____resolved_583));// L733:L734
// typedef moved to top of scope
extern void  * ((__bsearch_594) (const void  * (____key_587), const void  * (____base_588), __size_t_15  ____nmemb_589, __size_t_15  ____size_590, ____compar_fn_t_586  ____compar_591));// L754:L756
extern void  * ((__bsearch_596) (const void  * (____key_587), const void  * (____base_588), __size_t_15  ____nmemb_589, __size_t_15  ____size_590, ____compar_fn_t_586  ____compar_591));// L754:L756
/* no function due to type errors in the function prototype */
extern void  (__qsort_615) (void  * (____base_610), __size_t_15  ____nmemb_611, __size_t_15  ____size_612, ____compar_fn_t_586  ____compar_613);// L764:L765
extern void  (__qsort_617) (void  * (____base_610), __size_t_15  ____nmemb_611, __size_t_15  ____size_612, ____compar_fn_t_586  ____compar_613);// L764:L765
extern int  (__abs_620) (int  ____x_619);// L774
extern int  (__abs_621) (int  ____x_619);// L774
extern long int  (__labs_623) (long int  ____x_622);// L775
extern long int  (__labs_624) (long int  ____x_622);// L775
extern long long int  (__llabs_626) (long long int  ____x_625);// L779:L780
extern long long int  (__llabs_627) (long long int  ____x_625);// L779:L780
extern __div_t_108  (__div_630) (int  ____numer_628, int  ____denom_629);// L788:L789
extern __div_t_108  (__div_631) (int  ____numer_628, int  ____denom_629);// L788:L789
extern __ldiv_t_113  (__ldiv_634) (long int  ____numer_632, long int  ____denom_633);// L790:L791
extern __ldiv_t_113  (__ldiv_636) (long int  ____numer_632, long int  ____denom_633);// L790:L791
extern __lldiv_t_118  (__lldiv_640) (long long int  ____numer_638, long long int  ____denom_639);// L796:L798
extern __lldiv_t_118  (__lldiv_642) (long long int  ____numer_638, long long int  ____denom_639);// L796:L798
extern char  * ((__ecvt_648) (double  ____value_644, int  ____ndigit_645, int  * __restrict  ____decpt_646, int  * __restrict  ____sign_647));// L811:L812
extern char  * ((__ecvt_649) (double  ____value_644, int  ____ndigit_645, int  * __restrict  ____decpt_646, int  * __restrict  ____sign_647));// L811:L812
extern char  * ((__fcvt_654) (double  ____value_650, int  ____ndigit_651, int  * __restrict  ____decpt_652, int  * __restrict  ____sign_653));// L817:L818
extern char  * ((__fcvt_655) (double  ____value_650, int  ____ndigit_651, int  * __restrict  ____decpt_652, int  * __restrict  ____sign_653));// L817:L818
extern char  * ((__gcvt_659) (double  ____value_656, int  ____ndigit_657, char  * (____buf_658)));// L823:L824
extern char  * ((__gcvt_660) (double  ____value_656, int  ____ndigit_657, char  * (____buf_658)));// L823:L824
extern char  * ((__qecvt_665) (long double  ____value_661, int  ____ndigit_662, int  * __restrict  ____decpt_663, int  * __restrict  ____sign_664));// L829:L831
extern char  * ((__qecvt_666) (long double  ____value_661, int  ____ndigit_662, int  * __restrict  ____decpt_663, int  * __restrict  ____sign_664));// L829:L831
extern char  * ((__qfcvt_671) (long double  ____value_667, int  ____ndigit_668, int  * __restrict  ____decpt_669, int  * __restrict  ____sign_670));// L832:L834
extern char  * ((__qfcvt_672) (long double  ____value_667, int  ____ndigit_668, int  * __restrict  ____decpt_669, int  * __restrict  ____sign_670));// L832:L834
extern char  * ((__qgcvt_676) (long double  ____value_673, int  ____ndigit_674, char  * (____buf_675)));// L835:L836
extern char  * ((__qgcvt_677) (long double  ____value_673, int  ____ndigit_674, char  * (____buf_675)));// L835:L836
extern int  (__ecvt_r_684) (double  ____value_678, int  ____ndigit_679, int  * __restrict  ____decpt_680, int  * __restrict  ____sign_681, char  * __restrict  ____buf_682, __size_t_15  ____len_683);// L841:L843
extern int  (__fcvt_r_691) (double  ____value_685, int  ____ndigit_686, int  * __restrict  ____decpt_687, int  * __restrict  ____sign_688, char  * __restrict  ____buf_689, __size_t_15  ____len_690);// L844:L846
extern int  (__qecvt_r_698) (long double  ____value_692, int  ____ndigit_693, int  * __restrict  ____decpt_694, int  * __restrict  ____sign_695, char  * __restrict  ____buf_696, __size_t_15  ____len_697);// L848:L851
extern int  (__qfcvt_r_705) (long double  ____value_699, int  ____ndigit_700, int  * __restrict  ____decpt_701, int  * __restrict  ____sign_702, char  * __restrict  ____buf_703, __size_t_15  ____len_704);// L852:L855
extern int  (__mblen_708) (const char  * (____s_706), __size_t_15  ____n_707);// L862
extern int  (__mblen_709) (const char  * (____s_706), __size_t_15  ____n_707);// L862
extern int  (__mbtowc_713) (__wchar_t_16  * __restrict  ____pwc_710, const char  * __restrict  ____s_711, __size_t_15  ____n_712);// L865:L866
extern int  (__wctomb_716) (char  * (____s_714), __wchar_t_16  ____wchar_715);// L869
extern __size_t_15  (__mbstowcs_720) (__wchar_t_16  * __restrict  ____pwcs_717, const char  * __restrict  ____s_718, __size_t_15  ____n_719);// L873:L874
extern __size_t_15  (__wcstombs_724) (char  * __restrict  ____s_721, const __wchar_t_16  * __restrict  ____pwcs_722, __size_t_15  ____n_723);// L876:L878
extern int  (__rpmatch_727) (const char  * (____response_725));// L887
extern int  (__rpmatch_726) (const char  * (____response_725));// L887
extern int  (__getsubopt_732) (char  * (* __restrict  ____optionp_728), char  * const  * __restrict  ____tokens_729, char  * (* __restrict  ____valuep_730));// L898:L901
extern int  (__getsubopt_731) (char  * (* __restrict  ____optionp_728), char  * const  * __restrict  ____tokens_729, char  * (* __restrict  ____valuep_730));// L898:L901
extern int  (__getloadavg_735) (double  ____loadavg_733[], int  ____nelem_734);// L950:L951
/* no function due to type errors in the function prototype */
extern char  * ((____realpath_chk_740) (const char  * __restrict  ____name_737, char  * __restrict  ____resolved_738, __size_t_15  ____resolvedlen_739));// L23:L25
extern char  * ((____realpath_alias_743) (const char  * __restrict  ____name_741, char  * __restrict  ____resolved_742));// L26:L28
extern char  * ((____realpath_chk_warn_747) (const char  * __restrict  ____name_744, char  * __restrict  ____resolved_745, __size_t_15  ____resolvedlen_746));// L29:L34
/* no function due to type errors in the function prototype */
extern int  (____ptsname_r_chk_755) (int  ____fd_751, char  * (____buf_752), __size_t_15  ____buflen_753, __size_t_15  ____nreal_754);// L52:L53
extern int  (____ptsname_r_alias_759) (int  ____fd_756, char  * (____buf_757), __size_t_15  ____buflen_758);// L54:L56
extern int  (____ptsname_r_chk_warn_764) (int  ____fd_760, char  * (____buf_761), __size_t_15  ____buflen_762, __size_t_15  ____nreal_763);// L57:L61
/* no function due to type errors in the function prototype */
extern int  (____wctomb_chk_772) (char  * (____s_769), __wchar_t_16  ____wchar_770, __size_t_15  ____buflen_771);// L77:L78
extern int  (____wctomb_alias_775) (char  * (____s_773), __wchar_t_16  ____wchar_774);// L79:L80
/* no function due to type errors in the function prototype */
extern __size_t_15  (____mbstowcs_chk_782) (__wchar_t_16  * __restrict  ____dst_778, const char  * __restrict  ____src_779, __size_t_15  ____len_780, __size_t_15  ____dstlen_781);// L98:L100
extern __size_t_15  (____mbstowcs_alias_786) (__wchar_t_16  * __restrict  ____dst_783, const char  * __restrict  ____src_784, __size_t_15  ____len_785);// L101:L104
extern __size_t_15  (____mbstowcs_chk_warn_791) (__wchar_t_16  * __restrict  ____dst_787, const char  * __restrict  ____src_788, __size_t_15  ____len_789, __size_t_15  ____dstlen_790);// L105:L110
/* no function due to type errors in the function prototype */
extern __size_t_15  (____wcstombs_chk_799) (char  * __restrict  ____dst_795, const __wchar_t_16  * __restrict  ____src_796, __size_t_15  ____len_797, __size_t_15  ____dstlen_798);// L130:L132
extern __size_t_15  (____wcstombs_alias_803) (char  * __restrict  ____dst_800, const __wchar_t_16  * __restrict  ____src_801, __size_t_15  ____len_802);// L133:L136
extern __size_t_15  (____wcstombs_chk_warn_808) (char  * __restrict  ____dst_804, const __wchar_t_16  * __restrict  ____src_805, __size_t_15  ____len_806, __size_t_15  ____dstlen_807);// L137:L141
/* no function due to type errors in the function prototype */
void  * ((__vlan_dev_real_dev_812) ()) {

if (__static_condition_default_813) {

{// L12
{



if (__static_condition_default_814) {
( ( void   ) ( 0 ) ) ; // L13:L50
}
if (__static_condition_default_815) {
( ( 0 ) ? ( void   ) ( 0 ) :  ____assert_fail_4  ("false","/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/varBugs/LINUX/d549f55f2e1.c",13, __PRETTY_FUNCTION__ ) ) ; // L13:L91
}
if (__static_condition_default_816) {
__static_type_error("type error") ; // L13:L91
}
if (__static_condition_default_817) {
return ( ( void  * ) 0 ) ;// L14
}
if (__static_condition_default_818) {
__static_type_error("invalid type found in return expression");
}
}
}// L15


}
}
void  * ((__vlan_dev_real_dev_819) ()) {

if (__static_condition_default_820) {

{// L7
{



if (__static_condition_default_821) {
return ( ( void  * ) 0 ) ;// L8
}
if (__static_condition_default_822) {
__static_type_error("invalid type found in return expression");
}
}
}// L9


}
}
static int  (__ocrdma_inet6addr_event_823) () {

if (__static_condition_default_824) {

{// L20
{



if (__static_condition_default_825) {
 __vlan_dev_real_dev_812 ( ) ; // L21
}
if (__static_condition_default_826) {
 __vlan_dev_real_dev_819 ( ) ; // L21
}
return 0 ;// L23
}
}// L24


}
}
int  (__main_829) (int  __argc_827, char  * (* (__argv_828))) {

if (__static_condition_default_831) {

{// L28
{



return 0 ;// L32
}
}// L33


}
}
int  (__main_830) (int  __argc_827, char  * (* (__argv_828))) {

if (__static_condition_default_832) {

{// L28
{



 __ocrdma_inet6addr_event_823 ( ) ; // L30
return 0 ;// L32
}
}// L33


}
}

