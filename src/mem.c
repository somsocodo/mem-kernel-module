#include "mem.h"

void read_mem(void *buf, ulong addr, size_t len) {
    struct mm_struct *mm = get_task_mm(mem_task);
    struct vm_area_struct *vma;
    struct page *page = NULL;
    int locked = 1;

    down_read_killable(&mm->mmap_lock);
    vma = vma_lookup(mm, addr);

    if (get_user_pages_remote(mm, addr, 1, FOLL_FORCE, &page, NULL) == 1) {
        void *target = kmap(page);

        copy_from_user_page(vma, page, addr, buf, target + (addr % PAGE_SIZE), len);

        kunmap(page);
        put_page(page);
    }

    up_read(&mm->mmap_lock);
    mmput(mm);
}

uintptr_t read_module(char name[512]) {
    uintptr_t module_start = -1;
    struct mm_struct *mm = get_task_mm(mem_task);
    VMA_ITERATOR(vmi, mm, 0);
    struct vm_area_struct *c_vma;
    for_each_vma(vmi, c_vma) {
          if (c_vma->vm_file == NULL) continue;
          
          if (strcmp(c_vma->vm_file->f_path.dentry->d_iname,
                      name) == 0) {   
            module_start = c_vma->vm_start;
            break;      
          }
    }
    return module_start;
}

void set_task(struct task_struct *task){
    mem_task = task;
}