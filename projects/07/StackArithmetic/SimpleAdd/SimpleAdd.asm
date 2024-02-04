// push constant 7
@7
D=A
@SP
M=D
M=M+1

// push constant 8
@8
D=A
@SP
M=D
M=M+1

// add
@SP
M=M-1
D=M
@SP
M=M-1
D=M+D
M=D
@SP
M=M+1

// Infinite Loop
(PROGRAM_END)
@PROGRAM_END
0;JMP
