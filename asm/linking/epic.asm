bits 64
default rel

extern puts

section .data
    msg db "Epic message", 0

section .text
    global _epicFunction
    global DllMain

_epicFunction:
    sub rsp, 40
    lea rcx, [msg]
    call puts
    add rsp, 40
    ret

DllMain:
    mov eax, 1
    ret
