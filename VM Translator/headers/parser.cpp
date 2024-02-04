#include"./parser.hpp"

/*
    Function to check if next command is present. 
    Ignores all whitespaces and comments and _pos is set to first character
*/
bool parserAPI::Parser::hasMoreCommands(){
    // check if input is available
    
    if(!_in.is_open()){
        throw errors::FileHandlingException("Cannot find input file.");
    }

    while(!_in.eof()){
        _pos = 0;
        std::getline(_in, _currentLine);
                
        // remove whitespaces
        removeWhiteSpace();
        
        // check if end of line is reached or comment is found
        if(checkComment() || _pos >= _currentLine.length()){
            continue;
        }

        break;
    }
    
    if(_in.eof()) return false;
    return true;
}

/*
    Removes white spaces until either:
    1. End of line is reached
    2. First character is found
*/
void parserAPI::Parser::removeWhiteSpace(){
    while((_pos <  _currentLine.length())&& isspace(_currentLine[_pos])) _pos++;
}

/*
    Checks if next two characters are "//" or end of line is reached.
*/
bool parserAPI::Parser::checkComment(){
    if(_currentLine.length() == _pos) return true;
    if(_pos <= _currentLine.length()-2){
        if(_currentLine[_pos] == '/' && _currentLine[_pos+1] == '/'){
            return true;
        }
    }
    return false;
}

/*
    A user-defined symbol can be any sequence of letters, digits,
    underscore (_), dot (.), dollar sign ($), and colon (:) that does not begin with a
    digit.
*/
bool parserAPI::Parser::checkValidSymbolChar(){
    return (_currentLine[_pos] >= 'a' && _currentLine[_pos] <= 'z') ||
            (_currentLine[_pos] >= 'A' && _currentLine[_pos] <= 'Z') ||
            (_currentLine[_pos] >= '0' && _currentLine[_pos] <= '9') ||
            _currentLine[_pos] == '_' || _currentLine[_pos] == '.' ||
            _currentLine[_pos] == '$' || _currentLine[_pos] == ':';
}

/*
    A user-defined symbol can be any sequence of letters, digits,
    underscore (_), dot (.), dollar sign ($), and colon (:) that does not begin with a
    digit.
*/
void parserAPI::Parser::createSymbol(){
    removeWhiteSpace();
    _symbol = ""; _arg1 = ""; _arg2 = 0;
    while(_pos<_currentLine.length() && !isspace(_currentLine[_pos]) && _currentLine[_pos] != '/'){
        _symbol += _currentLine[_pos++];
    }

    // Arithmetic commands
    if(_symbol == "add" || _symbol == "sub" || _symbol == "neg" ||
       _symbol == "eq" || _symbol == "gt" || _symbol == "lt" || 
       _symbol == "and" || _symbol == "or" || _symbol =="not"){

        _cmdType = "C_ARITHMETIC";
    
    // Program flow Commands
    }else if(_symbol == "if-goto"){
        _cmdType = "C_IF"; findArg1();
    }else if(_symbol == "label"){
        _cmdType = "C_LABEL"; findArg1();
    }else if(_symbol == "goto"){
        _cmdType = "C_GOTO"; findArg1();
    
    // Memory Access commands
    }else if(_symbol == "push"){
        _cmdType = "C_PUSH"; findArg1(); findArg2();
    }else if(_symbol == "pop"){
        _cmdType = "C_POP"; findArg1(); findArg2();
    
    // Function calling findArguments 
    }else if(_symbol == "function"){
        _cmdType = "C_FUNCTION"; findArg1(); findArg2();
    }else if(_symbol == "return"){
        _cmdType = "C_RETURN";
    }else if(_symbol == "call"){
        _cmdType = "C_CALL"; findArg1(); findArg2();

    // Unrecognised command. Error is thrown.
    }else{
        _cmdType = "ERROR";
        throw errors::SyntaxErrorException(_lineNumber, _pos, "Wrong symbol: "+_currentLine);
    }
}

void parserAPI::Parser::findArg1(){
    removeWhiteSpace();
    while(_pos < _currentLine.length() && !isspace(_currentLine[_pos]) && _currentLine[_pos] != '/'){
        _arg1 += _currentLine[_pos++];
    }
}

void parserAPI::Parser::findArg2(){
    removeWhiteSpace();
    while(_pos < _currentLine.length() && !isspace(_currentLine[_pos]) && _currentLine[_pos] != '/'){
        _arg2 = _arg2*10 + (_currentLine[_pos]-'0');
        _pos++;
    }
}

/*
    Since this activates only after hasCommand, we use advance to find out the type of command
*/
void parserAPI::Parser::advance(){
    if(!_in || _in.eof() || _pos >= _currentLine.length()){
        throw errors::IllegalCallException("Cannot use advance function with no input: " + _currentLine);
    }

    createSymbol();
    _lineNumber++;
}

std::string parserAPI::Parser::commandType(){
    return _cmdType;
}

int parserAPI::Parser::getLineNumber(){
    return _lineNumber;
}

std::string parserAPI::Parser::getCurrentLine(){
    return _currentLine;
}

std::string parserAPI::Parser::arg1(){
    return _arg1;
}

int parserAPI::Parser::arg2(){
    return _arg2;
}

std::string parserAPI::Parser::getSymbol(){
    return _symbol;
}
