.intel_syntax noprefix
.text
.global main
main:
     mov rax, 10
     push rax
     mov rax, 2
     push rax
     mov rax, 1
     push rax
     mov rax, 1
     pop rbx
     add rax, rbx
     pop rbx
     mul rbx
     pop rbx
     mul rbx
     ret

