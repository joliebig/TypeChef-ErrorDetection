
#ifdef CONFIG_ANDROID
#define CONFIG_SYSFS
#endif

#include <errno.h>
#include <stdlib.h>

#ifdef CONFIG_SYSFS
static const char *linked = NULL;

static int sysfs_link_sibling(const char *s_name)
{
  if (linked != NULL)
    return (!strcmp(s_name,linked)) ? -EEXIST : -ENOMEM;

  linked = s_name;
  return 0;
}

static void sysfs_unlink_sibling(const char *s_name)
{
  if (linked != NULL && !strcmp(s_name,linked))
    linked = NULL;
}

int sysfs_create_dir(const char *name)
{
  return sysfs_link_sibling(name); // ERROR
}

struct kobject {
  int __foo;
};

static struct kobject the_kobj;

int kobject_add(const char *name)
{
  return sysfs_create_dir(name);
}

struct kobject *kobject_create_and_add(const char *name)
{
  struct kobject *kobj = &the_kobj;

  int retval = kobject_add(name);
  if (retval)
    kobj = NULL;

  return kobj;
}

struct class_compat {
  struct kobject *kobj;
};

static struct class_compat the_cls;

struct class_compat *class_compat_register(const char *name)
{
  struct class_compat *cls;

  cls = &the_cls;
  cls->kobj = kobject_create_and_add(name);
  if (!cls->kobj)
    return NULL;

  return cls;
}
#endif

#ifdef CONFIG_EXTCON
#if defined(CONFIG_ANDROID)
static struct class_compat *switch_class;
#endif /* CONFIG_ANDROID */

static int create_extcon_class(void)
{
#if defined(CONFIG_ANDROID)
    switch_class = class_compat_register("switch");
    if (!switch_class)
      return -ENOMEM;
#endif /* CONFIG_ANDROID */
  return 0;
}

static int extcon_class_init(void)
{
  return create_extcon_class();
}

static void extcon_class_exit(void)
{
  return;
}
#endif

int main(int argc, char** argv)
{
#ifdef CONFIG_EXTCON
  extcon_class_init();
  extcon_class_exit();
  extcon_class_init();
#endif
  return 0;
}

