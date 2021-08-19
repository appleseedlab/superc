typedef struct __fd_set
{
  int fds_bits[4];
} fd_set;
# define __FD_ZERO_STOS "stosq"
# define __FDS_BITS(set) ((set)->fds_bits)
# define __FD_ZERO(fdsp)                                                \
  do {                                                                        \
    int __d0, __d1;                                                           \
    __asm__ __volatile__ ("cld; rep; " __FD_ZERO_STOS                         \
                          : "=c" (__d0), "=D" (__d1)                          \
                          : "a" (0), "0" (sizeof (fd_set)),             \
                            "1" (&__FDS_BITS (fdsp)[0])                       \
                          : "memory");                                        \
  } while (0)

int main()
{
  fd_set x;
  __FD_ZERO(&x);
}
