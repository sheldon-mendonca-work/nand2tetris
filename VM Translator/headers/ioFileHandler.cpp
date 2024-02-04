#include "ioFileHandler.hpp"

void ioFileHandler::IOFileHandler::createOutputStream(std::string inputFileName, std::string outputFileExt){
    
    std::string inputFileExt = inputFileName.substr(inputFileName.length()-3, 3);
    
    _inputFileName = inputFileName;
    
    inputFileName = inputFileName.substr(0, inputFileName.length()-3);
    _fileNameNoExt = "";
    
    int i = inputFileName.length()-1;
    for(; i >= 0 && inputFileName[i] != '/'; i--){
        
    }
    i--;
    for(; i >= 0 && inputFileName[i] != '/'; i--){
        _fileNameNoExt = inputFileName[i]+_fileNameNoExt;
    }
    
    while(i >= 0){
        _inputFolderName = inputFileName[i--]+_inputFolderName;
    }
    _inputFolderName = _inputFolderName + "/" + _fileNameNoExt;
    _outputFileName = _inputFolderName + "/" + _fileNameNoExt + outputFileExt;

    if(inputFileExt != ".vm"){
        throw errors::FileHandlingException("Input file extension is not '.vm'.");
    }

    _inputFileStream.open(_inputFileName);

    if(!_inputFileStream.is_open()){
        throw errors::FileHandlingException("Input file could not be opened.");
    }

    _inputFileStream.close();
    _outputFileStream.open(_outputFileName);

    if(!_outputFileStream.is_open()){
        throw errors::FileHandlingException("Output file could not be created.");
    }
}

std::ifstream& ioFileHandler::IOFileHandler::setInputStream(std::string &inputFileName){
    std::string inputFileExt = inputFileName.substr(inputFileName.length()-3, 3);
    if(inputFileExt != ".vm"){
        throw errors::FileHandlingException("Input file extension is not '.vm'.");
    }
    _inputFileName = inputFileName;
    _inputFileStream.open(_inputFileName);

    if(!_inputFileStream.is_open()){
        throw errors::FileHandlingException("Input file could not be opened.");
    }
    
    return _inputFileStream;
}

void ioFileHandler::IOFileHandler::closeInputFileStream(){
    _inputFileStream.close();
}

void ioFileHandler::IOFileHandler::closeOutputFileStream(){
    std::cout<<_outputFileName<<std::endl;
    _outputFileStream.close();
}