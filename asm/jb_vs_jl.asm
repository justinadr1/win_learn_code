extern GetStdHandle
extern WriteConsoleA
extern ExitProcess

section .data
msg_jb db "JB branch taken (unsigned comparison)", 10, 0
len_jb equ $ - msg_jb

msg_jl db "JL branch taken (signed comparison)", 10, 0
len_jl equ $ - msg_jl

section .bss

section .text
global main
main:

    ; --- Unsigned comparison ---
    mov eax, 0xFFFFFFFF      ; 4294967295 unsigned
    mov ebx, 1               ; 1 unsigned
    cmp eax, ebx             ; Compare eax - ebx
    jb unsigned_taken         ; Jump if below (CF=1)

    ; --- Signed comparison ---
    mov eax, -1              ; signed -1
    mov ebx, 1               ; signed 1
    cmp eax, ebx             ; Compare eax - ebx
    jl signed_taken           ; Jump if less (SF != OF)

    jmp exit_program          ; If no branch taken, exit

; -------------------------------
unsigned_taken:
    ; Get handle
    mov rcx, -11              ; STD_OUTPUT_HANDLE
    call GetStdHandle          ; handle returned in RAX

    ; WriteConsoleA
    sub rsp, 40               ; 32-byte shadow + 8 stack for lpReserved
    mov rcx, rax              ; hConsoleOutput
    mov rdx, msg_jb           ; lpBuffer
    mov r8, len_jb            ; nNumberOfCharsToWrite
    lea r9, [rsp+32]          ; lpNumberOfCharsWritten
    mov qword [rsp+32], 0     ; lpReserved = NULL
    call WriteConsoleA
    add rsp, 40

; -------------------------------
signed_taken:
    ; Get handle
    mov rcx, -11              ; STD_OUTPUT_HANDLE
    call GetStdHandle          ; handle returned in RAX

    ; WriteConsoleA
    sub rsp, 40
    mov rcx, rax              ; hConsoleOutput
    mov rdx, msg_jl           ; lpBuffer
    mov r8, len_jl            ; nNumberOfCharsToWrite
    lea r9, [rsp+32]          ; lpNumberOfCharsWritten
    mov qword [rsp+32], 0     ; lpReserved = NULL
    call WriteConsoleA
    add rsp, 40

; -------------------------------
exit_program:
    mov rcx, 0               ; exit code
    call ExitProcess

