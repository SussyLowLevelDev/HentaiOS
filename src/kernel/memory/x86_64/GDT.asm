bits 64
global load_gdt

GDT64:                           ; Global Descriptor Table (64-bit).
    .Null: equ $ - GDT64         ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
    .Code: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .Data: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    .UserCode: equ $ - GDT64     ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 11111010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .UserData: equ $ - GDT64     ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 11110010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    TSSDesc:
        dq 0
        dq 0

    Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1            ; Limit.
    dq GDT64                    ; Base.


load_gdt:
    cli                             ; Clear interrupt flag so nothing weird happens.
    lgdt [Pointer]                  ; Load the GDT pointer into the CPU.
    mov rax, GDT64.Data             ; Set RAX to the data selector.
    mov ds, rax                     ; Set DS to data.
    mov es, rax                     ; Set ES to data.
    mov fs, rax                     ; Set FS to data.
    mov gs, rax                     ; Set GS to data.
    mov ss, rax                     ; Set SS to data.
    pop rdi                         ; The return address with be popped from the stack frame into RDI.
    mov rax, GDT64.Code             ; Set RAX to the code segment.
    push rax                        ; Push code segment (this will be loaded into CS).
    push rdi                        ; Push the returna ddress.
    retfq                           ; Far return (To load code selector into CS).
