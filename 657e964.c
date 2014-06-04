
#include <assert.h>
#include <stdbool.h>

#ifdef UNK_TRUE
#define unk() 1
#else
#include <stdlib.h>
#define unk() (rand() % 2)
#endif

static int preempt_counter = 0;

#define preempt_count() (preempt_counter)

#ifdef CONFIG_PREEMPT
#define put_cpu() (preempt_counter--)
#else
#define put_cpu()
#endif

static inline void tcp_put_md5sig_pool(void)
{
  put_cpu();
}

void tcp_twsk_destructor()
{
#ifdef CONFIG_TCP_MD5SIG
  if (unk())
    tcp_put_md5sig_pool();
#endif
}

static inline void twsk_destructor()
{
  tcp_twsk_destructor();
}

static void inet_twsk_free()
{
  twsk_destructor();
}

void inet_twsk_put()
{
  inet_twsk_free();
}

static int inet_twdr_do_twkill_work()
{
  inet_twsk_put();
  return 0;
}

void inet_twdr_hangman()
{
  inet_twdr_do_twkill_work();
}

static inline void __run_timers()
{
  int preempt_count = preempt_count();
  inet_twdr_hangman();
  if (preempt_count != preempt_count()) {
    assert(false);
  }
}

int main(int argc, char** argv)
{
  __run_timers();
  return 0;
}

