#pragma once
#include<string>
#include<fstream>
#include<unordered_set>

#include<iostream>

#include "./errors.hpp"

namespace compileAPI {
    static std::string types[] = {"int", "char", "boolean"};
    static std::string term[] = {"+", "-", "*", "/", "&amp;", "|", "&lt;", "&gt;", "="};
    static std::string unaryTerm[] = {"~", "-"};
    static std::string keywordConstant[] = {"true", "false", "null", "this"};

    class Compile{

        public:
            Compile(std::ifstream &in, std::ofstream &out):_in(in), _out(out), _tokenType(""), _token(""){}
            ~Compile(){_out.close();}

            void compileTokens();
            void compileClass();
            void compileClassVarDec();
            void compileSubroutine();
            void compileParameterList();
            void compileVarDec();
            void compileStatements();
            void compileDo();
            void compileLet();
            void compileWhile();
            void compileReturn();
            void compileIf();
            void compileExpression();
            void compileTerm();
            void compileExpressionList();       
            
            // Modifying functions
            void getNextLine(const std::string &errMsg, const std::string &tokenType, const std::string &token);
            void writeLine();
            void compileSubroutineCall();
            bool checkKeyboardConst();
            bool checkUnaryTerm();
            bool checkTerm();            
            
        private:
            std::ifstream& _in;
            std::ofstream& _out;
            std::string _tokenType;
            std::string _token;
            std::string _inputLine;
            int _lineNumber = 0;
            int _pos = 0;
    };
}