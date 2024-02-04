#include<iostream>
#include<string>
#include<fstream>
#include <filesystem>

#include "./headers/errors.hpp"
#include "./headers/ioFileHandler.hpp"
#include "./headers/parser.hpp"
#include "./headers/code.hpp"


int main(int argc, char *argv[]){

    try{
        
        // Check if two arguments are provided in command prompt.

        if(argc != 2){
            throw errors::IllegalCallException("File name is not provided.");
        }
        
        ioFileHandler::IOFileHandler *ioFile = new ioFileHandler::IOFileHandler();

        ioFile->createOutputStream(argv[1], ".asm");
        std::string fileNameNoExt = ioFile->fileNameNoExt(), inputFolderName = ioFile->inputFolderName();
        codeAPI::Code codeOutput(ioFile->getOutputStream(), fileNameNoExt);
        std::string cmdType, sym, arg1, inputFileExt, inputFileName;
        int arg2 = 0;

        codeOutput.writeInit();

        for (const auto & entry : std::filesystem::directory_iterator(inputFolderName)){
            inputFileExt = entry.path();
            inputFileExt = inputFileExt.substr(inputFileExt.length()-3, 3);
            
            if(inputFileExt != ".vm") continue;
            
            inputFileName = entry.path();
            parserAPI::Parser parser(ioFile->setInputStream(inputFileName));
    
            codeOutput.setFileNameNoExt(inputFileName);
            codeOutput.writeToFile("// FILE: "+inputFileName+"\n\n");
            
            while (parser.hasMoreCommands()){
                parser.advance();

                cmdType = parser.commandType();
                sym = parser.getSymbol();
                arg1 = parser.arg1();
                arg2 = parser.arg2();
                
                if(cmdType == "C_ARITHMETIC"){
                    codeOutput.writeArithmetic(sym);
                }else if(cmdType == "C_PUSH"){
                    codeOutput.writePush(sym, arg1, arg2);
                }else if(cmdType == "C_POP"){
                    codeOutput.writePop(sym, arg1, arg2);
                }else if(cmdType == "C_IF"){
                    codeOutput.writeIf(sym, arg1);
                }else if(cmdType == "C_GOTO"){
                    codeOutput.writeGoto(sym, arg1);
                }else if(cmdType == "C_LABEL"){
                    codeOutput.writeLabel(sym, arg1);
                }else if(cmdType == "C_FUNCTION"){
                    codeOutput.writeFunction(sym, arg1, arg2);
                }else if(cmdType == "C_RETURN"){
                    codeOutput.writeReturn(sym);
                }else if(cmdType == "C_CALL"){
                    codeOutput.writeCall(sym, arg1, arg2);
                }else{
                    throw errors::IllegalCallException("Error at "+parser.getCurrentLine());
                }
            }

            ioFile->closeInputFileStream();
        }
        
        // codeOutput.infiniteLoop();
        ioFile->closeOutputFileStream();
        return 0;

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
        std::cout<<"Some error occured."<< '\n';
        return 2;
    }
    
}