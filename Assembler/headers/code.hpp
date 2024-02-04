#pragma once

#include<string>
#include<iostream>
#include<unordered_map>

namespace codeAPI
{
    class DestCode{
        public:
        
            // Initialize Mnemonics without creating an object that is accessible throughout the program.
            std::unordered_map<std::string, std::string> initDestMnemonics();
            
            bool findDestMnemonic(std::string key){
                return _destMnemo.find(key) != _destMnemo.end();
            }
            std::string getDestMnemonic(std::string key){
                return _destMnemo[key];
            }

        private:
            std::unordered_map<std::string, std::string> _destMnemo = initDestMnemonics();
    };

    class CompCode{
        public:
            // Initialize Mnemonics without creating an object that is accessible throughout the program.
            std::unordered_map<std::string, std::string> initCompMnemonics();
            
            bool findCompMnemonic(std::string key){
                return _compMnemo.find(key) != _compMnemo.end();
            }
            std::string getCompMnemonic(std::string key){
                return _compMnemo[key];
            }

        private:
            std::unordered_map<std::string, std::string> _compMnemo = initCompMnemonics();
    };

    class JumpCode{
        public:
            // Initialize Mnemonics without creating an object that is accessible throughout the program.
            std::unordered_map<std::string, std::string> initJumpMnemonics();
            
            bool findJumpMnemonic(std::string key){
                return _jumpMnemo.find(key) != _jumpMnemo.end();
            }
            std::string getJumpMnemonic(std::string key){
                return _jumpMnemo[key];
            }

        private:
            std::unordered_map<std::string, std::string> _jumpMnemo = initJumpMnemonics();
    };
} // namespace codeAPI
