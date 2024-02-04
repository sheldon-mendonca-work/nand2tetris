#pragma once
#include<string>
#include<fstream>

#include<iostream>

#include "./errors.hpp"

// enum CommandType {
// 	C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_RETURN, C_CALL, ERROR
// };


namespace parserAPI {
    class Parser{

        public:
            Parser(std::ifstream &in):_in(in), _lineNumber(0), _pos(0){}
            ~Parser(){_in.close();};
            bool hasMoreCommands();
            void advance();
            std::string commandType();
            std::string arg1();
            int arg2();
            std::string getSymbol();
            
            // Modifying functions
            void removeWhiteSpace();
            bool checkComment();
            bool checkValidSymbolChar();
            int getLineNumber();
            std::string getCurrentLine();
            void findArg1();
            void findArg2();
            void createSymbol();
            
        private:
            std::ifstream& _in;
            std::string _currentLine;
            int _lineNumber;
            int _pos;
            std::string _cmdType;
            std::string _symbol = "";
            std::string _arg1 = "";
            int _arg2 = 0;
    };
}