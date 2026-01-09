; ==================================================
; Windows x64 NASM
; Win32 API version (kernel32.dll)
; ReadFile / WriteFile
; VirtualAlloc / VirtualFree
; Sleep
; ==================================================

default rel

extern GetStdHandle
extern ReadFile
extern WriteFile
extern ExitProcess
extern VirtualAlloc
extern VirtualFree
extern Sleep

STD_INPUT_HANDLE  equ -10
STD_OUTPUT_HANDLE equ -11

MEM_COMMIT  equ 0x1000
MEM_RESERVE equ 0x2000
MEM_RELEASE equ 0x8000
PAGE_READWRITE equ 0x04

section .data
    bytes_read     dq 0
    bytes_written  dq 0

section .text
global main

main:
    ; ---------------------------------
    ; Get STDIN handle
    ; ---------------------------------
    mov ecx, STD_INPUT_HANDLE
    sub rsp, 40
    call GetStdHandle
    add rsp, 40
    mov r12, rax

    ; ---------------------------------
    ; Get STDOUT handle
    ; ---------------------------------
    mov ecx, STD_OUTPUT_HANDLE
    sub rsp, 40
    call GetStdHandle
    add rsp, 40
    mov r13, rax

    ; ---------------------------------
    ; VirtualAlloc(NULL, 128, COMMIT|RESERVE, RW)
    ; ---------------------------------
    xor rcx, rcx
    mov rdx, 128
    mov r8d, MEM_COMMIT | MEM_RESERVE
    mov r9d, PAGE_READWRITE

    sub rsp, 40
    call VirtualAlloc
    add rsp, 40

    mov r15, rax
    test r15, r15
    jz exit

    ; ---------------------------------
    ; ReadFile(STDIN, buffer, 128, &bytes_read, NULL)
    ; ---------------------------------
    mov rcx, r12
    mov rdx, r15
    mov r8d, 128
    lea r9, [bytes_read]

    sub rsp, 40
    mov qword [rsp+32], 0
    call ReadFile
    add rsp, 40

    ; ---------------------------------
    ; WriteFile(STDOUT, buffer, bytes_read, &bytes_written, NULL)
    ; ---------------------------------
    mov rcx, r13
    mov rdx, r15
    mov r8,  [bytes_read]
    lea r9,  [bytes_written]

    sub rsp, 40
    mov qword [rsp+32], 0
    call WriteFile
    add rsp, 40

    ; ---------------------------------
    ; Sleep(3000 ms)
    ; ---------------------------------
    mov ecx, 3000
    sub rsp, 40
    call Sleep
    add rsp, 40

    ; ---------------------------------
    ; VirtualFree(buffer, 0, MEM_RELEASE)
    ; ---------------------------------
    mov rcx, r15
    xor edx, edx
    mov r8d, MEM_RELEASE

    sub rsp, 40
    call VirtualFree
    add rsp, 40

exit:
    xor ecx, ecx
    call ExitProcess
