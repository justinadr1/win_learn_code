; dllmain.asm
default rel
section .text
global DllMain
DllMain:
    ; Parameters:
    ; RCX = hinstDLL
    ; RDX = reason
    ; R8  = reserved
    mov eax, 1          ; TRUE
    ret
