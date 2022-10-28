; Loads the IDT defined in '_idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
global idt_load
extern idt_ptr
idt_load:
    lidt [idt_ptr]
    ret

%macro ISR_NOERRORCODE 1
global ISR%1
ISR%1:
    cli
    push 0
    push %1         ; Push interrupt number
    jmp isr_common_stub

%endmacro

%macro ISR_ERRORCODE 1
global ISR%1
ISR%1:
    cli
                    ; CPU pushes error code
    push %1         ; Push interrupt number
    jmp isr_common_stub

%endmacro

%include "./kernel/cpu/idt_include.asm"

; We call a C function in here. We need to let the assembler know
; that '_fault_handler' exists in another file
extern fault_handler

; ; This is our common ISR stub. It saves the processor state, sets
; ; up for kernel mode segments, calls the C-level fault handler,
; ; and finally restores the stack frame.
; isr_common_stub:
;     ; 1. Save CPU state
; 	pusha ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
; 	mov ax, ds ; Lower 16-bits of eax = ds.
; 	push eax ; save the data segment descriptor
; 	mov ax, 0x10  ; kernel data segment descriptor
; 	mov ds, ax
; 	mov es, ax
; 	mov fs, ax
; 	mov gs, ax
	
;     ; 2. Call C handler
; 	call fault_handler
	
;     ; 3. Restore state
; 	pop eax 
; 	mov ds, ax
; 	mov es, ax
; 	mov fs, ax
; 	mov gs, ax
; 	popa
; 	add esp, 8 ; Cleans up the pushed error code and pushed ISR number
; 	sti
; 	iret ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, fault_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!