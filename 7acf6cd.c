
#ifdef UNK_TRUE
#define unk() 1
#else
#include <stdlib.h>
#define unk() (rand() % 2)
#endif

int some_int = 1;

void pts_sb_from_inode(int *inode)
{
#ifdef CONFIG_DEVPTS_MULTIPLE_INSTANCES
	if (*inode)
	  ;
#endif
}

void devpts_pty_kill(int *inode)
{
  pts_sb_from_inode(inode);
}

void pty_close(int *driver_data)
{
#ifdef CONFIG_UNIX98_PTYS
  devpts_pty_kill(driver_data);
#endif
}

int tty_release(int *driver_data)
{
  pty_close(driver_data);
  return 0;
}

#ifdef CONFIG_UNIX98_PTYS
int ptmx_open()
{
  int *driver_data;

  if (unk()) {
    goto err_release;
  }

  driver_data = &some_int;
  
  return 0;

err_release:
  tty_release(driver_data);
  return -1;
}
#endif

int main()
{
#ifdef CONFIG_UNIX98_PTYS
  ptmx_open();
#endif
  return 0;
}

