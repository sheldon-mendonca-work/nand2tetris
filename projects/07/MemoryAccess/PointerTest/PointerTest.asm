// push constant 3030
@3030
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop pointer 0
D=M
@3
D=A
@R14
M=D
@SP
M=M-1
A=M
D=M
@R14
A=M
M=D

// push constant 3040
@3040
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop pointer 1
D=M
@3
D=A
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

// push constant 32
@32
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop this 2
@THIS
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

// push constant 46
@46
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop that 6
@THAT
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

// push pointer 0
D=M
@3
D=A
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push pointer 1
D=M
@3
D=A
@1
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

// push this 2
@THIS
D=M
@2
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

// push that 6
@THAT
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

// Infinite Loop
(PROGRAM_END)
@PROGRAM_END
0;JMP
