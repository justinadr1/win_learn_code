
default rel
extern printf
extern ExitProcess

section .data
    fmt db "fib(%d) = %lld", 10, 0
    n   dd 10                ; compute fib(10)
    x   dd 5588019

section .text
global main

main:
    sub rsp, 40              ; shadow space + alignment
    
    mov ecx, [n]             ; n
    call fib                 ; RAX = fib(n)
    nop
    nop
    ; printf("fib(%d) = %lld\n", n, result)
    lea rcx, [fmt]           ; format
    mov edx, [n]             ; int n
    mov r8, rax              ; result
    xor r9d, r9d
    call printf

    xor ecx, ecx
    call ExitProcess

; ---------------------------------------
; long long fib(int n)
; RCX = n
; RAX = result
; ---------------------------------------
fib:
    xor rax, rax             ; a = 0
    mov rbx, 1               ; b = 1

.loop:
    test ecx, ecx
    jz .done

    mov rdx, rax
    add rdx, rbx             ; t = a + b
    mov rax, rbx             ; a = b
    mov rbx, rdx             ; b = t
    dec ecx
    jmp .loop

.done:
    ret
