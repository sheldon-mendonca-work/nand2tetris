#pragma once

#include<fstream>
#include<string>
#include<iostream>

#include "./errors.hpp"

namespace ioFileHandler{
    class IOFileHandler{
        public:
            IOFileHandler():_inputFileStream(nullptr), _outputFileStream(nullptr){};
            void createOutputStream(std::string inputFileName, std::string outputFileExt);
            void closeInputFileStream();
            void closeOutputFileStream();
            std::ifstream &getInputStream(){return _inputFileStream;};
            std::ofstream &getOutputStream(){return _outputFileStream;};
            std::string &fileNameNoExt(){return _fileNameNoExt;};
            std::string &inputFolderName(){return _inputFolderName;};
            std::ifstream &setInputStream(std::string &inputFileName);
            
        private:
            std::ifstream _inputFileStream;
            std::ofstream _outputFileStream;
            std::string _inputFileName="";
            std::string _fileNameNoExt="";
            std::string _inputFolderName="";
            std::string _outputFileName="";
    };
}// namespace ioFileHandler