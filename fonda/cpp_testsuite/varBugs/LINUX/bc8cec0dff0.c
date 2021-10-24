#define ENOMEM          12      /* Out of memory */

typedef long unsigned int size_t;

extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));

#define WBUF_PAGESIZE 32

unsigned char *wbuf; /* Write-behind buffer for NAND flash */
#ifdef CONFIG_JFFS2_FS_WBUF_VERIFY
unsigned char *wbuf_verify; /* read-back buffer for verification */
#endif

int jffs2_nor_wbuf_flash_setup() {
  wbuf = malloc(WBUF_PAGESIZE);
  if (!wbuf)
    return -ENOMEM;

  return 0;
}

#ifdef CONFIG_JFFS2_FS_WBUF_VERIFY
static int jffs2_verify_write()
{
  return(int) *wbuf_verify; // ERROR (6)
}
#else
#define jffs2_verify_write() do { } while (0)
#endif

int __jffs2_flush_wbuf()
{
  jffs2_verify_write(); // (5)
  return 0;
}

int jffs2_flash_writev()
{
  __jffs2_flush_wbuf(); // (4)
  return 0;
}

int jffs2_flash_write()
{
  return jffs2_flash_writev(); // (3)
}

int main()
{
  jffs2_nor_wbuf_flash_setup(); // (1)
  jffs2_flash_write(); // (2)
  return 0;
}
