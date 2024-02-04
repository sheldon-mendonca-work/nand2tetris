// push constant 10
@10
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop local 0
@LCL
D=M
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// push constant 21
@21
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 22
@22
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop argument 2
@ARG
D=M
@2
D=A+D
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// pop argument 1
@ARG
D=M
@1
D=A+D
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// push constant 36
@36
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop this 6
@THIS
D=M
@6
D=A+D
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// push constant 42
@42
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 45
@45
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop that 5
@THAT
D=M
@5
D=A+D
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// pop that 2
@THAT
D=M
@2
D=A+D
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// push constant 510
@510
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop temp 6
D=M
@5
D=A
@6
D=A+D
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// push local 0
@LCL
D=M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push that 5
@THAT
D=M
@5
D=A+D
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// add
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M+D
M=D
@SP
M=M+1

// push argument 1
@ARG
D=M
@1
D=A+D
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// sub
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
M=D
@SP
M=M+1

// push this 6
@THIS
D=M
@6
D=A+D
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push this 6
@THIS
D=M
@6
D=A+D
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// add
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M+D
M=D
@SP
M=M+1

// sub
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
M=D
@SP
M=M+1

// push temp 6
D=M
@5
D=A
@6
D=A+D
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// add
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M+D
M=D
@SP
M=M+1

// Infinite Loop
(PROGRAM_END)
@PROGRAM_END
0;JMP
