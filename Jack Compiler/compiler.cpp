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
#include "./headers/tokenizer.hpp"
#include "./headers/compilationEngine.hpp"
#include "./headers/symbolTable.hpp"
#include "./headers/vmWriter.hpp"


int main(int argc, char *argv[]){

    try{
        
        // Check if two arguments are provided in command prompt.

        if(argc != 2){
            throw errors::IllegalCallException("Folder name is not provided.");
        }

        std::string inputFileExt = ".jack", outputFileExt = ".xml"; 
        int inputFileExtLen = inputFileExt.length(), outputFileExtLen = outputFileExt.length();

        /*
            For each input ".jack" file, there needs to be one ".xml" tokenizer file and one ".vm" file.
        */  
        
        ioFileHandler::InputFileHandler *inputFile = new ioFileHandler::InputFileHandler();
        std::string inputFolderName = argv[1];
        std::string currFileName = "", currFileExt = "", currOutputFileName = "";

        for (const auto & entry : std::filesystem::directory_iterator(inputFolderName)){
            
            inputFileExt = ".jack";
            inputFileExtLen = inputFileExt.length();

            // Get the extension of file and check if equal to the wanted file extension.
            currFileName = entry.path();
            currFileExt = currFileName.substr(currFileName.length()-inputFileExtLen, inputFileExtLen);
            
            // if file ext is not equal to input file, move to next file.
            if(currFileExt != inputFileExt) continue;

            // Create input and output stream for each file
            inputFile->setInputStream(currFileName, inputFileExt);

            ioFileHandler::OutputFileHandler *compiledFile = new ioFileHandler::OutputFileHandler();
        
            compiledFile->createOutputStream(currFileName, inputFileExt, "_1.vm");
            std::string compiledFileName = compiledFile->getOutputFileName();
            
            // tokenizer
            tokenizerAPI::Tokenizer tokenizer(inputFile->getInputStream());
            symbolTable::SymbolTable symbolTable;
            vmWriter::VMWriter vmWriter(compiledFile->getOutputStream());
            compileAPI::Compile compiler(tokenizer, symbolTable, vmWriter);
            
            compiler.compileTokens();

            inputFile->closeInputFileStream();
            compiledFile->closeOutputFileStream();
        }
        
        
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