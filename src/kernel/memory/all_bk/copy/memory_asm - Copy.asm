[bits 32]
extern page
;global enable_pae_paging
_1lsh5 equ 1<<5

enable_pae_paging:
     mov eax,cr4
     or eax, _1lsh5
     mov cr4,eax
    ; mov eax,[pdpt]
     mov cr3,eax
     mov eax,cr0
     or eax,0x80000000
     mov cr0,eax
     ret