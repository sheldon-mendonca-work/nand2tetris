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
            Tokenizer(std::ifstream &in, std::ofstream &out):_in(in), _out(out),
                 _lineNumber(0), _pos(0), _isComment(false), _currentLine(""){}
            ~Tokenizer(){_in.close();};
            bool hasMoreTokens();
            void advance();
            std::string tokenType(){return _tokenType;}
            std::string keyWord(){return _keyWord;}
            char symbol(){return _symbol;}
            std::string identifier(){return _identifier;}
            int intVal(){return _intVal;}
            std::string stringVal(){return _stringVal;}
            
            // Modifying functions
            void removeWhiteSpace();
            bool checkSingleLineComment();
            void checkMultiLineComment();
            std::string getCurrentLine(){ return _currentLine; }
            int getLineNumber(){return _lineNumber;};
            void writeInit();
            void writeEnd();
            void getKeyWordOrIdentifer();
            void getIntVal();
            void getStringVal();
            void getSymbol();
            bool checkValidSymbolChar();
            
        private:
            std::ifstream& _in;
            std::ofstream& _out;
            std::string _currentLine;
            std::string _tokenType;
            std::string _keyWord;
            char _symbol;
            std::string _identifier;
            int _intVal;
            std::string _stringVal;
            int _lineNumber;
            int _pos;
            bool _isComment = false;
    };
}