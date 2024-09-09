
#include <linux/module.h>

#include "ioctl.h"
#include "mem.h"

MODULE_LICENSE("GPL");

static int __init mem_module_init(void) {
  if (ioctl_init() > 0) pr_err("ioctl_init failed\n");

  pr_info("Module loaded.\n");

  return 0;
}

static void __exit mem_module_exit(void) {
  ioctl_exit();
  pr_info("Module unloaded.\n");
}

module_init(mem_module_init);
module_exit(mem_module_exit);
