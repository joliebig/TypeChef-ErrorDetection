
#include <pthread.h>
#include <stdlib.h>

static pthread_mutex_t i_lock = PTHREAD_MUTEX_INITIALIZER;

static int inode_get_rsv_space(void)
{
  pthread_mutex_lock(&i_lock); // ERROR
  // do something
  pthread_mutex_unlock(&i_lock);
  return 0;
}

static void add_dquot_ref(void)
{
#ifdef CONFIG_QUOTA_DEBUG
  int reserved = 0;
#endif

  int i, j;
  for (i=0; i<10; i++) {
    pthread_mutex_lock(&i_lock);
    if (rand() % 2) {
      pthread_mutex_unlock(&i_lock);
      continue;
    }

#ifdef CONFIG_QUOTA_DEBUG
    if (inode_get_rsv_space() > 0)
      reserved = 1;
#endif

    pthread_mutex_unlock(&i_lock);
  }
}

int main(int argc, char** arv) {
  add_dquot_ref();
  return 0;
}
