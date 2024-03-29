#pragma once
#include<string>
#include<fstream>
#include<unordered_set>
#include<vector>

#include<iostream>

#include "./errors.hpp"
#include "./tokenizer.hpp"
#include "./vmWriter.hpp"
#include "./symbolTable.hpp"

namespace compileAPI {
    static std::string types[] = {"int", "char", "boolean"};
    static std::string term[] = {"+", "-", "*", "/", "&amp;", "|", "&lt;", "&gt;", "="};
    static std::string unaryTerm[] = {"~", "-"};
    static std::string keywordConstant[] = {"true", "false", "null", "this"};

    class Compile{

        public:
            Compile(tokenizerAPI::Tokenizer &tokenizer, symbolTable::SymbolTable &sym, vmWriter::VMWriter &vm):
             _tokenizer(tokenizer), _sym(sym), _writer(vm), _tokenType(""),
             _token(""){}
            ~Compile(){}

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
            bool checkKeyboardConst(const std::string &token);
            bool checkUnaryTerm(const std::string &token);
            bool checkTerm(const std::string &token);
            void addToken(const std::string &t);      
            
        private:
            tokenizerAPI::Tokenizer _tokenizer;
            symbolTable::SymbolTable _sym;
            vmWriter::VMWriter _writer;
            std::string _tokenType;
            std::string _token;
            std::string _kind;
            std::string _type;
            std::string _className;
            int _argCount = 0;
            std::vector<std::string> _tokenList;
            int _curr = 0;
            int _labelCount = 0;
    };
}