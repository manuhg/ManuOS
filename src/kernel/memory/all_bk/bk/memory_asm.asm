[bits 32]
extern page_dir_ptr_tab
global enable_pae_paging
_1lsh5 equ 1<<5

enable_pae_paging:
     mov eax,cr4
     or eax, _1lsh5
     mov cr4,eax
     mov eax,0
     mov eax,page_dir_ptr_tab
     shl eax,5
     mov cr3,eax
     mov eax,cr0
     or eax,0x80000000 ;enable paging by setting bit 31 of cr0 
     mov cr0,eax
     ret
