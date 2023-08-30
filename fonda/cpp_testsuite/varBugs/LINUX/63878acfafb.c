extern void __assert_fail (const char *__assertion, const char *__file,
                           unsigned int __line, const char *__function)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));

__attribute__ ((noinline)) int nondet() { return 42; }

#ifdef CONFIG_ARCH_OMAP3

static int* _omap3_sram_configure_core_dpll;

int omap3_configure_core_dpll()
{
  ((_omap3_sram_configure_core_dpll)
   ? (void) (0)
   : __assert_fail ("_omap3_sram_configure_core_dpll", "63878ac.c", 16, __PRETTY_FUNCTION__));
  return *_omap3_sram_configure_core_dpll; // (6) ERROR
}

#ifdef CONFIG_PM // DISABLED
static int some_int = 1;

void omap3_sram_restore_context(void)
{
  _omap3_sram_configure_core_dpll = &some_int;
}
#endif /* CONFIG_PM */

int omap3_core_dpll_m2_set_rate()
{
  omap3_configure_core_dpll(); // (5)
  return 0;
}

int _omap2_init_reprogram_sdrc(void)
{
  int v;

  v = omap3_core_dpll_m2_set_rate(); // (4)

  return v;
}
#endif /* CONFIG_ARCH_OMAP3 */

int omap34xx_sram_init(void)
{
#if defined(CONFIG_ARCH_OMAP3) && defined(CONFIG_PM) // DISABLED
  omap3_sram_restore_context();
  #endif
  return 0;
}

int omap_sram_init(void)
{
  if (nondet())
    omap34xx_sram_init();

  return 0;
}

void omap_sdrc_init()
{
  omap_sram_init(); // does nothing in ARCH_OPAM3 && !PM

  if (nondet()) { // evaluates to true
    #ifdef CONFIG_ARCH_OMAP3
    _omap2_init_reprogram_sdrc(); // (3)
    #endif
  }
}

void omap3pandora_init(void)
{
  omap_sdrc_init(); // (2)
}

int main(void)
{
  omap3pandora_init(); // (1)
  return 0;
}
