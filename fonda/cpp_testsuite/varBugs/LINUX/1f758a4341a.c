#define ENOMEM      12  /* Out of memory */

#define NULL (void*)0

#define ___GFP_WAIT             0x10u
#define ___GFP_IO               0x40u
#define ___GFP_FS               0x80u
#define __GFP_WAIT      ((int)___GFP_WAIT)    /* Can wait and reschedule? */
#define __GFP_IO        ((int)___GFP_IO)      /* Can start physical IO? */
#define __GFP_FS        ((int)___GFP_FS)      /* Can call down to low-level FS? */
#define GFP_KERNEL      (__GFP_WAIT | __GFP_IO | __GFP_FS)

#define ___GFP_DMA              0x01u
#define __GFP_DMA       ((int)___GFP_DMA)
#define GFP_DMA         __GFP_DMA

static int some_int = 0;

int* __alloc_pages_nodemask(int gfp_mask)
{
  #ifndef CONFIG_ZONE_DMA
  if (gfp_mask & __GFP_DMA)
    return NULL; // (4)
  #endif
  return &some_int;
}

#ifdef CONFIG_EP93XX_ETH
int ep93xx_alloc_buffers()
{
  int *descs = __alloc_pages_nodemask(GFP_KERNEL | GFP_DMA); // (3)
  if (descs == NULL)
    return 1; // (5)
}

int ep93xx_open()
{
  if (ep93xx_alloc_buffers()) // (2)
    return -ENOMEM; // (6) ERROR
}
#endif

int main(void)
{
  #ifdef CONFIG_EP93XX_ETH
  ep93xx_open(); // (1)
  #endif
  return 0;
}
