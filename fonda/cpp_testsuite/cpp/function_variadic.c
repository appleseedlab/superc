#define eprintf(...) fprintf (stderr, __VA_ARGS__)
eprintf("%s:%d: ", input_file, lineno)

#undef eprintf
#define eprintf(args...) fprintf (stderr, args)
eprintf("%s:%d: ", input_file, lineno)
