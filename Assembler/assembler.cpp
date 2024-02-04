#include<iostream>
#include<string>
#include<fstream>
#include<unordered_map>
#include<cstdio>

#include "./headers/parser.hpp"
#include "./headers/errors.hpp"
#include "./headers/code.hpp"
#include "./headers/symbolTable.hpp"

/* 
    Takes in two arguments: Output file stream and Output file name(having same value as input file name).
    If successful, a new output file(.hack) is created and a value of "0" is returned;
    If unsuccessful, a non-zero integer value is returned.
*/
int generateOutputFiles(std::string &outputFileName, std::ofstream &outputFileStream, std::string fileExt){
    // Generate hack file name
    for(int i = outputFileName.length()-1; i >= 0; i--){
        if(outputFileName[i] == '.'){
            outputFileName = outputFileName.substr(0, i);
            break;
        }
    }
    outputFileName += fileExt;

    // Create output file
    outputFileStream.open(outputFileName);

    //If output file could not be opened, return 1;
    if(!outputFileStream.is_open()){
        throw errors::FileHandlingException("Output file could not be generated.");
    }
    return 0;
}

/*
    Converts a number written in base 10 string to a base 2 numerical string having 16 digits.
    If a non-zero character is found, error is thrown.
*/
void convertTextToBitNumber(std::string &inputString, std::string &outputString){
    int curr = 0, i = 0;
    while(inputString[i] != '\0'){
        if(inputString[i] >= '0' && inputString[i] <= '9'){
            curr = curr*10 + (inputString[i]-'0');
            i++;
        }else if (inputString[i] == ' '){
            i++;
        }else{
            throw errors::IllegalCallException("Invalid variable/number '"+inputString+"'.");
        }        
    }

    i = 0;
    while(i++ < 16){
        outputString = std::string(1, (curr&1)+'0') + outputString;
        curr = curr>>1;
    }
}

/*
    Generates C Command based on destination, computation and jump parameters.
*/
std::string generateCCommand(parserAPI::Parser &parser, codeAPI::DestCode &destCode, codeAPI::CompCode &compCode, codeAPI::JumpCode &jumpCode){
    std::string outputString = "111";
    int compType = 0;
    std::string comp = parser.comp(), dest = parser.dest(), jump = parser.jump(); 
    for(char c: comp){
        if(c == 'M'){
            compType = 1;
            break;
        }
    }
    
    outputString += (compType ? "1":"0");

    if(compCode.findCompMnemonic(comp)){
        outputString += compCode.getCompMnemonic(comp);
    }else{
        throw errors::IllegalCallException("Computation is not defined: " + parser.getCurrentLine());
    }

    if(destCode.findDestMnemonic(dest)){
        outputString += destCode.getDestMnemonic(dest);
    }else{
        throw errors::IllegalCallException("Destination is not defined: " + parser.getCurrentLine());
    }

    if(jumpCode.findJumpMnemonic(jump)){
        outputString += jumpCode.getJumpMnemonic(jump);
    }else{
        throw errors::IllegalCallException("Jump is not defined: " + parser.getCurrentLine());
    }

    return outputString;
}

/*
    The command line arguments takes in an additional parameter: Location of the file.
    if no argument is provided, error is thrown.
*/
int main(int argc, char *argv[]){

    try{
        std::string inputFileName = "", outputFileName = "";
        if(argc != 2){
            std::cerr<<"Only one argument is entered. Enter the file name as second argument."<<std::endl;
            return 1;
        }else{
            inputFileName = outputFileName = argv[1];
        }

        std::ifstream inputFileStream;
        std::ofstream outputFileStream;
        int i, currentLine = 0;
        
        // Check if file type is asm
        
        if(inputFileName.find(".asm") == std::string::npos){
            std::cerr<<"Input file type is not '.asm'."<<std::endl;
            return 2;
        }
        
        inputFileStream.open(inputFileName);

        //If input file could not be opened, return 1;
        if(!inputFileStream.is_open()){
            std::cout<<"Input file could not be opened."<<std::endl;
            return 1;
        }

        parserAPI::Parser parser(inputFileStream);
        codeAPI::CompCode compCode;
        codeAPI::DestCode destCode;
        codeAPI::JumpCode jumpCode;
        symbolTable::SymbolTable symbolTable;

        std::string inputLine, outputLine;
        int count = 0;

        int opGeneratedFlag = generateOutputFiles(outputFileName, outputFileStream, ".mhack");
        if(opGeneratedFlag){
            return opGeneratedFlag;
        }


        /*
            First Pass.
            A temporary file of type .mhack is created. The following actions are performed:
            - A_COMMAND: numerical values are converted to bit strings. For symbols, the symbol name is stored in output.
            - L_COMMAND: The Command is added to the symbol table with line number. If duplicates are found, error is thrown.
            - C_COMMAND: The symbols are processed, converted and stored in output.

            For symbol table, '-2' is used to indicate that symbol is not present in table.
            '-1' is used to indicate that symbol is present in table but value is not assigned. 
        */
        try
        {
            while(parser.hasMoreCommands()){
                parser.advance();
                outputLine = "";
                std::string x = parser.symbol();

                // Handles A_COMMAND
                if(parser.commandType() == A_COMMAND){
                    // Symbol is a number, hence it is converted to bit.
                    if(x[0] >= '0' && x[0] <= '9'){
                        convertTextToBitNumber(x,outputLine);
                        outputFileStream<<outputLine<<"\n";
                    }else{
                        // Symbol is a text, so it is stored in table with value -1.
                        if(symbolTable.findKey(x) == -2){
                            symbolTable.insertKeyByValue(x, -1);
                        }
                        outputFileStream<<x<<"\n";
                    }

                }else if(parser.commandType() == L_COMMAND){
                    int a = symbolTable.findKey(x);
                    
                    if(a == -2){
                        symbolTable.insertKeyByValue(x, parser.getLineNumber());
                    }else if(a == -1){
                        symbolTable.updateKey(x, parser.getLineNumber());
                    }else{
                        throw errors::SyntaxErrorException(parser.getLineNumber(), 0, "Cannot have two labels of same name: "+parser.getCurrentLine());
                    }
                }else if(parser.commandType() == C_COMMAND){
                    outputLine = generateCCommand(parser, destCode, compCode, jumpCode);
                    outputFileStream<<outputLine<<"\n";
                }else{
                    throw errors::IllegalCallException("Something went wrong at "+ std::to_string(parser.getLineNumber()) + ".");
                }
            }
        
            inputFileStream.close();
            outputFileStream.close();            
            
            inputFileName = outputFileName;

            inputFileStream.open(inputFileName);

            //If input file could not be opened, return 1;
            if(!inputFileStream.is_open()){
                throw errors::FileHandlingException("Could not open .mhack file.");
            }

            opGeneratedFlag = generateOutputFiles(outputFileName, outputFileStream, ".hack");
            if(opGeneratedFlag){
                throw errors::FileHandlingException("Could not create .hack file.");
            }

            /*
                Second Pass. 
                We use the output file as base file.
            */

            while(getline(inputFileStream, inputLine)){
                outputLine = "";
                if(!inputLine.length()) continue;
                if(inputLine[0] >= '0' && inputLine[0] <= '9'){
                    outputFileStream<<inputLine<<std::endl;
                }else{
                    int x = symbolTable.findKey(inputLine);
                    if(x == -1){
                        symbolTable.updateKey(inputLine, -1);
                    }

                    x = symbolTable.findKey(inputLine);
                    std::string y = std::to_string(x);
                    convertTextToBitNumber(y, outputLine);
                    outputFileStream<<outputLine<<std::endl;
                }
            }
            inputFileStream.close();
            outputFileStream.close(); 

            std::remove(inputFileName.c_str());
       }catch(errors::FileHandlingException &e){
            std::cout<<e.what()<< '\n';
            return 1;
        }catch(errors::IllegalCallException &e){
            std::cout<<e.what()<< '\n';
            return 1;
        }catch(errors::SyntaxErrorException &e){
            std::cout<<e.what()<< '\n';
            return 1;
        }catch(errors::UndefinedSymbolException &e){
            std::cout<<e.what()<< '\n';
            return 1;
        }catch(...){
            std::cout<<"Some error occured."<<parser.getLineNumber()<<inputFileName<< '\n';
            return 2;
        }
        return 0;

    }catch(const std::exception& e){
        std::cerr << e.what();
    } 
}