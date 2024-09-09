#include "driver.hpp"

//https://github.com/a2x/cs2-dumper
constexpr std::ptrdiff_t dwLocalPlayerController = 0x386DFF8;
constexpr std::ptrdiff_t m_iPawnHealth = 0x980; // uint32
constexpr std::ptrdiff_t m_iszPlayerName = 0x7C8; // char[128]

struct s_struct {
    char name[128];
};

int main(int argc, char **argv){
    const char* device_name = "mem-device";
    const char* task_name = "cs2";
    const char* module_name = "libclient.so";

    if(driver::open_device(device_name) == -1){
        printf("Cannot open device file.\n");
        return 0;
    }
    
    pid_t pid = driver::set_task(task_name);

    if(pid == -1){
        printf("Could not find task %s\n", task_name);
        return 0;
    }

    printf("Set task %s, pid: %d.\n", task_name, pid);
    
    uintptr_t module_addr = driver::read_module(module_name);

    if(module_addr == -1){
        printf("Could not find module address for %s\n", task_name);
        return 0;
    }

    printf("Found module address for %s: %x\n", module_name, module_addr);

    const uintptr_t local_controller = driver::read_mem<uintptr_t>(module_addr + dwLocalPlayerController);
    const uint32_t health = driver::read_mem<uint32_t>(local_controller + m_iPawnHealth);
    const char* name = driver::read_mem<s_struct>(local_controller + m_iszPlayerName).name;

    printf("%s | %d\n", name, health);
    
    return 1;
}