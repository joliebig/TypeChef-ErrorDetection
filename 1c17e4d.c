
#include <stdio.h>

#ifdef CONFIG_RCU_CPU_STALL_INFO

#ifdef CONFIG_RCU_FAST_NO_HZ
static void print_cpu_stall_fast_no_hz(char *cp, int cpu)
{
	sprintf(cp, "foobar");
}
#else /* #ifdef CONFIG_RCU_FAST_NO_HZ */
static void print_cpu_stall_fast_no_hz(char *cp, int cpu)
{
}
#endif /* #else #ifdef CONFIG_RCU_FAST_NO_HZ */

static void print_cpu_stall_info(int cpu)
{
	char fast_no_hz[72];

	print_cpu_stall_fast_no_hz(fast_no_hz, cpu);
	printf("\t%d: %s\n", cpu, fast_no_hz); // ERROR
}
#else /* #ifdef CONFIG_RCU_CPU_STALL_INFO */
static void print_cpu_stall_info(int cpu)
{
	printf(" %d", cpu);
}
#endif /* #else #ifdef CONFIG_RCU_CPU_STALL_INFO */

int main(int argc, char** argv) {
#ifdef CONFIG_RCU_CPU_STALL_INFO
  print_cpu_stall_info(0);
#endif
  return 0;
}
