
#ifndef	_DIRENT_H
#define	_DIRENT_H	1



#ifdef __USE_XOPEN
# ifndef __ino_t_defined
#  ifndef __USE_FILE_OFFSET64
typedef __ino_t ino_t;
#  else
typedef __ino64_t ino_t;
#  endif
#  define __ino_t_defined
# endif
# if /*defined __USE_LARGEFILE64 &&*/ !defined __ino64_t_defined
typedef __ino64_t ino64_t;
#  define __ino64_t_defined
# endif
#endif


#if defined __USE_MISC && !defined d_fileno
# define d_ino	d_fileno		 /* Backward compatibility.  */
#endif

//#ifdef _DIRENT_HAVE_D_NAMLEN
//# define _D_EXACT_NAMLEN(d) ((d)->d_namlen)
//# define _D_ALLOC_NAMLEN(d) (_D_EXACT_NAMLEN (d) + 1)
//#else
# define _D_EXACT_NAMLEN(d) (strlen ((d)->d_name))
//# ifdef _DIRENT_HAVE_D_RECLEN
#  define _D_ALLOC_NAMLEN(d) (((char *) (d) + (d)->d_reclen) - &(d)->d_name[0])

#endif
