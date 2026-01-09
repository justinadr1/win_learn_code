; Filename: thread_example.asm
; Assemble: nasm -f win64 thread_example.asm -o thread_example.obj
; Link: link thread_example.obj /subsystem:console kernel32.lib

default rel

extern CreateThread
extern WaitForSingleObject
extern CloseHandle
extern GetStdHandle
extern WriteFile
extern Sleep
extern GetLastError

global main

SECTION .data
    ; Strings to write
    msg_main_start db "Main thread: starting worker", 10
    msg_main_wait db "Main thread: waiting", 10
    msg_main_exit db "Main thread: exiting", 10
    msg_worker_run db "Worker thread: running", 10
    msg_worker_done db "Worker thread: done", 10
    msg_create_fail db "CreateThread failed: ", 0

    len_main_start equ $-msg_main_start
    len_main_wait equ $-msg_main_wait
    len_main_exit equ $-msg_main_exit
    len_worker_run equ $-msg_worker_run
    len_worker_done equ $-msg_worker_done

SECTION .bss
    hThread resq 1
    bytesWritten resq 1

; --------------------------
; Worker thread
; --------------------------
SECTION .text

worker_thread:
    ; param in rcx (unused)
    push rbp
    mov rbp, rsp

    ; Write "Worker thread: running\n"
    mov rcx, -11          ; STD_OUTPUT_HANDLE
    call get_stdout_handle
    mov rdx, msg_worker_run
    mov r8, len_worker_run
    mov r9, bytesWritten
    mov rax, WriteFile
    call rax

    ; Sleep(2500)
    mov ecx, 2500
    call Sleep

    ; Write "Worker thread: done\n"
    mov rcx, -11
    call get_stdout_handle
    mov rdx, msg_worker_done
    mov r8, len_worker_done
    mov r9, bytesWritten
    mov rax, WriteFile
    call rax

    mov eax, 0
    pop rbp
    ret

; --------------------------
; Helper: GetStdHandle
; rcx = handle type
; returns rax = handle
; --------------------------
get_stdout_handle:
    push rax
    mov rax, GetStdHandle
    call rax
    pop rcx
    mov rax, rax
    ret

; --------------------------
; Main function
; --------------------------
main:
    push rbp
    mov rbp, rsp

    ; Get console handle
    mov rcx, -11      ; STD_OUTPUT_HANDLE
    call get_stdout_handle
    mov rbx, rax      ; save stdout handle

    ; Write "Main thread: starting worker\n"
    mov rcx, rbx
    mov rdx, msg_main_start
    mov r8, len_main_start
    mov r9, bytesWritten
    mov rax, WriteFile
    call rax

    ; CreateThread(NULL, 0, worker_thread, NULL, 0, NULL)
    xor rcx, rcx        ; lpThreadAttributes = NULL
    xor rdx, rdx        ; dwStackSize = 0
    lea r8, [rel worker_thread] ; lpStartAddress
    xor r9, r9          ; lpParameter = NULL
    ; 5th and 6th arguments: dwCreationFlags, lpThreadId
    sub rsp, 16          ; shadow space for 2 args
    xor rax, rax         ; dwCreationFlags = 0
    mov [rsp+8], rax     ; lpThreadId = NULL
    call CreateThread
    add rsp, 16
    mov [hThread], rax
    cmp rax, 0
    jne .thread_created

    ; CreateThread failed
    mov rcx, rbx
    mov rdx, msg_create_fail
    mov r8, 21            ; length of "CreateThread failed: "
    mov r9, bytesWritten
    mov rax, WriteFile
    call rax

    ; GetLastError
    call GetLastError
    mov eax, 1
    jmp .exit

.thread_created:
    ; Write "Main thread: waiting\n"
    mov rcx, rbx
    mov rdx, msg_main_wait
    mov r8, len_main_wait
    mov r9, bytesWritten
    mov rax, WriteFile
    call rax

    ; WaitForSingleObject(thread, INFINITE)
    mov rcx, [hThread]
    mov edx, 0xFFFFFFFF      ; INFINITE
    call WaitForSingleObject

    ; CloseHandle(thread)
    mov rcx, [hThread]
    call CloseHandle

    ; Write "Main thread: exiting\n"
    mov rcx, rbx
    mov rdx, msg_main_exit
    mov r8, len_main_exit
    mov r9, bytesWritten
    mov rax, WriteFile
    call rax

    mov eax, 0

.exit:
    pop rbp
    ret
