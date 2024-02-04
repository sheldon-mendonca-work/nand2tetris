// Initial Set up
@256
D=A
@SP
M=D

// call Sys.init 0
// -- Push return address on stack
@_RETURN_Sys.init_0
D=A
@SP
A=M
M=D
@SP
M=M+1
// -- Push LCL on stack
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push ARG on stack
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push THIS on stack
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push THAT on stack
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- ARG = SP-n-5
D=M
@5
D=D-A
@0
D=D-A
@ARG
M=D

// -- LCL = SP
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
(_RETURN_Sys.init_0)


// FILE: ./projects/08/FunctionCalls//FibonacciElement/Main.vm

// function Main.fibonacci 0
(Main.fibonacci)
@SP
A=M
@0
D=A
@SP
M=D+M

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

// lt
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@COMPARISON_TRUE_4
D;JLT
@SP
A=M
M=0
@COMPARISON_END_4
0;JMP
(COMPARISON_TRUE_4)
@SP
A=M
M=-1
(COMPARISON_END_4)
@SP
M=M+1

// if-goto N_LT_2
@SP
M=M-1
A=M
D=M
@Main.fibonacci$N_LT_2
D;JNE

// goto N_GE_2
@Main.fibonacci$N_GE_2
0;JMP

// label N_LT_2
(Main.fibonacci$N_LT_2)

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

// return
// -- Store LCL in R13
@LCL
D=M
@R13
M=D

// -- R14 = R13-5
@5
A=D-A
D=M
@R14
M=D

// -- *ARG=pop()
@SP
AM=M-1
D=M
@ARG
A=M
M=D

// -- SP=ARG+1
@ARG
D=M+1
@SP
M=D

// -- THAT=*(R13-1)
@R13
D=M-1
AM=D
D=M
@THAT
M=D

// -- THIS=*(R13-2)
@R13
D=M-1
AM=D
D=M
@THIS
M=D

// -- ARG=*(R13-3)
@R13
D=M-1
AM=D
D=M
@ARG
M=D

// -- LCL=*(R13-4)
@R13
D=M-1
AM=D
D=M
@LCL
M=D

// -- goto R14
@R14
A=M
0;JMP

// label N_GE_2
(Main.fibonacci$N_GE_2)

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

// call Main.fibonacci 1
// -- Push return address on stack
@_RETURN_Main.fibonacci_11
D=A
@SP
A=M
M=D
@SP
M=M+1
// -- Push LCL on stack
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push ARG on stack
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push THIS on stack
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push THAT on stack
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- ARG = SP-n-5
D=M
@5
D=D-A
@1
D=D-A
@ARG
M=D

// -- LCL = SP
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(_RETURN_Main.fibonacci_11)

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

// call Main.fibonacci 1
// -- Push return address on stack
@_RETURN_Main.fibonacci_15
D=A
@SP
A=M
M=D
@SP
M=M+1
// -- Push LCL on stack
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push ARG on stack
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push THIS on stack
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push THAT on stack
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- ARG = SP-n-5
D=M
@5
D=D-A
@1
D=D-A
@ARG
M=D

// -- LCL = SP
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(_RETURN_Main.fibonacci_15)

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

// return
// -- Store LCL in R13
@LCL
D=M
@R13
M=D

// -- R14 = R13-5
@5
A=D-A
D=M
@R14
M=D

// -- *ARG=pop()
@SP
AM=M-1
D=M
@ARG
A=M
M=D

// -- SP=ARG+1
@ARG
D=M+1
@SP
M=D

// -- THAT=*(R13-1)
@R13
D=M-1
AM=D
D=M
@THAT
M=D

// -- THIS=*(R13-2)
@R13
D=M-1
AM=D
D=M
@THIS
M=D

// -- ARG=*(R13-3)
@R13
D=M-1
AM=D
D=M
@ARG
M=D

// -- LCL=*(R13-4)
@R13
D=M-1
AM=D
D=M
@LCL
M=D

// -- goto R14
@R14
A=M
0;JMP

// FILE: ./projects/08/FunctionCalls//FibonacciElement/Sys.vm

// function Sys.init 0
(Sys.init)
@SP
A=M
@0
D=A
@SP
M=D+M

// push constant 4
@4
D=A
@SP
A=M
M=D
@SP
M=M+1

// call Main.fibonacci 1
// -- Push return address on stack
@_RETURN_Main.fibonacci_20
D=A
@SP
A=M
M=D
@SP
M=M+1
// -- Push LCL on stack
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push ARG on stack
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push THIS on stack
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- Push THAT on stack
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
// -- ARG = SP-n-5
D=M
@5
D=D-A
@1
D=D-A
@ARG
M=D

// -- LCL = SP
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(_RETURN_Main.fibonacci_20)

// label END
(Sys.init$END)

// goto END
@Sys.init$END
0;JMP

