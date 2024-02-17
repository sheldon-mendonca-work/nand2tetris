#pragma once

#include<string>
#include<fstream>

#include<iostream>

#include "./errors.hpp"
#include "./parser.hpp"


namespace codeAPI{
    class Code{
        public:
            Code(std::ofstream &outputFileStream, std::string fileNameNoExt): 
                _outputFileStream(outputFileStream), _fileNameNoExt(fileNameNoExt), _lineNumber(-1)
                    {};
            void writeInit();
            void writeArithmetic(std::string &inputLine);
            void writePush(std::string symbol, std::string &arg1, int &arg2);
            void writePop(std::string symbol, std::string &arg1, int &arg2);
            void writeFunction(std::string symbol, std::string &arg1, int &arg2);
            void writeReturn(std::string symbol);
            void writeLabel(std::string symbol, std::string &arg1);
            void writeGoto(std::string symbol, std::string &arg1);
            void writeIf(std::string symbol, std::string &arg1);
            void writeCall(std::string symbol, std::string &arg1, int &arg2);
            
            // Perform operations
            void infiniteLoop();
            void writeToFile(std::string inputLine);
            void setFileNameNoExt(std::string inputFileName);

        private:
            std::ofstream &_outputFileStream;
            std::string _fileNameNoExt = "";
            int _lineNumber = -1;
            std::string _currentFunction = "null";
            
    };
}