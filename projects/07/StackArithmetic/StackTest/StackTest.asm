// FILE: ./projects/07/StackArithmetic//StackTest/StackTest.vm

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// eq
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_3
D;JEQ
@SP
A=M
M=0
@COMPARISON_END_3
0;JMP
(COMPARISON_TRUE_3)
@SP
A=M
M=-1
(COMPARISON_END_3)
@SP
M=M+1

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

// eq
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_6
D;JEQ
@SP
A=M
M=0
@COMPARISON_END_6
0;JMP
(COMPARISON_TRUE_6)
@SP
A=M
M=-1
(COMPARISON_END_6)
@SP
M=M+1

// push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// eq
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_9
D;JEQ
@SP
A=M
M=0
@COMPARISON_END_9
0;JMP
(COMPARISON_TRUE_9)
@SP
A=M
M=-1
(COMPARISON_END_9)
@SP
M=M+1

// push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// lt
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_12
D;JLT
@SP
A=M
M=0
@COMPARISON_END_12
0;JMP
(COMPARISON_TRUE_12)
@SP
A=M
M=-1
(COMPARISON_END_12)
@SP
M=M+1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1

// lt
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_15
D;JLT
@SP
A=M
M=0
@COMPARISON_END_15
0;JMP
(COMPARISON_TRUE_15)
@SP
A=M
M=-1
(COMPARISON_END_15)
@SP
M=M+1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

// lt
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_18
D;JLT
@SP
A=M
M=0
@COMPARISON_END_18
0;JMP
(COMPARISON_TRUE_18)
@SP
A=M
M=-1
(COMPARISON_END_18)
@SP
M=M+1

// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// gt
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_21
D;JGT
@SP
A=M
M=0
@COMPARISON_END_21
0;JMP
(COMPARISON_TRUE_21)
@SP
A=M
M=-1
(COMPARISON_END_21)
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

// gt
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_24
D;JGT
@SP
A=M
M=0
@COMPARISON_END_24
0;JMP
(COMPARISON_TRUE_24)
@SP
A=M
M=-1
(COMPARISON_END_24)
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

// gt
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_27
D;JGT
@SP
A=M
M=0
@COMPARISON_END_27
0;JMP
(COMPARISON_TRUE_27)
@SP
A=M
M=-1
(COMPARISON_END_27)
@SP
M=M+1

// push constant 57
@57
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 31
@31
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 53
@53
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

// push constant 112
@112
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

// neg
@SP
M=M-1
A=M
M=-M
@SP
M=M+1

// and
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=D&M
M=D
@SP
M=M+1

// push constant 82
@82
D=A
@SP
A=M
M=D
@SP
M=M+1

// or
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=D|M
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

