;read write registers


global read_cr0
global read_cr3
global read_cr4
global read_eax  for testing
global write_cr0
global write_cr3
global write_cr4
global write_eax for testing

read_cr0:
mov eax,cr0
ret
write_cr0:
mov eax,[esp+4]
mov cr0,eax
ret

read_cr3:
mov eax,cr3
ret

write_cr3:
mov eax,[esp+4]
mov cr3,eax
ret

read_cr4:
mov eax,cr4
ret

write_cr4:
mov eax,[esp+4]
mov cr4,eax
ret

read_eax:
ret

write_eax:
mov eax,[esp+4]
ret

read_ebx:
mov eax,ebx
ret

write_ebx:
mov eax,[esp+4]
mov ebx,eax
ret

read_ecx:
mov eax,ecx
ret

write_ecx:
mov eax,[esp+4]
mov ecx,eax
ret
read_edx:
mov eax,edx
ret

write_edx:
mov eax,[esp+4]
mov edx,eax
ret