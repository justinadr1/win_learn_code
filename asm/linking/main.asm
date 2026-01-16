; main.asm
default rel
extern _myDynamicFunction    ; Import from DLL
extern _ExitProcess@4
section .data
a dq 5
b dq 7
result dq 0

section .text
global main
main:
    mov rcx, [a]            ; first arg
    mov rdx, [b]            ; second arg
    call _myDynamicFunction
    mov [result], rax       ; store return value

    ; Exit program: Windows API ExitProcess
    mov rcx, 0              ; exit code 0
    call _ExitProcess
