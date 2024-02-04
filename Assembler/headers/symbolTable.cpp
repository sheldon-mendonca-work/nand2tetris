#include "./symbolTable.hpp"

std::vector<std::pair<std::string, int>>  symbolTable::SymbolTable::defaultSymbols(){
    std::vector<std::pair<std::string, int>> vect;
    vect.push_back({"SP", 0});
    vect.push_back({"LCL", 1});
    vect.push_back({"ARG", 2});
    vect.push_back({"THIS", 3});
    vect.push_back({"THAT", 4});
    vect.push_back({"R0", 0});
    vect.push_back({"R1", 1});
    vect.push_back({"R2", 2});
    vect.push_back({"R3", 3});
    vect.push_back({"R4", 4});
    vect.push_back({"R5", 5});
    vect.push_back({"R6", 6});
    vect.push_back({"R7", 7});
    vect.push_back({"R8", 8});
    vect.push_back({"R9", 9});
    vect.push_back({"R10", 10});
    vect.push_back({"R11", 11});
    vect.push_back({"R12", 12});
    vect.push_back({"R13", 13});
    vect.push_back({"R14", 14});
    vect.push_back({"R15", 15});
    vect.push_back({"SCREEN", 16384});
    vect.push_back({"KBD", 24576});
    
    return vect;
}

/*
    If key is present in symbol table, the value is returned.
    If not present, -2 is returned. 
*/
int symbolTable::SymbolTable::findKey(const std::string &key){
    for(auto x: _symbolTable){
        if(x.first == key) return x.second;
    }
    return -2;
}

/*
    Update the value of symbol by providing the key and value.
    If key is not present, UndefinedSymbolException is thrown.
*/
void symbolTable::SymbolTable::updateKey(const std::string &key, int val){
    
    if(findKey(key) == -2){
        throw errors::UndefinedSymbolException("Symbol '" + key + "' is not present.");
    }

    for(auto &x : _symbolTable){
        if(x.first == key){
           if(val == -1){
                x.second = index++;
            }else{
                x.second = val;
            }
            return;
        }
    }
}

/*
    Insert a key in the table. If key is already present, an error is thrown.
    If key has no initial value, it is recommended to set it to -1.
*/
void symbolTable::SymbolTable::insertKeyByValue(const std::string &key, int val){
    if(findKey(key) != -2){
        throw errors::IllegalCallException("Cannot add existing symbol: "+key);
    }

    _symbolTable.push_back({key, val});
}