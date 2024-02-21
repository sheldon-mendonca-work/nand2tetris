Jack compiler consists of two parts:
1. Tokenizer
2. Compile Engine

Tokenizer:
Takes a JACK program(similar to Java) and performs the following:
1. Opens all the files having ".jack" extension in a folder, one by one.
2. Removes all single and multiline comments
3. Removes all whitespaces
4. Parses the program into tokens. These tokens can be keywords, identifiers or symbols.
5. The output of a tokenizer is an XML file of the format ".txml".

Compile Engine:
Takes the ".txml" file from the tokenizer and performs the following:
1. As per the language grammar, it parses each token and tokenType and matches it.
2. Any language gramatical errors are detected and notified to the user. 
3. The output of a compile engine is a file with extension ".xml".

To build the Compile Engine from main directory:

g++-12 ./Jack\ Compiler/compiler.cpp -o ./Jack\ Compiler/compiler ./Jack\ Compiler/headers/errors.cpp ./Jack\ Compiler/headers/ioFileHandler.cpp ./Jack\ Compiler/headers/compilationEngine.cpp ./Jack\ Compiler/headers/tokenizer.cpp

To run the Compile Engine, two arguments are provided.
1. The name of cpp executable file
2. Folder containing one or more JACK files.

Example:

./Jack\ Compiler/compiler ./projects/10/Square