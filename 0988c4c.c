
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef CONFIG_VLAN_8021Q
static inline bool vlan_hwaccel_do_receive()
{
  // do something
  return true;
}
#else
static inline bool vlan_hwaccel_do_receive()
{
  assert(false); // ERROR
  return false;
}
#endif

static int __netif_receive_skb()
{
  if (rand() % 2) {
    vlan_hwaccel_do_receive();
  }
}

int netif_receive_skb()
{
#ifdef CONFIG_RPS
  return __netif_receive_skb();
#else
	return __netif_receive_skb();
#endif
}

int main(int argc, char** argv)
{
  netif_receive_skb();
  return 0;
}
