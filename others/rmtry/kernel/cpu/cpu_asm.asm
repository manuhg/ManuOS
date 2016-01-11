[bits 32]
 extern print_error
 extern _printf
 extern outbyte
 extern _print_hex

[section .text]

 global cpu_cpuid_supported
 global cpu_find_vendorID
 global dword_byterev
 global cpu_find_features
 global _ebx_val
 global _edx_val
 global _ecx_val

cpu_cpuid_supported:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 0x200000
    push eax
    popfd
    pushfd
    pop eax
    xor eax, ecx
    shr eax, 21
    and eax, 1
    push ecx
    popfd
    ret

cpu_find_vendorID:
    call cpu_cpuid_supported
    cmp eax,1
    jge .eax_is1
    push err_str
    call print_error
    mov eax,0
    ret    
  .eax_is1:
    mov eax,0
    cpuid
    mov [_ebx_val],ebx
    mov [_edx_val],edx
    mov [_ecx_val],ecx
    mov byte [_cpuidstr_end],0
    

    push _ebx_val
    call dword_byterev
    push _edx_val
    call dword_byterev
    push _ecx_val
    call dword_byterev
    
    mov byte [_cpuidstr_end],0
    push _ebx_val
    call _printf
    mov eax,_ebx_val
.return:
    ret
    
cpu_find_features:
    mov eax,1
    cpuid    
    mov [_ebx_val],ebx
    mov [_edx_val],edx
    mov [_ecx_val],ecx
    mov byte [_cpuidstr_end],0    
    mov eax,_ebx_val
    
    ;push ebx
    ;call _print_hex
    
    ;mov eax,[_ebx_val]
    ;push eax
    ;call _print_hex
    ret
    
dword_byterev:
    mov eax,[esp+4]
    mov ebx,eax
    mov ecx,0
    
    and eax,0xff
    shl eax,24
    mov ecx,eax
    
    mov eax,ebx
    and eax,0xff00
    shl eax,8
    or  ecx,eax
    
    mov eax,ebx
    and eax,0xff0000
    shr eax,8
    or  ecx,eax
    
    mov eax,ebx
    and eax,0xff000000
    shr eax,24
    or  ecx,eax
    
    mov ecx,eax   
    ret
    
[section .data]
 err_str db 'cpuid not supported!',0
 
[section .bss]
 _ebx_val: resd 1
 _edx_val: resd 1
 _ecx_val: resd 1
 _cpuidstr_end: resb 1
