
default rel
extern printf
extern ExitProcess

section .data
    num db "%i", 0
    lst db 10, 0
    nxt db ", ", 0   
    
section .text
global main

fib:
    push rbp
    mov rbp, rsp
    sub rsp, 48

    mov dword [rbp-4], 0
    mov dword [rbp-8], 1
    mov dword [rbp-16], 0

.loop:
    cmp dword [rbp-16], 10
    jge .exit
    
    lea rcx, [num]
    mov edx, [rbp-4]
    call printf

    cmp dword [rbp-16], 9
    jne .continue

    lea rcx, [lst]
    call printf
    jmp .exit

.continue:
    lea rcx, [nxt]
    call printf
    
    mov eax, dword [rbp-4]
    add eax, dword [rbp-8]
    mov dword [rbp-12], eax

    mov eax, [rbp-8]
    mov dword [rbp-4], eax

    mov eax, dword [rbp-12]
    mov dword [rbp-8], eax

    inc dword [rbp-16]
    jmp .loop

.exit:
    add rsp, 48
    pop rbp
    ret

main:
    sub rsp, 40              
    call fib                
    xor ecx, ecx
    call ExitProcess