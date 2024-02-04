To build the assembler from main directory:

g++-12 ./Assembler/assembler.cpp -o ./Assembler/assembler ./Assembler/headers/parser.cpp ./Assembler/headers/errors.cpp ./Assembler/headers/code.cpp ./Assembler/headers/symbolTable.cpp

To run the assembler, two arguments are provided. Example:

./Assembler/assembler ./projects/06/max/Max.asm