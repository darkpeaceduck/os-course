#include "buddy_allocator.h"
#include "paging.h"
#include "mmap.h"
#include "memory.h"
#include "boot_allocator.h"
#include "print.h"

#define TWO_GB (0x80000000)

typedef struct{
	phys_t phys_start;
	virt_t virt_start;
	uint64_t page_size;
	uint64_t len;

}map_region;

static map_region AFTER_HOLE = {
	.phys_start = 0,
	.virt_start = VA(0),
	.page_size  = PAGE_SIZE_2M
};

static map_region KERNEL_HIGH = {
	.phys_start = 0,
	.virt_start = KERNEL_VIRT(0),
	.len = TWO_GB,
	.page_size = PAGE_SIZE_2M
};


static void rewrite_addr_with_flags(pte_t * addr, phys_t phys, int page_flags){
	*addr = phys | page_flags;
}

static void rewrite_entry(pte_t * addr, int page_flags){
	void * new_page_addr = boot_allocator_alloc(PAGE_SIZE, PAGE_SIZE);
	rewrite_addr_with_flags(addr, pa(new_page_addr), page_flags);
}

static void add_map_entry(pte_t * pml4 , phys_t paddr, virt_t virtaddr){
	pte_t * pml4e = pml4 + pml4_i(virtaddr);
	if(!pte_present(*pml4e)){
		rewrite_entry(pml4e, PTE_PRESENT | PTE_WRITE);
	}
	pte_t * pdpte = pte_level_addr(*pml4e) + pml3_i(virtaddr);
	if(!pte_present(*pdpte)){
		rewrite_entry(pdpte, PTE_PRESENT | PTE_WRITE);
	}
	pte_t * pde = pte_level_addr(*pdpte) + pml2_i(virtaddr);
	rewrite_addr_with_flags(pde, paddr, PTE_PRESENT | PTE_WRITE | PTE_LARGE);
}

static void recalculate_map_region_lens(){
	AFTER_HOLE.len = mmap_get_high_memory_level();
}

static uint64_t get_region_mem(map_region * region){
	return (region->len / region->page_size + 1) * PAGE_SIZE * 2;
}

uint64_t paging_get_component_size(){
	recalculate_map_region_lens();
	return get_region_mem(&AFTER_HOLE) +
		   get_region_mem(&KERNEL_HIGH);
}

static void mmap_region(pte_t * pml4, map_region * region){
	for(phys_t i = region->phys_start;
			i < region->phys_start + region->len;
			i += region->page_size){
		add_map_entry(pml4, i, region->virt_start + (i - region->phys_start));
	}
}

void paging_init(){
	recalculate_map_region_lens();
	pte_t * pml4 = (pte_t *) va(load_pml4());

	mmap_region(pml4, &AFTER_HOLE);
	mmap_region(pml4, &KERNEL_HIGH);

	store_pml4(pa(pml4));
}
