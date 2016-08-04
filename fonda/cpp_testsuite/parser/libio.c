/*   /usr/include/libio.h   */

struct _IO_FILE {
  int _flags;

#ifdef _IO_USE_OLD_IO_FILE  /* <==== */
};

struct _IO_FILE_complete
{
  struct _IO_FILE _file;
#endif                      /* <==== */
  int _mode;
};

