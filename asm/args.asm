; Windows x64 NASM
; Uses MSVCRT printf
; Accepts argv[1]

default rel
extern printf

section .data
    fmt_noarg db "No argument provided", 10, 0
    fmt_arg   db "argv[1] = %s", 10, 0

section .text
global main

; int main(int argc, char** argv)
main:
    ; Windows x64 calling convention:
    ; RCX = argc
    ; RDX = argv

    cmp rcx, 2                  ; argc < 2 ?
    jl  no_argument

    ; argv[1] = *(argv + 8)
    mov r8, [rdx + 8]            ; r8 = argv[1]

    ; printf("argv[1] = %s\n", argv[1])
    lea rcx, [fmt_arg]           ; format string
    mov rdx, r8                  ; string argument
    sub rsp, 40                  ; shadow space (32) + alignment
    call printf
    add rsp, 40
    xor eax, eax
    ret

no_argument:
    lea rcx, [fmt_noarg]
    sub rsp, 40
    call printf
    add rsp, 40
    xor eax, eax
    ret
