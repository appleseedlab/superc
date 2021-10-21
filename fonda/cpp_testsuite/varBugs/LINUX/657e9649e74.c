#include <assert.h>

__attribute__ ((noinline)) int nondet() { return 42; }

static int preempt_counter = 0;

#define preempt_count() (preempt_counter)

#ifdef CONFIG_PREEMPT
#define put_cpu() (preempt_counter--)
#else
#define put_cpu()
#endif

#ifdef CONFIG_TCP_MD5SIG
#define free_cpu()
#endif

static inline void tcp_free_md5sig_pool(void)
{
  free_cpu();
}

static inline void tcp_put_md5sig_pool(void)
{
  put_cpu(); // (9)
}

void tcp_twsk_destructor()
{
  #ifdef CONFIG_TCP_MD5SIG
  if (nondet())
    tcp_put_md5sig_pool(); // (8)
  #endif
}

static inline void twsk_destructor()
{
  tcp_twsk_destructor(); // (7)
}

static void inet_twsk_free()
{
  twsk_destructor(); // (6)
}

void inet_twsk_put()
{
  inet_twsk_free(); // (5)
}

static int inet_twdr_do_twkill_work()
{
  inet_twsk_put(); // (4)
  return 0;
}

void inet_twdr_hangman()
{
  inet_twdr_do_twkill_work(); // (3)
}

static inline void __run_timers()
{
  int preempt_count = preempt_count();
  inet_twdr_hangman(); // (2)
  if (preempt_count != preempt_count()) {
    assert(0); // (10) ERROR
  }
}

int main(void)
{
  __run_timers(); // (1)
  return 0;
}
