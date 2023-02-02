#MAIN: 
#ASSIGN: a 3
#ASSIGN: b 5
#PRINT: 3
.intel_syntax noprefix
.data
  format: .asciz "%d\n"
.text

.global main
main:
  enter 0,0
  mov rax,3
  mov QWORD PTR [rbp-4], rax
  mov rax, QWORD PTR [rbp-4]
  push rax
  mov rax,1
  pop rbx
  add rax, rbx
  push rax
  mov rax,1
  pop rbx
  add rax, rbx
  mov QWORD PTR [rbp-6], rax
  mov rax,1
  push rax
  mov rax,1
  pop rbx
  add rax, rbx
  push rax
  mov rax,1
  pop rbx
  add rax, rbx
  lea rdi, format
  mov rsi, rax
  xor rax, rax
  call printf
  leave
  ret

