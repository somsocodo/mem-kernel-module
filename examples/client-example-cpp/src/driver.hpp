
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <cstdint>

#include "../../../src/ioctl-types.h"

#pragma once
namespace driver {

    int open_device(const char *name);
    pid_t set_task(const char *name);
    uintptr_t read_module(const char *name);
    void ioctl_handle(read_mem_s req);
    template <typename T>
    static const T read_mem(uintptr_t addr) noexcept{
            T value = { };
            struct read_mem_s mem = {
                .addr = addr,
                .len = sizeof(T),
                .buf_addr = reinterpret_cast<uintptr_t>(&value)
            };
        ioctl_handle(mem);
        return value;
    }
}