#include"./parser.hpp"

/*
    Function to check if next command is present. 
    Ignores all whitespaces and comments and _pos is set to first character
*/
bool parserAPI::Parser::hasMoreCommands(){
    // check if input is available
    
    if(!Parser::_in){
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
    A_Command Handler
*/
void parserAPI::Parser::ACommandHandler(){
    _pos++;
    _cmdType = ERROR;
    _symbol = "";
    if(_currentLine[_pos] >= '0' && _currentLine[_pos] <= '9'){
        while(_currentLine[_pos] >= '0' && _currentLine[_pos] <= '9'){
            _symbol += _currentLine[_pos++];
        }

        removeWhiteSpace();
        if(!checkComment()){
            _symbol = "";
            throw errors::SyntaxErrorException(_lineNumber, _pos, "Number should not have spaces");
        }
    }else{
        while(_pos < _currentLine.length() && checkValidSymbolChar()){
            _symbol += _currentLine[_pos++];
        }

        removeWhiteSpace();
        if(!checkComment()){
            _symbol = "";
            throw errors::SyntaxErrorException(_lineNumber, _pos, "Symbol should not have spaces");
        }
    }

    _cmdType = A_COMMAND;
    return;
}

/*
    L Command Handler
*/
void parserAPI::Parser::LCommandHandler(){
    _pos++;
    _cmdType = ERROR;
    _symbol = "";

    while(_pos < _currentLine.length() && _currentLine[_pos] != ')' && checkValidSymbolChar()){
        _symbol += _currentLine[_pos++];
    }

    if(_pos == _currentLine.length() || _currentLine[_pos] != ')'){
        throw errors::SyntaxErrorException(_lineNumber, _pos, "Symbol should not have spaces and should end with ')'");
    }

    _cmdType = L_COMMAND;
    return;
}

/*
    C Command Handler
    is of the type ?[dest =] comp?[;jump]
*/
void parserAPI::Parser::CCommandHandler(){
    _dest = _comp = _jump = "NULL";
    _cmdType = ERROR;
    std::string curr = "";
    char lastC = '1';

    while(_pos < _currentLine.length()){
        removeWhiteSpace(); 
        if(_pos >= _currentLine.length()) break;
        while (_pos < _currentLine.length()){
            if(_currentLine[_pos] == '=' || _currentLine[_pos] == ';' || _currentLine[_pos] == '/'){
                break;
            }
            if(isspace(_currentLine[_pos])){
                _pos++;
                continue;
            }
            curr += _currentLine[_pos++];
        }

        // Check for comment
        if(_currentLine[_pos] == '/'){
            if(_currentLine[_pos+1] != '/'){
                throw errors::SyntaxErrorException(_lineNumber, _pos, "Illegal Character");
            }else{
                _pos = _currentLine.length();
            }
        }
        //Check for Destination
        else if(_currentLine[_pos] == '=' && lastC == '1'){
            _dest = curr;
            lastC = _currentLine[_pos];
        }
        //Check for Jump
        else if (lastC == ';'){
            _jump = curr;
            lastC = _currentLine[_pos];
        }
        //Check for Computation
        else if((lastC == '1' && _currentLine[_pos] == ';') || lastC == '='){
            _comp = curr;
            lastC = _currentLine[_pos];
        }
        curr="";
        _pos++;           
    }

    // Computation is mandatory and should exist
    if(_comp == "NULL"){
        throw errors::SyntaxErrorException(_lineNumber, _pos, "Computation field is required");
    }

    // One of destination or jump should exist
    if((_dest == "NULL") ^ (_jump == "NULL") == 0){
        throw errors::SyntaxErrorException(_lineNumber, _pos, "One of jump or  is required");
    }

    _cmdType = C_COMMAND;
    return;
}

/*
    Since this activates only after hasCommand, we use advance to find out the type of command
    The command type is either one of A_COMMAND, C_COMMAND, L_COMMAND.
*/
void parserAPI::Parser::advance(){
    if(!_in.is_open() || _in.eof() || _pos >= _currentLine.length()){
        throw errors::IllegalCallException("Cannot use advance function with no input.\n");
    }

    if(_currentLine[_pos] == '@'){
        ACommandHandler();
        _lineNumber++;
    }else if(_currentLine[_pos] == '('){
        LCommandHandler();
    }else{
        CCommandHandler();
        _lineNumber++;
    }
}

CommandType parserAPI::Parser::commandType(){
    return _cmdType;
}

std::string parserAPI::Parser::symbol(){
    return _symbol;
}

std::string parserAPI::Parser::dest(){
    return _dest;
}

std::string parserAPI::Parser::comp(){
    return _comp;
}

std::string parserAPI::Parser::jump(){
    return _jump;
}

int parserAPI::Parser::getLineNumber(){
    return _lineNumber;
}

std::string parserAPI::Parser::getCurrentLine(){
    return _currentLine;
}