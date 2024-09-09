#include "driver.hpp"
#pragma GCC diagnostic ignored "-Wmultichar"

namespace driver {
int driverFD = -1;

int open_device(const char *name) {
  DIR *d = opendir("/dev/");
  struct dirent *e;
  char p[512];

  snprintf(p, sizeof(p), "/dev/%s", name);
  driverFD = open(p, O_RDWR);

  closedir(d);
  return driverFD;
}

pid_t set_task(const char *name) {
  set_task_s rd_task;
  snprintf(rd_task.task_name, sizeof(rd_task.task_name), "%s", name);
  rd_task.pid = -1;
  ioctl(driverFD, RD_TASK, (set_task_s *)&rd_task);
  return rd_task.pid;
}

uintptr_t read_module(const char *name) {
  read_module_s rd_module;
  snprintf(rd_module.module_name, sizeof(rd_module.module_name), "%s", name);
  rd_module.addr = -1;
  ioctl(driverFD, RD_MODULE, (read_module_s *)&rd_module);
  return rd_module.addr;
}

void ioctl_handle(read_mem_s req) {
  ioctl(driverFD, RD_MEM, (read_mem_s *)&req);
}
}