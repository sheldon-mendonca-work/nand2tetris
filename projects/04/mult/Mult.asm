// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[3], respectively.)

// Put your code here.

@R2 // Reset R2 if any value is present
M = 0
@R1
D = M

// Add R0 to R2 R1 times. If R1 == 0, the loop ends
(MULT_LOOP)
    @R1
    D = M

    @END_MULT_LOOP
    D;JLE

    @R1
    M = D-1
    @R0
    D = M
    @R2
    M = M + D
    @MULT_LOOP
    0;JMP

(END_MULT_LOOP)

(END) // Forever loop
@END
0;JMP
