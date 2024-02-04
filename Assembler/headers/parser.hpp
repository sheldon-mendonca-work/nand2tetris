#pragma once
#include<string>
#include<fstream>

#include<iostream>

#include"./parser.hpp"
#include "./errors.hpp"
#include "./code.hpp"

enum CommandType {
	A_COMMAND, C_COMMAND, L_COMMAND, ERROR
};


namespace parserAPI {
    class Parser{

        public:
            Parser(std::ifstream &in):_in(in), _lineNumber(0), _pos(0), _cmdType(ERROR){}
            ~Parser(){_in.close();};
            bool hasMoreCommands();
            void advance();
            CommandType commandType();
            std::string symbol();
            std::string dest();
            std::string comp();
            std::string jump();
            
            // Modifying functions
            void removeWhiteSpace();
            bool checkComment();
            bool checkValidSymbolChar();
            void ACommandHandler();
            void LCommandHandler();
            void CCommandHandler();
            int getLineNumber();
            std::string getCurrentLine();
            
        private:
            std::ifstream& _in;
            std::string _currentLine;
            int _lineNumber;
            int _pos;
            CommandType _cmdType;
            std::string _symbol;
            std::string _dest;
            std::string _comp;
            std::string _jump;
    };
}