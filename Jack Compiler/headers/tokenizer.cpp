#include"./tokenizer.hpp"

/*
    Function to check if next token is present. 
    Ignores all whitespaces and comments and _pos is set to first character
*/
bool tokenizerAPI::Tokenizer::hasMoreTokens(){
    // check if input is available
    
    if(!_in.is_open()){
        throw errors::FileHandlingException("Cannot find input file.");
    }

    while(!_in.eof()){
        if(_pos >= _currentLine.length()){
            _pos = 0;
            std::getline(_in, _currentLine);
            _lineNumber++;
        }
        // remove whitespaces
        removeWhiteSpace();
        
        // check if end of line is reached or comment is found
        if(checkSingleLineComment()){
            _pos = _currentLine.length();
            continue;
        }

        // check multiline comment
        checkMultiLineComment();

        // remove whitespaces after multiline comments
        removeWhiteSpace();

        if(_pos >= _currentLine.length()) {
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
void tokenizerAPI::Tokenizer::removeWhiteSpace(){
    while((_pos <  _currentLine.length())&& isspace(_currentLine[_pos])) _pos++;
}

/*
    Checks if next two characters are "//" or end of line is reached.
    For multiline comment, a separate function is written.
*/
bool tokenizerAPI::Tokenizer::checkSingleLineComment(){
    if(_currentLine.length() == _pos) return true;
    if(_pos <= _currentLine.length()-2){
        if(_currentLine[_pos] == '/' && _currentLine[_pos+1] == '/'){
            return true;
        }
    }

    return false;
}

/*
    Checks if next two characters are "/*".
    Continue till "*""/" is reached    
*/
void tokenizerAPI::Tokenizer::checkMultiLineComment(){
    if(_pos <= _currentLine.length()-2){
        if(_currentLine[_pos] == '/' && _currentLine[_pos+1] == '*'){
            _pos+=2;
            _isComment = true;
        }
    }

    while(_isComment && _pos <= _currentLine.length()){
        if(_currentLine[_pos-1] == '*' && _currentLine[_pos] == '/'){
            _isComment = false;
            _pos++;
            break;
        }
        _pos++;
    }
}

/*
    A keyword/identifier can be any sequence of letters, digits,
    underscore (_), dot (.), dollar sign ($), and colon (:) that does not begin with a
    digit.
*/
bool tokenizerAPI::Tokenizer::checkValidSymbolChar(){
    return (_currentLine[_pos] >= 'a' && _currentLine[_pos] <= 'z') ||
            (_currentLine[_pos] >= 'A' && _currentLine[_pos] <= 'Z') ||
            (_currentLine[_pos] >= '0' && _currentLine[_pos] <= '9') ||
            _currentLine[_pos] == '_' ||
            _currentLine[_pos] == '$' || _currentLine[_pos] == ':';
}

void tokenizerAPI::Tokenizer::getKeyWordOrIdentifer(){
    std::string curr = "";
    while(_pos < _currentLine.length() && checkValidSymbolChar()){
        curr += _currentLine[_pos++];
    }
    for(int i = 0; i < _keyWordTableSize; i++){
        if(_keyWordTable[i] == curr){
            _token = _keyWordTable[i];
            _tokenType = "keyword";
            return;
        }
    }

    _token = curr;
    _tokenType = "identifier";
}

void tokenizerAPI::Tokenizer::getIntVal(){

    while(_currentLine[_pos] >= '0' && _currentLine[_pos] <= '9'){
        _token += _currentLine[_pos];
        _pos++;
    }
    _tokenType = "integerConstant";
}

void tokenizerAPI::Tokenizer::getStringVal(){
    _pos++;
    while(_pos < _currentLine.length() && _currentLine[_pos] != '"'){
        _token += _currentLine[_pos++];
    }
    _tokenType = "stringConstant";
    _pos++;
}

void tokenizerAPI::Tokenizer::getSymbol(){
    for(char c:_symbolTable){
        if(_currentLine[_pos] == c){
            _tokenType = "symbol";
            _token = _currentLine[_pos];
            _pos++;
            if(_token == "<"){
                _token = "&lt;";
            }else if(_token == "&"){
                _token = "&amp;";
            }else if(_token == ">"){
                _token = "&gt;";
            }
            return;
        }
    }

    throw new errors::UndefinedSymbolException("Illegal symbol on: " + _currentLine + ": " + _currentLine[_pos]);
}

/*
    Since this activates only after hasCommand, we use advance to find out the type of command
*/
void tokenizerAPI::Tokenizer::advance(){
    if(!_in || _in.eof() || _pos >= _currentLine.length()){
        throw errors::IllegalCallException("Cannot use advance function with no input: " + _currentLine);
    }

    if((_currentLine[_pos] >= 'a' && _currentLine[_pos] <= 'z') ||
        (_currentLine[_pos] >= 'A' && _currentLine[_pos] <= 'Z') ||
        (_currentLine[_pos] == '_')){
            _token = "";
            _tokenType = "";
            getKeyWordOrIdentifer();
    }else if(_currentLine[_pos] >= '0' && _currentLine[_pos] <= '9'){
        _token = "";
        getIntVal();
    }else if(_currentLine[_pos] == '"'){
        _token = "";
        getStringVal();
    }else{
        getSymbol();
    }
    
}