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


// FILE: ./projects/08/FunctionCalls//StaticsTest/Class1.vm

// function Class1.set 0
(Class1.set)
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

// pop static 0
@SP
M=M-1
A=M
D=M
@Class1.0
M=D

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

// pop static 1
@SP
M=M-1
A=M
D=M
@Class1.1
M=D

// push constant 0
@0
D=A
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

// function Class1.get 0
(Class1.get)
@SP
A=M
@0
D=A
@SP
M=D+M

// push static 0
@Class1.0
D=M
@SP
A=M
M=D
@SP
M=M+1

// push static 1
@Class1.1
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

// FILE: ./projects/08/FunctionCalls//StaticsTest/Class2.vm

// function Class2.set 0
(Class2.set)
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

// pop static 0
@SP
M=M-1
A=M
D=M
@Class2.0
M=D

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

// pop static 1
@SP
M=M-1
A=M
D=M
@Class2.1
M=D

// push constant 0
@0
D=A
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

// function Class2.get 0
(Class2.get)
@SP
A=M
@0
D=A
@SP
M=D+M

// push static 0
@Class2.0
D=M
@SP
A=M
M=D
@SP
M=M+1

// push static 1
@Class2.1
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

// FILE: ./projects/08/FunctionCalls//StaticsTest/Sys.vm

// function Sys.init 0
(Sys.init)
@SP
A=M
@0
D=A
@SP
M=D+M

// push constant 6
@6
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 8
@8
D=A
@SP
A=M
M=D
@SP
M=M+1

// call Class1.set 2
// -- Push return address on stack
@_RETURN_Class1.set_28
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
@2
D=D-A
@ARG
M=D

// -- LCL = SP
@SP
D=M
@LCL
M=D
@Class1.set
0;JMP
(_RETURN_Class1.set_28)

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

// push constant 23
@23
D=A
@SP
A=M
M=D
@SP
M=M+1

// push constant 15
@15
D=A
@SP
A=M
M=D
@SP
M=M+1

// call Class2.set 2
// -- Push return address on stack
@_RETURN_Class2.set_32
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
@2
D=D-A
@ARG
M=D

// -- LCL = SP
@SP
D=M
@LCL
M=D
@Class2.set
0;JMP
(_RETURN_Class2.set_32)

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

// call Class1.get 0
// -- Push return address on stack
@_RETURN_Class1.get_34
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
@Class1.get
0;JMP
(_RETURN_Class1.get_34)

// call Class2.get 0
// -- Push return address on stack
@_RETURN_Class2.get_35
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
@Class2.get
0;JMP
(_RETURN_Class2.get_35)

// label END
(Sys.init$END)

// goto END
@Sys.init$END
0;JMP

