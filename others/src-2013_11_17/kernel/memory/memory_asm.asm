[bits 32]
extern page_dir_ptr_tab
global enable_pae_paging
global set_pg_bit
global set_pae_bit
global set_lme_bit
global set_nxe_bit

_1lsh5 equ 1<<5

enable_pae_paging:
     mov eax,cr4
     or eax, _1lsh5
     mov cr4,eax
     ;mov eax,page_dir_ptr_tab
     ;mov eax,[esp+4]
     mov cr3,eax
     mov eax,cr0
     or eax,0x80000000 ;enable paging by setting bit 31 of cr0 
     mov cr0,eax
     ret

set_pg_bit:
     mov eax,cr0
     or eax,0x80000000
     mov cr0,eax
     ret
set_pae_bit:
     mov eax,cr4
     or eax,0x20
     mov cr0,eax
     ret
set_lme_bit:
     ;mov eax,efer
     or eax,0x100
     ;mov efer,eax
     ret
set_nxe_bit:
     ;mov eax,efer
     or eax,0x800
     ;mov efer,eax
     ret
