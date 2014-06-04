
#include <stdlib.h>

#ifdef CONFIG_SECURITY
static inline int security_old_inode_init_security(int *len)
{
  if (rand() % 2) {
    *len = 0;
    return 0;
  }
  else
    return -1;
}
#else
static inline int security_old_inode_init_security(int *len)
{
  return 0;
}
#endif

int reiserfs_security_init(int *length)
{
  int error;

  error = security_old_inode_init_security(length);

  if (error) {
    *length = 0;
    return error;
  }

  if (*length) { // ERROR
    // do something
  }

  return 0;
}

static int reiserfs_create()
{
  int retval;
  int length;

  retval = reiserfs_security_init(&length);
  if (retval < 0) {
    return retval;
  }

  return 0;
}

int main(int argc, char** argv) {
  reiserfs_create();
  return 0;
}

