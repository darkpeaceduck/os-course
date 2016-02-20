#ifndef __MEMORY_H__
#define __MEMORY_H__

#define PAGE_BITS         12
#define PAGE_SIZE         (1 << 12)
#define PAGE_MASK         (PAGE_SIZE - 1)
#define KERNEL_BASE       0xffffffff80000000
#define HIGH_BASE         0xffff800000000000
#define PHYSICAL_BASE     0x0000000000000000

#define KERNEL_CODE       0x18
#define KERNEL_DATA       0x20

#define KERNEL_PHYS(x)    ((x) - KERNEL_BASE)
#define KERNEL_VIRT(x)    ((x) + KERNEL_BASE)

#ifndef __ASM_FILE__

#include <stdint.h>

static inline uintptr_t kernel_phys(void *addr) {
	return KERNEL_PHYS((uintptr_t )addr);
}

static inline void *kernel_virt(uintptr_t addr) {
	return (void *) KERNEL_VIRT(addr);
}

static inline void fill_mem(void * ptr, uint8_t value, int64_t size) {
	for (char * _ptr = (char *) ptr; _ptr - ((char *) ptr) < size; _ptr++) {
		*_ptr = value;
	}
}

#endif /*__ASM_FILE__*/

#endif /*__MEMORY_H__*/
