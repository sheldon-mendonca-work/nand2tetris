// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen
// by writing 'black' in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen by writing
// 'white' in every pixel;
// the screen should remain fully clear as long as no key is pressed.

//// Replace this comment with your code.

(START)
@SCREEN
D = A
@R1
M = D

// Run an infinite loop that listens to the keyboard input.
(KBD_INPUT_LOOP_START)
    @KBD
    D = M

    // When a key is pressed (any key), the program blackens the screen
    @BLACKEN_START
    D;JGT
    @WHITEN_START
    D;JEQ

    @KBD_INPUT_LOOP_START
    0;JMP
(KBD_INPUT_LOOP_END)

(BLACKEN_START)
    // set memory at address R2 =  -1
    @R2
    M = -1

    @CHANGE_SCREEN_ADDRESS
    0;JMP
(BLACKEN_END)


(WHITEN_START)
    // set memory at address R2 =  0
    @R2
    M = 0
    
    @CHANGE_SCREEN_ADDRESS
    0;JMP
(WHITEN_END)

(CHANGE_SCREEN_ADDRESS)
// Get value to be updated in screen
@R2
D = M

// Update current cell value in screen
@R1
A = M
M = D

//Get next value of pixel
@R1
D = M+1

//To check if valid
@KBD
D = A - D

// get next address
@R1
M = M + 1
A = M

//If valid, update screen with value from R2
@CHANGE_SCREEN_ADDRESS
D;JGT

//else start from beginning
@START
0;JMP