.intel_syntax noprefix
.extern printf
.data
     format: .asciz "%d\n"
.text
.global main
main:
     push rbx
     mov rax, 1
     lea rdi, format
     mov rsi, rax
     xor rax, rax
     call printf
     pop rbx
     ret

