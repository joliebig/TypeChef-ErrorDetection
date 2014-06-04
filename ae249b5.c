
#include <stdbool.h>

#ifdef CONFIG_DISCONTIGMEM
#include <assert.h>
#include <string.h>
#endif

#define PFNNID_MAP_MAX  512     /* support 512GB */
unsigned char pfnnid_map[PFNNID_MAP_MAX];
unsigned long max_pfn = PFNNID_MAP_MAX;

#ifdef CONFIG_DISCONTIGMEM
int pfn_to_nid(unsigned long pfn)
{
  unsigned char r;

  assert(pfn < PFNNID_MAP_MAX);
  r = pfnnid_map[pfn];
  assert(r != 0xff); // ERROR

  return (int)r;
}

int pfn_valid(int pfn)
{
	int nid = pfn_to_nid(pfn);

	return (nid >= 0);
}
#endif

#ifndef CONFIG_DISCONTIGMEM
#define pfn_valid(pfn)		(true)
#endif /* CONFIG_DISCONTIGMEM */

#ifdef CONFIG_PROC_PAGE_MONITOR
int kpageflags_read()
{
  unsigned int pfn = 0;

  for (;pfn<max_pfn;pfn++) {
    if (pfn_valid(pfn))
      ;
  }

  return 0;
}
#endif

void setup_bootmem(void)
{
#ifdef CONFIG_DISCONTIGMEM
  memset(pfnnid_map, 0xff, sizeof(pfnnid_map));
#endif
}

int main()
{
  setup_bootmem();
#ifdef CONFIG_PROC_PAGE_MONITOR
  kpageflags_read();
#endif
  return 0;
}

