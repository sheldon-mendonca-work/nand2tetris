#include "vmWriter.hpp"

void vmWriter::VMWriter:: initializeMp(){
    mp["arg"] = "argument";
    mp["var"] = "local";
    mp["field"] = "this";

    mp["+"] = "add";
    mp["-"] = "sub";
    mp["neg"] = "neg";
    mp["~"] = "not";
    mp["="] = "eq";
    mp["&gt;"] = "gt";
    mp["&lt;"] = "lt";
    mp["&amp;"] = "and";
    mp["|"] = "or";
    mp["!"] = "";
    mp["*"] = "call Math.multiply 2";
    mp["/"] = "call Math.divide 2";
}

void vmWriter::VMWriter::writePush(const std::string &arg1, const std::string &arg2){
    std::string tk = arg1;
    if(mp.find(arg1) != mp.end()) tk = mp[arg1];
    _out<<"push "<<tk<<" "<<arg2<<"\n";
}

void vmWriter::VMWriter::writePop(const std::string &arg1, const std::string &arg2){
    std::string tk = arg1;
    if(mp.find(arg1) != mp.end()) tk = mp[arg1];
    _out<<"pop "<<tk<<" "<<arg2<<"\n";
}

void vmWriter::VMWriter::writeArithmetic(const std::string &arg1){
    _out<<mp[arg1]<<"\n";
}

void vmWriter::VMWriter::writeLabel(const std::string &arg1){
    _out<<"label "<<arg1<<"\n";
}

void vmWriter::VMWriter::writeGoto(const std::string &arg1){
    _out<<"goto "<<arg1<<"\n";
}

void vmWriter::VMWriter::writeIf(const std::string &arg1){
    _out<<"if-goto "<<arg1<<"\n";
}

void vmWriter::VMWriter::writeCall(const std::string &arg1, const std::string &arg2){
    _out<<"call "<<arg1<<" "<<arg2<<"\n";
}

void vmWriter::VMWriter::writeFunction(const std::string &arg1, const std::string &arg2){
    _out<<"function "<<arg1<<" "<<arg2<<"\n";
}

void vmWriter::VMWriter::writeReturn(){
    _out<<"return"<<"\n";
}
