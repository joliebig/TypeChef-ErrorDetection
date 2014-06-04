
#include <errno.h>
#include <stdlib.h>

#define PAGE_SIZE 12

int *x = NULL;
unsigned int size = PAGE_SIZE+1;

static inline int inet_ehash_locks_alloc()
{
#ifdef CONFIG_NUMA
    if (size > PAGE_SIZE)
      x = malloc(size);
    else
#endif
    x =	malloc(size);
    if (!x)
      return ENOMEM;
  return 0;
}

static inline void inet_ehash_locks_free()
{
  if (x) {
#ifdef CONFIG_NUMA
    if (size > PAGE_SIZE)
      free(x);
    else
#else
    free(x);
#endif
    x = NULL; // ERROR
  }
}

int main(int argc, char** argv)
{
  inet_ehash_locks_alloc();
  inet_ehash_locks_free();
  return 0;
}

