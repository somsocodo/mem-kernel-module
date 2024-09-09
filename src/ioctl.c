#include "ioctl.h"
#include "mem.h"

static int etx_open(struct inode *inode, struct file *file) {
  // pr_info("Device File Opened...!!!\n");
  return 0;
}

static int etx_release(struct inode *inode, struct file *file) {
  // pr_info("Device File Closed...!!!\n");
  return 0;
}

static ssize_t etx_read(struct file *filp, char __user *buf, size_t len,
                        loff_t *off) {
  // pr_info("Read Function\n");
  return 0;
}

static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len,
                         loff_t *off) {
  // pr_info("Write function\n");
  return len;
}

static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
  switch (cmd) {
    case RD_TASK:
      struct set_task_s rd_task;
      struct task_struct *task;
      if (copy_from_user(&rd_task, (void *)arg, sizeof(struct set_task_s)) ==
          0) {
        for_each_process(task) {
          if (strcmp(task->comm, rd_task.task_name) == 0) {
            rd_task.pid = task->pid;
            set_task(task);
            if (copy_to_user((struct set_task_s *)arg, &rd_task,
                             sizeof(rd_task))) {
              pr_err("Data Read : Err!\n");
              break;
            }
            break;
          }
        }
      }
      break;
    case RD_MODULE:
      struct read_module_s module;
      if (copy_from_user(&module, (void *)arg, sizeof(struct read_module_s)) ==
          0) {
        module.addr = read_module(module.module_name);
        if (copy_to_user((struct read_module_s *)arg, &module,
                         sizeof(module))) {
          pr_err("Data Read : Err!\n");
          break;
        }
      }
      break;
    case RD_MEM:
      struct read_mem_s mem;
      void *temp;
      if (copy_from_user(&mem, (void *)arg, sizeof(struct read_mem_s)) == 0) {
        temp = vmalloc(mem.len);
        read_mem(temp, mem.addr, mem.len);

        if (copy_to_user((struct read_mem_s *)mem.buf_addr, temp, mem.len)) {
          pr_err("Data Read : Err!\n");
        }
        vfree(temp);
      }

      break;
    default:
      pr_err("Default\n");
      break;
  }
  return 0;
}

dev_t dev = 0;
int ioctl_init() {
  if ((alloc_chrdev_region(&dev, 0, 1, "mem-module")) < 0) {
    pr_err("Cannot allocate major number\n");
    return -1;
  }

  cdev_init(&etx_cdev, &fops);

  if ((cdev_add(&etx_cdev, dev, 1)) < 0) {
    pr_err("Cannot add the device to the system\n");
    goto r_class;
  }

  if (IS_ERR(dev_class = class_create("mem-class"))) {
    pr_err("Cannot create the struct class\n");
    goto r_class;
  }

  if (IS_ERR(device_create(dev_class, NULL, dev, NULL, "mem-device"))) {
    pr_err("Cannot create the Device 1\n");
    goto r_device;
  }
  pr_info("Device loaded.\n");
  return 0;

r_device:
  class_destroy(dev_class);
r_class:
  unregister_chrdev_region(dev, 1);
  return -1;
}

void ioctl_exit() {
  device_destroy(dev_class, dev);
  class_destroy(dev_class);
  cdev_del(&etx_cdev);
  unregister_chrdev_region(dev, 1);
}