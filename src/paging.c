#include "buddy_allocator.h"
#include "paging.h"
#include "mmap.h"
#include "memory.h"
#include "boot_allocator.h"
#include "print.h"

#define TWO_GB (0x80000000)

static paging_map_region AFTER_HOLE = {
	.phys_start = 0,
	.virt_start = VA(0)
};

static paging_map_region KERNEL_HIGH = {
	.phys_start = 0,
	.virt_start = KERNEL_VIRT(0),
	.len = TWO_GB
};

static pte_t * pml4;

#define BOOT_ALLOC 0
#define BUDDY_ALLOC 1
static int mode = BOOT_ALLOC;


static void rewrite_addr_with_flags(pte_t * addr, phys_t phys, int page_flags){
	*addr = phys | page_flags;
}

static void rewrite_entry(pte_t * addr, int page_flags){
	void * new_page_addr;
	if(mode == BOOT_ALLOC) {
		new_page_addr = boot_allocator_alloc(PAGE_SIZE, PAGE_SIZE);
	} else {
		new_page_addr = buddy_allocate_page(0);
	}
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

static uint64_t paging_get_region_mem(paging_map_region * region){
	return (region->len / PAGE_SIZE_2M + 1) * PAGE_SIZE * 2;
}

uint64_t paging_get_component_size(){
	recalculate_map_region_lens();
	return paging_get_region_mem(&AFTER_HOLE) +
		   paging_get_region_mem(&KERNEL_HIGH);
}

void paging_mmap_region(paging_map_region * region){
	for(phys_t i = region->phys_start;
			i < region->phys_start + region->len;
			i += PAGE_SIZE_2M){
		add_map_entry(pml4, i, region->virt_start + (i - region->phys_start));
	}
	store_pml4(pa(pml4));
}

void paging_ummap_region_defaut_holem(paging_map_region * region){
	paging_map_region new_region = {
			.phys_start = PA(region->virt_start),
			.virt_start = region->virt_start,
			.len = region->len
	};
	paging_mmap_region(&new_region);
}

void paging_init(){
	recalculate_map_region_lens();
	pml4 = (pte_t *) va(load_pml4());

	paging_mmap_region(&AFTER_HOLE);
	paging_mmap_region(&KERNEL_HIGH);

	mode = BUDDY_ALLOC;
}
