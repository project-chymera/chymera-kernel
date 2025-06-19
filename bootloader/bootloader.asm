;this is a basic bootloader for the system
org 0x7c00
bits 16

main:

print_str:
	mov si, hello
	mov ah, 0x0e
.next_char:
	lodsb
	or al, al
	jz halt
	int 0x10
	jmp .next_char

halt:
	cli
	hlt

times 510-($-$$) db 0
dw 0xaa55
