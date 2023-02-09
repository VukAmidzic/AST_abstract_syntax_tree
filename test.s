#MAIN: 
#ASSIGN: a 2
#ASSIGN: b 7
#ASSIGN: a 49
	#ASSIGN: c 10
#PRINT: 49
#PRINT: 7
#PRINT: 10
#PRINT: 66
.intel_syntax noprefix
.data
  format: .asciz "%d\n"
.text

.global main
main:
  enter 24, 0
  mov rax, 2
  mov QWORD PTR [rbp-8], rax
  mov rax, QWORD PTR [rbp-8]
  shl rax, 2
  push rax
  mov rax, 1
  push rax
  pop rbx
  pop rax
  sub rax, rbx
  mov QWORD PTR [rbp-16], rax
  mov rax, QWORD PTR [rbp-16]
  push rax
  mov rax, QWORD PTR [rbp-16]
  pop rbx
  imul rax, rbx
  mov QWORD PTR [rbp-8], rax
  mov rax, 10
  mov QWORD PTR [rbp-24], rax
  mov rax, QWORD PTR [rbp-8]
  lea rdi, format
  mov rsi, rax
  xor rax, rax
  call printf
  mov rax, QWORD PTR [rbp-16]
  lea rdi, format
  mov rsi, rax
  xor rax, rax
  call printf
  mov rax, QWORD PTR [rbp-24]
  lea rdi, format
  mov rsi, rax
  xor rax, rax
  call printf
  mov rax, QWORD PTR [rbp-8]
  push rax
  mov rax, QWORD PTR [rbp-16]
  pop rbx
  add rax, rbx
  push rax
  mov rax, QWORD PTR [rbp-24]
  pop rbx
  add rax, rbx
  lea rdi, format
  mov rsi, rax
  xor rax, rax
  call printf
  leave
  ret

