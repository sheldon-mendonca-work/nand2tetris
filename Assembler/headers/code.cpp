#include"./code.hpp"
#include "./errors.hpp"

/*
    Default Destination Mnemonics
*/
std::unordered_map<std::string, std::string> codeAPI::DestCode::initDestMnemonics(){
    // destination mnemonics
    std::unordered_map<std::string, std::string> mpd;
    mpd.insert({"NULL", "000"});
    mpd.insert({"A", "100"});
    mpd.insert({"D", "010"});
    mpd.insert({"M", "001"});
    mpd.insert({"AD", "110"});
    mpd.insert({"AM", "101"});
    mpd.insert({"MD", "011"});
    mpd.insert({"AMD", "111"});
    // common permutations
    mpd.insert({"DA", "110"});
    mpd.insert({"MA", "101"});
    mpd.insert({"DM", "011"});

    return mpd;
}

/*
    Default Computation Mnemonics
*/
std::unordered_map<std::string, std::string> codeAPI::CompCode::initCompMnemonics(){
    std::unordered_map<std::string, std::string> mpc;
    // // computation mnemonics
    mpc.insert({"0", "101010"});
    mpc.insert({"1", "111111"});
    mpc.insert({"-1", "111010"});
    mpc.insert({"D", "001100"});
    mpc.insert({"A", "110000"});
    mpc.insert({"M", "110000"});
    mpc.insert({"!D", "001101"});
    mpc.insert({"!A", "110001"});
    mpc.insert({"!M", "110001"});
    mpc.insert({"-D", "001111"});
    mpc.insert({"-A", "110011"});
    mpc.insert({"-M", "110011"});
    mpc.insert({"D+1", "011111"});
    mpc.insert({"A+1", "110111"});
    mpc.insert({"M+1", "110111"});
    mpc.insert({"D-1", "001110"});
    mpc.insert({"A-1", "110010"});
    mpc.insert({"M-1", "110010"});
    mpc.insert({"D+A", "000010"});
    mpc.insert({"D+M", "000010"});
    mpc.insert({"D-A", "010011"});
    mpc.insert({"D-M", "010011"});
    mpc.insert({"A-D", "000111"});
    mpc.insert({"M-D", "000111"});
    mpc.insert({"D&A", "000000"});
    mpc.insert({"D&M", "000000"});
    mpc.insert({"D|A", "010101"});
    mpc.insert({"D|M", "010101"});
    //common permutations of computations
    mpc.insert({"1+D", "011111"});
    mpc.insert({"1+A", "110111"});
    mpc.insert({"1+M", "110111"});
    mpc.insert({"A+D", "000010"});
    mpc.insert({"A+M", "000010"});
    mpc.insert({"A&D", "000000"});
    mpc.insert({"M&D", "000000"});
    mpc.insert({"A|D", "010101"});
    mpc.insert({"M|D", "010101"});
    return mpc;
}

/*
    Default Jump Mnemonics
*/
std::unordered_map<std::string, std::string> codeAPI::JumpCode::initJumpMnemonics(){
    std::unordered_map<std::string, std::string> mpj;
    // // jump Mnemonics
    mpj.insert({"NULL", "000"});
    mpj.insert({"JGT", "001"});
    mpj.insert({"JEQ", "010"});
    mpj.insert({"JGE", "011"});
    mpj.insert({"JLT", "100"});
    mpj.insert({"JNE", "101"});
    mpj.insert({"JLE", "110"});
    mpj.insert({"JMP", "111"});  
    return mpj;
}