.intel_syntax noprefix
.text
.global main
main:
     mov rax, 5
     push rax
     mov rax, 1
     pop rbx
     add rax, rbx
     push rax
     mov rax, 2
     pop rbx
     mul rbx
     push rax
     mov rax, 3
     pop rbx
     push rax
     mov rax, rbx
     pop rbx
     xor rdx, rdx
     idiv rbx
     push rax
     mov rax, 1
     pop rbx
     add rax, rbx
     ret

