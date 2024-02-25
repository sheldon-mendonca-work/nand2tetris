#pragma once
#include <string>

namespace errors{
    /*
        Handles the errors related to opening, closing, reading and writing of files.
    */
    class FileHandlingException{	
        private:
            std::string _errMsg;
        public:
            FileHandlingException(std::string s): _errMsg(s) {}
            std::string what();
    };

    /*
        If a function is wrongly called, this error is thrown.
    */
    class IllegalCallException{	
        private:
            std::string _errMsg;
        public:
            IllegalCallException(std::string s): _errMsg(s) {}
            std::string what();
    };

    /*
        If a syntax error is present, this error is thrown. line number, character position of the processed file and error message are provided as inputs.
    */
    class SyntaxErrorException{
        private:
            int _lineNum;
            int _pos;
            std::string _errMsg;
        public:
            SyntaxErrorException(int lineNum, int pos, std::string errMsg)
                : _lineNum(lineNum), _pos(pos), _errMsg(errMsg) {}
            std::string what();
    };

    /*
        If a symbol is called that is not present in symbol table, this error is thrown.
    */
    class UndefinedSymbolException{	
        private:
            std::string _errMsg;
        public:
            UndefinedSymbolException(std::string s)
                : _errMsg(s) {}
            std::string what();
    };

}
