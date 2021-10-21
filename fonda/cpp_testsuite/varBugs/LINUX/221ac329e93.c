#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

char *buffer;

#if !defined(CONFIG_KGDB) && !defined(CONFIG_XMON) && !defined(CONFIG_BDI_SWITCH)
void allocate_buffer() {
  int pagesize;

  pagesize = sysconf(_SC_PAGE_SIZE);
  if (pagesize == -1)
    handle_error("sysconf");

  buffer = memalign(pagesize, 4*pagesize);
  if (buffer == NULL)
    handle_error("memalign");

  if (mprotect(buffer, 4*pagesize, PROT_READ) == -1)
    handle_error("mprotect");
}
#else
#define allocate_buffer() ({ buffer = malloc(4092); })
#endif


int main(int argc, char** argv)
{
  allocate_buffer();
  #ifdef CONFIG_KPROBES
  *buffer = 'a'; // ERROR
  #endif
  return 0;
}
