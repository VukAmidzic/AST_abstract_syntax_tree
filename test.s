#MAIN: 
#ASSIGN: a 1
#ASSIGN: b 4
#PRINT: -16
.intel_syntax noprefix
.data
  format: .asciz "%d\n"
.text

.global main
main:
  enter 32, 0
  mov rax, 1
  mov QWORD PTR [rbp-8], rax
  mov rax, QWORD PTR [rbp-8]
  push rax
  mov rax, QWORD PTR [rbp-8]
  pop rbx
  add rax, rbx
  push rax
  mov rax, QWORD PTR [rbp-8]
  pop rbx
  add rax, rbx
  push rax
  mov rax, QWORD PTR [rbp-8]
  pop rbx
  add rax, rbx
  mov QWORD PTR [rbp-16], rax
  mov rax, 0
  push rax
  mov rax, QWORD PTR [rbp-16]
  push rax
  mov rax, QWORD PTR [rbp-16]
  pop rbx
  imul rax, rbx
  push rax
  pop rbx
  pop rax
  sub rax, rbx
  lea rdi, format
  mov rsi, rax
  xor rax, rax
  call printf
  leave
  ret

