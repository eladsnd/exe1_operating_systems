#include <stdio.h>
#include "os.h"
#include "os.c"

const int WINDOW_SIZE = 9;

/**introduction:
 * need implement a simulated os  code that handles multi-level (trie-based) page table
 * implement 2 funcs :
 *      1) create\destroy virtual memory mappings in page table
 *      2) check if an address is mapped in a page table
 * */

/*information:
 * 64 bit x86-like CPU
 * address (virtual or physical):
 *        lsb (least significant bit) = 0
 *        msb = 63
 * virtual address :
 *        address size is 64 bits
 *        lower 57 are translation
 *        top 7 identical to bit 56
 *        [ 63 - 57 |     56 - 12    | 11 - 0 ]
 *        [sign ext | virtual page # | offset ]
 * page table structure :
 *        page\frame size is 4kb(4096 b)
 *        Page Table nodes occupy a physical frame => they are 4 KB size
 *        bit 0 : valid bit
 *        bit 1 - 11 : unused and set to zero(no implementation of page access rights)
 *        bit 12 - 63 : page frame number (entry)
 *        [63 - 12 | 11 - 0 |   0   ]
 *        [ frame  | unused | valid?]
 * */

/** virtual memory PT levels:
 * page size is 4KB
 * PTE size is 64 bits (or 8B)
 * witch means a pt can contain 4096\8(B) => 512 PTE's in a page
 * 512 = 2^9 => each symbol is 9b
 * 52 - 7 = 45 bit address
 * 45\9 = 5 => 5 levels of pt
 * */

/* OS physical memory manager: using os.c
 *  1) obtain page num of unused pp :
 *              allocate a physical page (page frame):
 *                  unint64_t alloc_page_frame(void)
 *                          returns physical page number
 *                          contains all zeros
 *  2) obtain the kernal virtual address
 *              void* phys_to_virt(unint64_t phys_addr)
 *                      returns a ptr to the virtual page
 *
 * */

uint16_t* next_pt(int entry , uint16_t* pte,int last)
{
    if((pte[entry] & 1 )== 0)
        return NO_MAPPING;
    if (last)
        return pte[entry];

    return phys_to_virt(pte[entry] - 1);
}

/**
 * pt  -   the physical page number of the page table root
 * vpn -   target virtual page number
 * ppn -   ppn = NO_MAPPING? => destroy vpn mapping
 *         else? => ppn = ppn that vpn is mapped to
 * */
void page_table_update(uint64_t pt,uint64_t vpn ,uint64_t ppn)
{

}
/**
 *  pt  -   the physical page number of the page table root
 *  vpn -   target virtual page number
 *
 * */
uint64_t page_table_query(uint64_t pt, uint64_t vpn)
{
    int pt_levle = 0,entry;
    // receive ptn , witch means the page is at pt*2^12
    uint16_t ppt = pt << 12;
    uint16_t* page_table_root = phys_to_virt(ppt);
    // i got the root of the pt , now i need to go over 5 levels of pt to find mapping
    while(pt_levle = 0<4) {
        entry = (pt_levle*WINDOW_SIZE) & 0x1ff;
        pt_levle++;
        pt_levle = next_pt(entry,pt_levle,0);
    }
     pt_levle = next_pt(entry,pt_levle,1)[entry] >> 12;
    return pt_levle;
}


int main() {
    uint64_t pt = alloc_page_frame();
    pt = alloc_page_frame() ;
    pt = alloc_page_frame() ;

    printf(page_table_query(pt,0xcafe));
    return 0;
}
