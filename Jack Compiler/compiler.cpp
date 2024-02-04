/**
 * Jack Compiler
 * Written in C++-11
*/
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
        // second argument should be a file name so that it can be validated.

        if(argc != 2){
            throw errors::IllegalCallException("File name is not provided.");
        }
        
        // Create XML file for tokenizer
        ioFileHandler::IOFileHandler *ioFile = new ioFileHandler::IOFileHandler();

        ioFile->createOutputStream(argv[1], ".jack", ".xml");
        std::string fileNameNoExt = ioFile->fileNameNoExt(), inputFolderName = ioFile->inputFolderName();
        codeAPI::Code codeOutput(ioFile->getOutputStream(), fileNameNoExt);
        std::string cmdType, sym, arg1, inputFileExt, inputFileName;
        int arg2 = 0;

        
        for (const auto & entry : std::filesystem::directory_iterator(inputFolderName)){
            
            // Check if input file extension is ".jack"
            inputFileExt = entry.path();
            inputFileExt = inputFileExt.substr(inputFileExt.length()-5, 5);
            
            if(inputFileExt != ".jack") continue;
            
            inputFileName = entry.path();
            parserAPI::Parser parser(ioFile->setInputStream(inputFileName, ".jack"));
    
            codeOutput.setFileNameNoExt(inputFileName);
            codeOutput.writeToFile("// FILE: "+inputFileName+"\n\n");
            
            // while (parser.hasMoreCommands()){
            //     parser.advance();

                
            // }

            ioFile->closeInputFileStream();
        }
        
        
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