// From linux-2.6.33.3/arch/x86/include/asm/mtrr.h
#ifdef CONFIG_MTRR
extern void mtrr_bp_init(void);
#else
#define mtrr_bp_init() do {} while (0)
#endif

// From linux-2.6.33.3/arch/x86/kernel/cpu/mtrr/main.c:644
void mtrr_bp_init(void)
{
}
