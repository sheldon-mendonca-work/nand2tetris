#include "symbolTable.hpp"

void symbolTable::SymbolTable::startSubroutine(){
    _methodST.clear();
    argVal = -1; varVal = -1;
}

void symbolTable::SymbolTable::define(const std::string &name, const std::string &type, const std::string &kind){
    if(kind == "static" || kind == "field"){
        if(_classST.find(name) != _classST.end()){
            throw errors::IllegalCallException("Value already exists: " + name);
        }
        if(kind == "static"){
            _classST[name] = new symbolTable::Symbol(name, type, kind, ++staticVal);
        }else{
            _classST[name] = new symbolTable::Symbol(name, type, kind, ++fieldVal);
        }
    }else if(kind == "argument" || kind == "var"){
        if(_methodST.find(name) != _methodST.end()){
            throw errors::IllegalCallException("Value already exists: " + name);
        }

        if(kind == "argument"){
            _methodST[name] = new symbolTable::Symbol(name, type, kind, ++argVal);
        }else{
            _methodST[name] = new symbolTable::Symbol(name, type, kind, ++varVal);
        }
    }else{
        throw errors::IllegalCallException("Scope does not match any: " + name + ", kind: " + kind);
    }
}

std::string symbolTable::SymbolTable::kindOf(const std::string &name){
    if(_classST.find(name) != _classST.end()) return _classST[name]->kind;
    if(_methodST.find(name) != _methodST.end()) return _methodST[name]->kind;
    return "NONE";
}

std::string symbolTable::SymbolTable::typeOf(const std::string &name){
    if(_classST.find(name) != _classST.end()) return _classST[name]->type;
    if(_methodST.find(name) != _methodST.end()) return _methodST[name]->type;
    return "NONE";
}

int symbolTable::SymbolTable::indexOf(const std::string &name){
    if(_classST.find(name) != _classST.end()) return _classST[name]->index;
    if(_methodST.find(name) != _methodST.end()) return _methodST[name]->index;
    return -1;
}

int symbolTable::SymbolTable::varCount(const std::string &kind){
    if(kind == "argument") return argVal+1;
    if(kind == "var") return varVal+1;
    if(kind == "static") return staticVal+1;
    if(kind == "field") return fieldVal+1;
    else return -1;
}