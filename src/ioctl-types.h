#include <linux/types.h>
#include <linux/ioctl.h>

#ifndef MEM_IOCTL
#define MEM_IOCTL

struct set_task_s {
  char task_name[512];
  pid_t pid;
};

struct read_module_s {
  char module_name[512];
  uintptr_t addr;
  size_t size;
};

struct read_mem_s {
  uintptr_t addr;
  size_t len;
  uintptr_t buf_addr;
};

#endif

#define RD_TASK _IOR('0x22','0', struct set_task_s*)
#define RD_MODULE _IOR('0x22','1', struct read_module_s*)
#define RD_MEM _IOWR('0x22','2', struct read_mem_s*)
