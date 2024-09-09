#ifndef MEM_H
#define MEM_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/sched/mm.h>
#include <linux/mm.h>
#include <linux/rwsem.h>
#include <linux/highmem.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>
#include <linux/cacheflush.h>

static struct task_struct *mem_task = NULL;

void read_mem(void* buf, ulong addr, size_t len);

uintptr_t read_module(char name[512]);

void set_task(struct task_struct *task);

#endif