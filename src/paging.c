#include "buddy_allocator.h"
#include "paging.h"
#include "mmap.h"
#include "memory.h"

#define TWO_GB (0x80000000)

static void rewrite_addr_with_flags(pte_t * addr, phys_t phys, int page_flags){
	*addr = phys | page_flags;
}
static void rewrite_flags(pte_t * addr, int page_flags){
	rewrite_addr_with_flags(addr, pa(addr), page_flags);
}
static void rewrite_entry(pte_t * addr, int page_flags){
	addr = buddy_allocate_page(0);
	rewrite_flags(addr, page_flags);
}

static void add_map_entry(pte_t * pml4 , phys_t paddr, virt_t virtaddr){
	pte_t * pml4e = pml4 + pml4_i(virtaddr);
	rewrite_entry(pml4e, PTE_PRESENT | PTE_WRITE);
	pte_t * pdpte = pte_level_addr(*pml4e) + pml3_i(virtaddr);
	rewrite_entry(pdpte, PTE_PRESENT | PTE_WRITE);
	pte_t * pde = pte_level_addr(*pdpte) + pml2_i(virtaddr);
	rewrite_addr_with_flags(pde, paddr, PTE_PRESENT | PTE_WRITE | PTE_LARGE);
}

void paging_init(){
	pte_t * pml4 = buddy_allocate_page(0);
	for(phys_t i = 0; i < mmap_get_high_memory_level(); i += PAGE_SIZE_2M) {
		add_map_entry(pml4, i, (virt_t) va(i));
	}
	for(phys_t i = 0; i < TWO_GB; i++){
		add_map_entry(pml4, i, (virt_t) kernel_virt(i));
	}
	store_pml4(pa(pml4));
}
