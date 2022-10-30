;
; Register definitions
; --------------------------
; print.asm: dx = pointer to string
;
; disk.asm : dl = disk to read from, dh = # sectors to read, load sectors to es:bx (BIOS originally stores boot disk in dl)
;

; Start of main program
[org 0x7c00]
KERNEL_OFFSET equ 0x1000
	mov bp, 0x9000 ; Here we set our stack safely out of the
	mov sp, bp
	
	mov [BOOT_DRIVE], dl
	
	mov bx, MSG_BOOT_REAL_MODE
	call print_rm
	call printnl_rm
	
	call load_kernel
	
	call switch_to_pm

	jmp $ ; Jump to the current address ( i.e. forever ) .

; End of main program
	

; Include helper definitions
%include "./boot/real-mode/print.asm"
%include "./boot/real-mode/disk.asm"
%include "./boot/protected-mode/gdt.asm"
%include "./boot/protected-mode/switch.asm"
%include "./boot/protected-mode/print.asm"

[bits 16]
; load_kernel
load_kernel :
	mov bx, MSG_LOAD_KERNEL ; Print a message to say we are loading the kernel
	call print_rm
	call printnl_rm
	mov bx, KERNEL_OFFSET ; Load first 15 sectors from kernel offset
	mov dh, 45
	mov dl, [BOOT_DRIVE]
	call diskload_rm
	ret

[bits 32]
begin_pm:
	mov ebx, MSG_BOOT_PROT_MODE
	call print_pm
	
	call KERNEL_OFFSET ; Jump to kernel offset
	
	jmp $

; Global variables
BOOT_DRIVE: db 0
MSG_BOOT_REAL_MODE: db 'Booting OS in 16-bit real mode...', 0
MSG_BOOT_PROT_MODE: db 'Booted into 32-bit protected mode...', 0
MSG_LOAD_KERNEL: db 'Succesfully loaded kernel!', 0

;
; Padding and magic BIOS number.
;
times 510-($-$$) db 0 ; Pad the boot sector out with zeros
dw 0xaa55 ; Last two bytes form the magic number,
; so BIOS knows we are a boot sector.