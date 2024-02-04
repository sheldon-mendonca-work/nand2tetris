#include "ioFileHandler.hpp"

/*
    Takes in an input file name, valid file extension and output file extension.
    Extensions must begin with a dot(.).
    Output file name is same as Folder name.
*/
void ioFileHandler::IOFileHandler::createOutputStream(std::string inputFileName, std::string validFileExt, std::string outputFileExt){
    
    // validate input file extension
    std::string inputFileExt = inputFileName.substr(inputFileName.length()-validFileExt.length(), validFileExt.length());
    
    if(inputFileExt != validFileExt){
        throw errors::FileHandlingException("Input file extension is not '"+validFileExt+"'.");
    }
    
    _inputFileName = inputFileName;
    
    // to get file name of output
    _fileNameNoExt = "";
    
    // first pass to remove input file name
    int i = inputFileName.length()-1;
    for(; i >= 0 && inputFileName[i] != '/'; i--){
        
    }


    // second pass to get folder name. output file name is same as folder name
    i--;
    for(; i >= 0 && inputFileName[i] != '/'; i--){
        _fileNameNoExt = inputFileName[i]+_fileNameNoExt;
    }
    
    // set input folder path.
    while(i >= 0){
        _inputFolderName = inputFileName[i--]+_inputFolderName;
    }
    
    _inputFolderName = _inputFolderName + "/" + _fileNameNoExt;

    // create output file
    _outputFileName = _inputFolderName + "/" + _fileNameNoExt + outputFileExt;

    // test input file opening
    _inputFileStream.open(_inputFileName);

    if(!_inputFileStream.is_open()){
        throw errors::FileHandlingException("Input file could not be opened.");
    }

    // Since folder can have multiple files of same extension, each of them can be parsed at once.
    // so we close the current file.
    _inputFileStream.close();
    
    // test output file opening
    _outputFileStream.open(_outputFileName);

    if(!_outputFileStream.is_open()){
        throw errors::FileHandlingException("Output file could not be created.");
    }
}

/*
    Opens an input file for reading.
    Extension type is checked before reading.
*/
std::ifstream& ioFileHandler::IOFileHandler::setInputStream(std::string &inputFileName, std::string validFileExt){
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

void ioFileHandler::IOFileHandler::closeInputFileStream(){
    _inputFileStream.close();
}

void ioFileHandler::IOFileHandler::closeOutputFileStream(){
    std::cout<<_outputFileName<<std::endl;
    _outputFileStream.close();
}