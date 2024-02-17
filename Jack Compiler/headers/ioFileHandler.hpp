#pragma once

#include<fstream>
#include<string>
#include<iostream>

#include "./errors.hpp"

namespace ioFileHandler{
    class InputFileHandler{
        public:
            InputFileHandler():_inputFileStream(nullptr){};
            void closeInputFileStream();
            std::ifstream &getInputStream(){return _inputFileStream;};
            std::ifstream &setInputStream(std::string &inputFileName, std::string validFileExt);
            
        private:
            std::ifstream _inputFileStream;
            std::string _inputFileName="";
    };

    class OutputFileHandler{
        public:
            OutputFileHandler(): _outputFileStream(nullptr){};
            void createOutputStream(std::string inputFileName, std::string validFileExt, std::string outputFileExt);
            void closeOutputFileStream();
            std::ofstream &getOutputStream(){return _outputFileStream;};
            std::string &getOutputFileName(){return _outputFileName;};
            
        private:
            std::ofstream _outputFileStream;
            std::string _outputFileName="";
    };
}// namespace ioFileHandler