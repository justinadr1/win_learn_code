bits 64
default rel

extern _epicFunction
extern ExitProcess

section .text
    global main

main:
    sub rsp, 40
    call _epicFunction
    xor ecx, ecx
    call ExitProcess
