// FILE: ./projects/08/ProgramFlow/FibonacciSeries/FibonacciSeries.vm

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

// push constant 0
@0
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop that 0
@THAT
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

// push constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop that 1
@THAT
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

// push constant 2
@2
D=A
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

// pop argument 0
@ARG
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

// label LOOP
(null$LOOP)

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

// if-goto COMPUTE_ELEMENT
@SP
M=M-1
A=M
D=M
@null$COMPUTE_ELEMENT
D;JGT

// goto END
@null$END
0;JMP

// label COMPUTE_ELEMENT
(null$COMPUTE_ELEMENT)

// push that 0
@THAT
D=M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push that 1
@THAT
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

// push constant 1
@1
D=A
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

// push constant 1
@1
D=A
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

// pop argument 0
@ARG
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

// goto LOOP
@null$LOOP
0;JMP

// label END
(null$END)

// Infinite Loop
(PROGRAM_END)
@PROGRAM_END
0;JMP
