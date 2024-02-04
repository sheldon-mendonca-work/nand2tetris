#pragma once
#include<string>
#include<vector>

#include "errors.hpp"

#include<iostream>

namespace symbolTable
{
    /*
        Defines a symbol table of key, value pairs.
        If no key is present, a value of -2 is returned.
        Maximum number of keys is 24576.
    */
    class SymbolTable{
        public:
            int findKey(const std::string &key);
            void updateKey(const std::string &key, int val);
            void insertKeyByValue(const std::string &key, int val);
            bool validateSymbolTable(){
                for(auto x:_symbolTable) if(x.second == -1) return false;
                return true;
            }

        private:
            std::vector<std::pair<std::string, int>> defaultSymbols();
            std::vector<std::pair<std::string, int>> _symbolTable = defaultSymbols();
            int index = 16;
    };
} // namespace symbolTable
