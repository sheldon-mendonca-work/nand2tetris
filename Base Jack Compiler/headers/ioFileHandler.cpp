#include "ioFileHandler.hpp"

/*
    Opens an input file for reading.
    Extension type is checked before reading.
*/
std::ifstream& ioFileHandler::InputFileHandler::setInputStream(std::string &inputFileName, std::string validFileExt){
    std::string inputFileExt = inputFileName.substr(inputFileName.length()-validFileExt.length(), validFileExt.length());
    if(inputFileExt != validFileExt){
        throw errors::FileHandlingException("Input file extension is not '"+ validFileExt +"'.");
    }
    _inputFileName = inputFileName;
    _inputFileStream.open(_inputFileName);

    if(!_inputFileStream.is_open()){
        throw errors::FileHandlingException("Input file could not be opened.");
    }
    
    return _inputFileStream;
}

/*
    Takes in an input file name and output file extension.
    Extensions must begin with a dot(.).
    Output file name is same as input name.
*/
void ioFileHandler::OutputFileHandler::createOutputStream(std::string inputFileName, std::string validFileExt, std::string outputFileExt){
    
    std::string outputFileName = inputFileName.substr(0, inputFileName.length()-validFileExt.length()) + outputFileExt;

    // create output file
    _outputFileName = outputFileName;

  // test output file opening
    _outputFileStream.open(_outputFileName);

    if(!_outputFileStream.is_open()){
        throw errors::FileHandlingException("Output file could not be created.");
    }
}

void ioFileHandler::InputFileHandler::closeInputFileStream(){
    _inputFileStream.close();
}

void ioFileHandler::OutputFileHandler::closeOutputFileStream(){
    std::cout<<_outputFileName<<std::endl;
    _outputFileStream.close();
}