// FILE: ./projects/08/ProgramFlow/BasicLoop/BasicLoop.vm

// push constant 0
@0
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

// if-goto LOOP
@SP
M=M-1
A=M
D=M
@null$LOOP
D;JGT

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

// Infinite Loop
(PROGRAM_END)
@PROGRAM_END
0;JMP
