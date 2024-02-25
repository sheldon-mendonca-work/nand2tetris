#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<unordered_map>

namespace vmWriter{
    class VMWriter{
        public:
            VMWriter(std::ofstream &out):
                _out(out){ initializeMp(); }
            ~VMWriter(){_out.close();}

            void writePush(const std::string &arg1, const std::string &arg2);
            void writePop(const std::string &arg1, const std::string &arg2);
            void writeArithmetic(const std::string &arg1);
            void writeLabel(const std::string &arg1);
            void writeGoto(const std::string &arg1);
            void writeIf(const std::string &arg1);
            void writeCall(const std::string &arg1, const std::string &arg2);
            void writeFunction(const std::string &arg1, const std::string &arg2);
            void writeReturn();
            void close(){
                // closing handled by main program
            };

            void initializeMp();
            void writeCmd(const std::string &s){
                // _out<<s;
            }
            
        private:
            std::ofstream& _out;
            std::unordered_map<std::string, std::string> mp;
    };
}