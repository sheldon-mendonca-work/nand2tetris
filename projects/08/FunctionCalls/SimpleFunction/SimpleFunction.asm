// FILE: ./projects/08/FunctionCalls/SimpleFunction/SimpleFunction.vm

// function SimpleFunction.test 2
(SimpleFunction.test)
@SP
A=M
M=0
A=A+1
M=0
A=A+1
@2
D=A
@SP
M=D+M

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

// push local 1
@LCL
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

// not
@SP
M=M-1
A=M
M=!M
@SP
M=M+1

// push argument 0
@ARG
D=M
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

// return
@LCL
D=M
@R13
M=D
@5
A=D-A
D=M
@R14
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R13
D=M-1
AM=D
D=M
@THAT
M=D
@R13
D=M-1
AM=D
D=M
@THIS
M=D
@R13
D=M-1
AM=D
D=M
@ARG
M=D
@R13
D=M-1
AM=D
D=M
@LCL
M=D
@R14
A=M
0;JMP

// Infinite Loop
(PROGRAM_END)
@PROGRAM_END
0;JMP
