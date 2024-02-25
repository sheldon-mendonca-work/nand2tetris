#pragma once

#include<iostream>
#include<string>
#include<unordered_map>

#include "errors.hpp"

namespace symbolTable{
    class Symbol;

    class SymbolTable{
        public:
            SymbolTable(){};
            void startSubroutine();
            void define(const std::string &name, const std::string &type, const std::string &kind);
            int varCount(const std::string &kind);
            std::string kindOf(const std::string &name);
            std::string typeOf(const std::string &name);
            int indexOf(const std::string &name);

        private:
            std::unordered_map<std::string, Symbol *> _classST, _methodST;
            int staticVal = -1, fieldVal = -1, argVal = -1, varVal = -1;
    };

    class Symbol{
        public:
            Symbol(const std::string &name, const std::string &type, const std::string &kind, int index): 
                name(name), type(type), kind(kind), index(index){}; 
            Symbol() = default;

            std::string name, type, kind;
            int index = 0;
    };
}