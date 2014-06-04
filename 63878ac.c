
#include <assert.h>
#include <stdlib.h>

#ifdef CONFIG_ARCH_OMAP3

static int* _omap3_sram_configure_core_dpll;

int omap3_configure_core_dpll()
{
	assert(_omap3_sram_configure_core_dpll);
	return *_omap3_sram_configure_core_dpll;
}

#ifdef CONFIG_PM
static int some_int = 1;

void omap3_sram_restore_context(void)
{
	_omap3_sram_configure_core_dpll = &some_int;
}
#endif /* CONFIG_PM */

int omap3_core_dpll_m2_set_rate()
{
  omap3_configure_core_dpll();
  return 0;
}

static int _omap2_init_reprogram_sdrc(void)
{
  int v;

	v = omap3_core_dpll_m2_set_rate();

	return v;
}
#endif /* CONFIG_ARCH_OMAP3 */

static inline int omap34xx_sram_init(void)
{
#if defined(CONFIG_ARCH_OMAP3) && defined(CONFIG_PM)
	omap3_sram_restore_context();
#endif
	return 0;
}

int omap_sram_init(void)
{
	if (rand() % 2)
		omap34xx_sram_init();

	return 0;
}

void omap_sdrc_init()
{
	omap_sram_init();

	if (rand() % 2) {
#ifdef CONFIG_ARCH_OMAP3
		_omap2_init_reprogram_sdrc();
#endif
	}
}

static void omap3pandora_init(void)
{
	omap_sdrc_init();
}

int main(int argc, char** argv)
{
  omap3pandora_init();
  return 0;
}

