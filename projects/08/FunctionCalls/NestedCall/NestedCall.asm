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


// FILE: ./projects/08/FunctionCalls//NestedCall/Sys.vm

// function Sys.init 0
(Sys.init)
@SP
A=M
@0
D=A
@SP
M=D+M

// push constant 4000
@4000
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

// push constant 5000
@5000
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

// call Sys.main 0
// -- Push return address on stack
@_RETURN_Sys.main_6
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
@Sys.main
0;JMP
(_RETURN_Sys.main_6)

// pop temp 1
D=M
@5
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

// label LOOP
(Sys.init$LOOP)

// goto LOOP
@Sys.init$LOOP
0;JMP

// function Sys.main 5
(Sys.main)
@SP
A=M
M=0
A=A+1
M=0
A=A+1
M=0
A=A+1
M=0
A=A+1
M=0
A=A+1
@5
D=A
@SP
M=D+M

// push constant 4001
@4001
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

// push constant 5001
@5001
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

// push constant 200
@200
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop local 1
@LCL
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

// push constant 40
@40
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop local 2
@LCL
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

// push constant 6
@6
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop local 3
@LCL
D=M
@3
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

// push constant 123
@123
D=A
@SP
A=M
M=D
@SP
M=M+1

// call Sys.add12 1
// -- Push return address on stack
@_RETURN_Sys.add12_21
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
@Sys.add12
0;JMP
(_RETURN_Sys.add12_21)

// pop temp 0
D=M
@5
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

// push local 2
@LCL
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

// push local 3
@LCL
D=M
@3
D=A+D
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// push local 4
@LCL
D=M
@4
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

// function Sys.add12 0
(Sys.add12)
@SP
A=M
@0
D=A
@SP
M=D+M

// push constant 4002
@4002
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

// push constant 5002
@5002
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

// push constant 12
@12
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

