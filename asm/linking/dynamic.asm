; dynamic.asm
default rel
section .text
global _myDynamicFunction  ; Exported function

_myDynamicFunction:
    ; Arguments in Windows x64: RCX = a, RDX = b
    mov rax, rcx           ; rax = a
    add rax, rdx           ; rax = a + b
    ret
