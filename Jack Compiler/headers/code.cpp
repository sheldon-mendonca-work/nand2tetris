#include "./code.hpp"


void codeAPI::Code::writeArithmetic(std::string &inputLine){
    ++_lineNumber;
    if(inputLine == "add" || inputLine == "sub"){
        _outputFileStream<<"// "<<inputLine<<std::endl;
        // Reduce address pointed by stack pointer by 1
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M-1\n";
        // Go to address and set value as y
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"D=M\n";
        // Reduce address pointed by stack pointer by 1
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M-1\n";
        // Go to address and set value as x
        _outputFileStream<<"A=M\n";
        if(inputLine == "add"){
            // Perform x+y with x in D register and store value in D register
            _outputFileStream<<"D=M+D\n";
        }else{
            // Perform x-y with x in D register and store value in D register
            _outputFileStream<<"D=M-D\n";
        }
        // A register contains address pointed by stack pointer. set value from D register
        _outputFileStream<<"M=D\n";
        // Increase address pointed by stack pointer by 1
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M+1\n";
        _outputFileStream<<std::endl;
        return;
    }

    if(inputLine == "neg" || inputLine == "not"){
        _outputFileStream<<"// "<<inputLine<<std::endl;
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M-1\n";
        _outputFileStream<<"A=M\n";
        if(inputLine == "neg"){
            _outputFileStream<<"M=-M\n";
        }else{
            _outputFileStream<<"M=!M\n";
        }
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M+1\n";
        _outputFileStream<<std::endl;
        return;
    }

    if(inputLine == "gt" || inputLine == "lt" || inputLine == "eq"){
        _outputFileStream<<"// "<<inputLine<<std::endl;
        // Take the address which is pointed at stack pointer and reduce it by 1
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M-1\n";
        // Get the value at the new stack pointer and set it as y
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"D=M\n";
        // Reduce stack pointer value by 1
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M-1\n";
        // Get the value as x and perform x-y
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"D=M-D\n";
        _outputFileStream<<"@COMPARISON_TRUE_"<<_lineNumber<<"\n";
        if(inputLine == "gt"){
            // if greater than zero, jump to COMPARISON_TRUE
            _outputFileStream<<"D;JGT\n";
        }else if(inputLine == "eq"){
            // if equal to zero, jump to COMPARISON_TRUE
            _outputFileStream<<"D;JEQ\n";
        }else if(inputLine == "lt"){
            // if less than zero, jump to COMPARISON_TRUE
            _outputFileStream<<"D;JLT\n";
        }
        
        // not equal to zero, set value at address sp to zero
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"M=0\n";
        // unconditional jump to end
        _outputFileStream<<"@COMPARISON_END_"<<_lineNumber<<"\n";
        _outputFileStream<<"0;JMP\n";
        
        _outputFileStream<<"(COMPARISON_TRUE_"<<_lineNumber<<")\n";
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"M=-1\n";
        
        _outputFileStream<<"(COMPARISON_END_"<<_lineNumber<<")\n";
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M+1\n";
        _outputFileStream<<std::endl;
        return;
    }

    if(inputLine == "and" || inputLine == "or"){
        _outputFileStream<<"// "<<inputLine<<std::endl;
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M-1\n";
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"D=M\n";
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M-1\n";
        _outputFileStream<<"A=M\n";
        if(inputLine == "and"){
            _outputFileStream<<"D=D&M\n";
        }else{
            _outputFileStream<<"D=D|M\n";
        }
        _outputFileStream<<"M=D\n";
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M+1\n";
        _outputFileStream<<std::endl;
        return;
    }

    throw errors::IllegalCallException("Illegal symbol "+inputLine);
}

void codeAPI::Code::writePush(std::string symbol, std::string &arg1, int &arg2){
    ++_lineNumber;
    _outputFileStream<<"// "<<symbol<<" "<<arg1<<" "<<arg2<<std::endl;
    
    if(arg1 == "constant"
        || arg1 == "static" // called only for clearing exercise 7, StaticTest.vm
    ){
        if(arg1 == "constant"){
            _outputFileStream<<"@"<<arg2<<std::endl;
            _outputFileStream<<"D=A\n";
        }else if(arg1 == "static"){
            _outputFileStream<<"@"<<_fileNameNoExt<<"."<<arg2<<"\n"; 
            _outputFileStream<<"D=M\n";
        }
        
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"M=D\n";
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M+1\n";
        _outputFileStream<<std::endl;
        return;
    }

    if(arg1 == "local" || arg1 == "argument" || arg1 == "this" 
        || arg1 == "that" || arg1 == "temp" || arg1 == "pointer"
        // || arg1 == "static"  // should not be called only for clearing exercise 7, StaticTest.vm
        ){
        // get the value and store it in D
        if(arg1 == "local"){
            _outputFileStream<<"@LCL\n";
        }else if(arg1 == "argument"){
            _outputFileStream<<"@ARG\n";
        }else if(arg1 == "this"){
            _outputFileStream<<"@THIS\n";
        }else if(arg1 == "that"){
            _outputFileStream<<"@THAT\n";
        }
        _outputFileStream<<"D=M\n";

        // temp static pointer are constant locations. Direct value can be stored in A register
        if(arg1 == "temp"){
            _outputFileStream<<"@5\n"<<"D=A\n";
        }else if(arg1 == "pointer"){
            _outputFileStream<<"@3\n"<<"D=A\n";
        }
        else if(arg1 == "static"){
            _outputFileStream<<"@"<<_fileNameNoExt<<"\n"<<"D=A\n"; 
        }

        //if arg2 > 0, get the new location and store it in D register 
        if(arg2 > 0){
            _outputFileStream<<"@"<<arg2<<"\n";
            _outputFileStream<<"D=A+D\n";
        }

        // get the value and store it in D
        _outputFileStream<<"A=D\n";
        _outputFileStream<<"D=M\n";
        
        // Update value at stack pointer with D
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"M=D\n";
        // Increase stack pointer by 1
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M+1\n";
        _outputFileStream<<std::endl;
        return;
    }

    throw errors::IllegalCallException("Illegal symbol "+arg1);
}

void codeAPI::Code::writePop(std::string symbol, std::string &arg1, int &arg2){
    ++_lineNumber;
    _outputFileStream<<"// "<<symbol<<" "<<arg1<<" "<<arg2<<std::endl;
    if(arg1 == "constant"
        || arg1 == "static" // called only for clearing exercise 7, StaticTest.vm
    ){
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M-1\n";
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"D=M\n";

        if(arg1 == "constant"){
            _outputFileStream<<"@"<<arg2<<std::endl;
        }else if(arg1 == "static"){
            _outputFileStream<<"@"<<_fileNameNoExt<<"."<<arg2<<"\n"; 
        }
        _outputFileStream<<"M=D\n";
        
        _outputFileStream<<std::endl;
        return;
    }

    if(arg1 == "local" || arg1 == "argument" || arg1 == "this" 
        || arg1 == "that" || arg1 == "temp" || arg1 == "pointer"
        // || arg1 == "static"  // should not be called only for clearing exercise 7, StaticTest.vm
        ){
        
        // get location of arg1 in D register
        if(arg1 == "local"){
            _outputFileStream<<"@LCL\n";
        }else if(arg1 == "argument"){
            _outputFileStream<<"@ARG\n";
        }else if(arg1 == "this"){
            _outputFileStream<<"@THIS\n";
        }else if(arg1 == "that"){
            _outputFileStream<<"@THAT\n";
        }
        _outputFileStream<<"D=M\n";
        
        if(arg1 == "temp"){
            _outputFileStream<<"@5\n"<<"D=A\n"; 
        }else if(arg1 == "pointer"){
            _outputFileStream<<"@3\n"<<"D=A\n"; 
        }
        else if(arg1 == "static"){
            _outputFileStream<<"@"<<_fileNameNoExt<<"\n"<<"D=A\n"; 
        }
        //if arg2 > 0, get the new location and store it in D register 
        if(arg2 > 0){
            _outputFileStream<<"@"<<arg2<<"\n";
            _outputFileStream<<"D=A+D\n";
        }

        // store location value in R14
        _outputFileStream<<"@R14\n";
        _outputFileStream<<"M=D\n";
        
        // Reduce stack pointer by 1
        _outputFileStream<<"@SP\n";
        _outputFileStream<<"M=M-1\n";
        // Get the value pointed by stack pointer and set it in D register
        _outputFileStream<<"A=M\n";
        _outputFileStream<<"D=M\n";
        
        // store value of R14 in A register 
        _outputFileStream<<"@R14\n";
        _outputFileStream<<"A=M\n";
        
        // Update value of A register from D.
        _outputFileStream<<"M=D\n";
        
        _outputFileStream<<std::endl;
        return;
    }

    throw errors::IllegalCallException("Illegal symbol "+arg1);
}

void codeAPI::Code::writeFunction(std::string symbol, std::string &arg1, int &arg2){
    ++_lineNumber;
    _outputFileStream<<"// "<<symbol<<" "<<arg1<<" "<<arg2<<std::endl;
    
    _outputFileStream<<"("<<arg1<<")\n";
    // push 0 to location pointed by stack pointer
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"A=M\n";
    for(int i = 0; i < arg2; i++){
        _outputFileStream<<"M=0\n";
        _outputFileStream<<"A=A+1\n";
    }

    // increase stack pointer by arg2 locations
    _outputFileStream<<"@"<<arg2<<"\n";
    _outputFileStream<<"D=A\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"M=D+M\n";

    _currentFunction = arg1;

    _outputFileStream<<std::endl;
}

void codeAPI::Code::writeLabel(std::string symbol, std::string &arg1){
    _outputFileStream<<"// "<<symbol<<" "<<arg1<<std::endl;
    
    _outputFileStream<<"("<<_currentFunction<<"$"<<arg1<<")\n";
    
    _outputFileStream<<std::endl;
}

void codeAPI::Code::writeGoto(std::string symbol, std::string &arg1){
    ++_lineNumber;
    _outputFileStream<<"// "<<symbol<<" "<<arg1<<std::endl;
    
    _outputFileStream<<"@"<<_currentFunction<<"$"<<arg1<<"\n";
    _outputFileStream<<"0;JMP\n";
    
    _outputFileStream<<std::endl;
}
//sys init= 52 main fibo = 318
void codeAPI::Code::writeIf(std::string symbol, std::string &arg1){
    _outputFileStream<<"// "<<symbol<<" "<<arg1<<std::endl;
    
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"M=M-1\n";
    _outputFileStream<<"A=M\n";
    _outputFileStream<<"D=M\n";

    _outputFileStream<<"@"<<_currentFunction<<"$"<<arg1<<"\n";
    _outputFileStream<<"D;JNE\n";
    
    _outputFileStream<<std::endl;
}

void codeAPI::Code::writeCall(std::string symbol, std::string &arg1, int &arg2){
    ++_lineNumber;
    _outputFileStream<<"// "<<symbol<<" "<<arg1<<" "<<arg2<<std::endl;
    
    // Push return address on stack
    _outputFileStream<<"// -- Push return address on stack\n";
    _outputFileStream<<"@_RETURN_"<<arg1<<"_"<<_lineNumber<<"\n";
    _outputFileStream<<"D=A\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"A=M\n";
    _outputFileStream<<"M=D\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"M=M+1\n";

    _outputFileStream<<"// -- Push LCL on stack\n";
    _outputFileStream<<"@LCL\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"A=M\n";
    _outputFileStream<<"M=D\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"M=M+1\n";

    _outputFileStream<<"// -- Push ARG on stack\n";
    _outputFileStream<<"@ARG\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"A=M\n";
    _outputFileStream<<"M=D\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"M=M+1\n";
    
    _outputFileStream<<"// -- Push THIS on stack\n";
    _outputFileStream<<"@THIS\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"A=M\n";
    _outputFileStream<<"M=D\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"M=M+1\n";

    _outputFileStream<<"// -- Push THAT on stack\n";
    _outputFileStream<<"@THAT\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"A=M\n";
    _outputFileStream<<"M=D\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"M=M+1\n";


    _outputFileStream<<"// -- ARG = SP-n-5\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@5\n";
    _outputFileStream<<"D=D-A\n";
    _outputFileStream<<"@"<<arg2<<"\n";
    _outputFileStream<<"D=D-A\n";
    _outputFileStream<<"@ARG\n";
    _outputFileStream<<"M=D\n\n";

    _outputFileStream<<"// -- LCL = SP\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@LCL\n";
    _outputFileStream<<"M=D\n";

    
    // go to function written in string arg1
    _outputFileStream<<"@"<<arg1<<"\n";
    _outputFileStream<<"0;JMP\n";
    
    // Create return label
    _outputFileStream<<"(_RETURN_"<<arg1<<"_"<<_lineNumber<<")\n";

    _outputFileStream<<std::endl;
}

void codeAPI::Code::writeReturn(std::string symbol){
    ++_lineNumber;
    _outputFileStream<<"// "<<symbol<<std::endl;

    // store lcl in temp address
    _outputFileStream<<"// -- Store LCL in R13\n";
    _outputFileStream<<"@LCL\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@R13\n";
    _outputFileStream<<"M=D\n\n";

    // Ret (r14) = frame(r13) - 5
    _outputFileStream<<"// -- R14 = R13-5\n";
    _outputFileStream<<"@5\n";
    _outputFileStream<<"A=D-A\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@R14\n";
    _outputFileStream<<"M=D\n\n";

    //*ARG=pop()
    _outputFileStream<<"// -- *ARG=pop()\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"AM=M-1\n";
    _outputFileStream<<"D=M\n"; // store pop() value to D
    _outputFileStream<<"@ARG\n";
    _outputFileStream<<"A=M\n";
    _outputFileStream<<"M=D\n\n"; // store D to *ARG

    //SP=ARG+1
    _outputFileStream<<"// -- SP=ARG+1\n";
    _outputFileStream<<"@ARG\n";
    _outputFileStream<<"D=M+1\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"M=D\n\n";

    //THAT=*(FRAME-1)
    _outputFileStream<<"// -- THAT=*(R13-1)\n";
    _outputFileStream<<"@R13\n";
    _outputFileStream<<"D=M-1\n";
    _outputFileStream<<"AM=D\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@THAT\n";
    _outputFileStream<<"M=D\n\n";
    // THAT => R13

    //THIS=*(FRAME-2)
    _outputFileStream<<"// -- THIS=*(R13-2)\n";
    _outputFileStream<<"@R13\n";
    _outputFileStream<<"D=M-1\n";
    _outputFileStream<<"AM=D\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@THIS\n";
    _outputFileStream<<"M=D\n\n";
    // THIS => R13

    //ARG=*(FRAME-3)
    _outputFileStream<<"// -- ARG=*(R13-3)\n";
    _outputFileStream<<"@R13\n";
    _outputFileStream<<"D=M-1\n";
    _outputFileStream<<"AM=D\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@ARG\n";
    _outputFileStream<<"M=D\n\n";
    // ARG => R13

    //LCL=*(FRAME-4)
    _outputFileStream<<"// -- LCL=*(R13-4)\n";
    _outputFileStream<<"@R13\n";
    _outputFileStream<<"D=M-1\n";
    _outputFileStream<<"AM=D\n";
    _outputFileStream<<"D=M\n";
    _outputFileStream<<"@LCL\n";
    _outputFileStream<<"M=D\n\n";
    // LCL=> R13

    //goto RET
    _outputFileStream<<"// -- goto R14\n";
    _outputFileStream<<"@R14\n";
    _outputFileStream<<"A=M\n";
    _outputFileStream<<"0;JMP\n";
    
    _outputFileStream<<std::endl;
}


void codeAPI::Code::writeInit(){
    _outputFileStream<<"// Initial Set up"<<std::endl;

    _outputFileStream<<"@256\n";
    _outputFileStream<<"D=A\n";
    _outputFileStream<<"@SP\n";
    _outputFileStream<<"M=D\n\n";

    // Call function Sys.init
    std::string _initFn = "Sys.init";
    int _pars = 0;
    writeCall("call", _initFn, _pars);

    // _outputFileStream<<"@PROGRAM_END"<<std::endl;
    // _outputFileStream<<"0;JMP\n"<<std::endl;

    // Create Sys.init
    // writeFunction("function", _initFn, _pars);
    _outputFileStream<<std::endl;
}


void codeAPI::Code::infiniteLoop(){
    // create return for Sys.init
    // writeReturn("return");
    
    _outputFileStream<<"// Infinite Loop"<<std::endl;
    _outputFileStream<<"(PROGRAM_END)"<<std::endl;
    _outputFileStream<<"@PROGRAM_END"<<std::endl;
    _outputFileStream<<"0;JMP"<<std::endl;
}

/*
    Use input file name or input file location as a parameter.
    This function is primarily for static variables.
*/
void codeAPI::Code::setFileNameNoExt(std::string inputFileName){
    int i = inputFileName.length()-1;
    while(i >= 0 && inputFileName[i] != '.')i--;
    i--;
    
    _fileNameNoExt = "";
    while(i >= 0 && inputFileName[i] != '/'){
        _fileNameNoExt = inputFileName[i--]+_fileNameNoExt;
    }

    if(_fileNameNoExt.length() == 0){
        throw errors::FileHandlingException("File naming is incorrect: "+inputFileName);
    }
}

void codeAPI::Code::writeToFile(std::string inputLine){
    _outputFileStream<<inputLine;
}