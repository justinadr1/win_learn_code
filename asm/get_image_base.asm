; get runtime image base address

bits 64
default rel

section .text
global get_image_base
global main

get_image_base:
    mov rax, [gs:0x60]
    mov rax, [rax + 0x10]
    mov rax, [rax + 0x30]
    mov rbp, rax
    ret

main:
    sub rsp, 40
    call get_image_base
    xor rax, rax
    ret
