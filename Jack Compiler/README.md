Jack compiler consists of two parts:
1. Tokenizer
2. Symbol Table
3. VM Writer
4. Compile Engine

Tokenizer:
Takes a JACK program(similar to Java) and performs the following:
1. Opens all the files having ".jack" extension in a folder, one by one.
2. Removes all single and multiline comments
3. Removes all whitespaces
4. Parses the program into tokens. These tokens can be keywords, identifiers or symbols.
5. The tokens are sent in the form of "_tokens" and "_tokenType" variables.

Symbol Table:
1. The symbol table consists of two maps: _classST and _methodST
2. _classST handles all variables within class scope
3. _methodST handles variables within function scope. This is reset once a function begins. 

VM Writer:
1. Writes to the output file.
2. All symbols from tokenizer are converted to the appropriate VM identifiers.

Compile Engine:
Takes the _tokens and _tokenType from the tokenizer and performs the following:
1. As per the language grammar, it parses each token and tokenType and matches it.
2. Any language gramatical errors are detected and notified to the user. 
3. Stores any variables in Symbol Table.
4. Passes the input to VM Writer so ".vm" code can be written.
5. To handle the tokens, a "_tokenList" table is created. 
   To ensure efficient usage, the tokens are replaced when a routine is completed.
   Space complexity of _tokenList = O(function_having_most_variables) which is extremely efficient compared to XML file.

To build the Compile Engine from main directory:

g++-12 ./Jack\ Compiler/compiler.cpp -o ./Jack\ Compiler/compiler ./Jack\ Compiler/headers/errors.cpp ./Jack\ Compiler/headers/ioFileHandler.cpp ./Jack\ Compiler/headers/compilationEngine.cpp ./Jack\ Compiler/headers/tokenizer.cpp ./Jack\ Compiler/headers/symbolTable.cpp ./Jack\ Compiler/headers/vmWriter.cpp

To run the Compile Engine, two arguments are provided.
1. The name of cpp executable file
2. Folder containing one or more JACK files.

Example:

./Jack\ Compiler/compiler ./projects/11/Square