[bits 16]
switch_to_pm:
	cli ; Clear interrupts
	lgdt [gdt_descriptor] ; Load our GDT, which defines our PM segments
	
	mov eax, cr0 ; Set the control bit of cr0, a control register to switch to PM
	or eax, 0x1
	mov cr0, eax
	
	jmp CODE_SEG:init_pm ; Execute a far jump to flush CPU instructions

[bits 32]
; Initialise 32 bit registers
init_pm:
	mov ax, DATA_SEG ; Point registers to new data segment defined in GDT
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x90000 ; Update stack position for top of free space
	mov esp, ebp
	
	call begin_pm
	ret