#pragma once

#include<string>
#include<fstream>

#include<iostream>

#include "./errors.hpp"

namespace tokenizerAPI {
    static char _symbolTable[] = {
        '{', '}', '(', ')', '[', ']', '.', ',',
        ';', '+', '-', '*', '/', '&', '|', '<',
        '>', '=', '~'
    };

    static std::string _keyWordTable[] = {
        "class", "constructor", "function", "method", "field",
        "static", "var", "int", "char", "boolean", "void",
        "true", "false", "null", "this", "let", "do",
        "if", "else", "while", "return"
    };

    static int _keyWordTableSize = 21;

    class Tokenizer{

        public:
            Tokenizer(std::ifstream &in):_in(in), _lineNumber(0),
              _pos(0), _isComment(false), _currentLine(""){}
            ~Tokenizer(){_in.close();};
            bool hasMoreTokens();
            void advance();
            std::string tokenType(){return _tokenType;}
            std::string token(){return _token;}
            
            // Modifying functions
            void removeWhiteSpace();
            bool checkSingleLineComment();
            void checkMultiLineComment();
            std::string getCurrentLine(){ return _currentLine; }
            int getLineNumber(){return _lineNumber;};
            void getKeyWordOrIdentifer();
            void getIntVal();
            void getStringVal();
            void getSymbol();
            bool checkValidSymbolChar();
            
        private:
            std::ifstream& _in;
            std::string _currentLine;
            std::string _tokenType;
            std::string _token;
            
            int _lineNumber;
            int _pos;
            bool _isComment = false;
    };
}