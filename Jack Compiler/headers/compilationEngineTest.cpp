// #include"./compilationEngine.hpp"

// void compileAPI::Compile::getNextLine(std::string err){
//     if(!_in.eof()){
//         getline(_in, _inputLine);
//     }else{
//         throw errors::IllegalCallException(err);
//     }
// }

// void compileAPI::Compile::getTokenType(){
//     _pos = 1;
//     _tokenType = "";
//     while(_inputLine[_pos] != '>') _tokenType += _inputLine[_pos++];
// }

// void compileAPI::Compile::getToken(){
//     _pos = 0;
//     _token = "";
//     while(_inputLine[_pos] != '>') _pos++;
//     _pos += 2;
//     while(!(_inputLine[_pos] == ' ' && _inputLine[_pos+1] == '<')) _token += _inputLine[_pos++];
// }

// bool compileAPI::Compile::checkVariableType(){
//     for(std::string s:types){
//         if(s == _token) return true;
//     }
//     if(_st.find(_token) != _st.end()) return true;
//     return false;
// }

// void compileAPI::Compile::compileTokens(){
//     if(!_in.eof()){
//         getline(_in, _inputLine);
//     }
//     getline(_in, _inputLine);
//     compileClass();

//     throw errors::IllegalCallException("Illegal call at: "+ _inputLine);
// } 

// void compileAPI::Compile::compileClass(){
//     _out<<"<class>\n";
    
//     _out<<_inputLine<<"\n";

//     // identifier
//     getNextLine("Identifier should be present after class.");
//     getTokenType();
//     getToken();
//     if(_tokenType != "identifier"){
//         throw errors::IllegalCallException("Identifier should be present after class: "+ _inputLine);
//     }
//     _st.insert(_token);
//     _out<<_inputLine<<"\n";
    
//     // symbol
//     getNextLine("Missing '{'" + _inputLine);
//     getToken();
    
//     if(_token != "{"){
//         throw errors::IllegalCallException("Missing '{: "+ _inputLine);
//     }
//     _out<<_inputLine<<"\n";

    
//     // declaration, routine or completed
//     while(1){
//         getNextLine("Class is not completed: "+_inputLine);
//         getTokenType();
//         getToken();
//         if(_tokenType == "keyword"){
//             if(_token == "static" || _token == "field"){
//                 compileClassVarDec();
//             }else if(_token == "constructor" || _token == "function" || _token == "method"){
//                 compileSubroutine();
//             }else if(_token == "}"){
//                 _out<<_inputLine<<"\n";
//                 break;
//             }else{
//                 throw errors::IllegalCallException("Class should have functions or fields:" + _inputLine);
//             }
//         }else{
//             throw errors::IllegalCallException("Class definition must begin with a keyword:" + _inputLine);
//         }
//     }
//     _out<<"</class>\n";
// }

// /*
//     class variable declarations are of the form:
//     ('static' | 'field') type varName (',' varName)';'
//     We run a loop till we reach ';' or the end of file.
//     If we observe a ',' the loop is continued;
// */
// void compileAPI::Compile::compileClassVarDec(){
    
//     _out<<"<classVarDec>\n";
//     _out<<_inputLine<<"\n";
    
//     getNextLine("Variable type is undefined:" + _inputLine);
//     getToken();
    
//     if(checkVariableType()){
//         _out<<_inputLine<<"\n";
//     }else{
//         throw errors::IllegalCallException("Variable type is invalid:" + _inputLine);
//     }

//     while(_token != ";"){
//         getNextLine("Variable is not present");
//         getTokenType();
//         getToken();
//         if(_tokenType != "identifier"){
//             throw errors::IllegalCallException("Variable name is invalid:" + _inputLine);
//         }
//         _out<<_inputLine<<"\n";
//         getNextLine("Illegal termination of declaration: "+_inputLine);
//         getToken();
//         if(_token == ","){
//             _out<<_inputLine<<"\n";
//         }
//     }

//     _out<<_inputLine<<"\n";
//     _out<<"</classVarDec>\n";
// }

// void compileAPI::Compile::compileSubroutine(){
//     _out<<"<subroutineDec>\n";
//     _out<<_inputLine<<"\n";
    
//     getNextLine("Function type is undefined:" + _inputLine);
//     getToken();
    
//     if(checkVariableType() || _token == "void"){
//         _out<<_inputLine<<"\n";
//     }else{
//         throw errors::IllegalCallException("Function type is invalid:" + _inputLine);
//     }

//     getNextLine("Function name is not present");
//     getTokenType();
    
//     if(_tokenType != "identifier"){
//         throw errors::IllegalCallException("Function name is invalid:" + _inputLine);
//     }
//     _out<<_inputLine<<"\n";

//     getNextLine("Bracket '(' is missing.");
//     getToken();
//     if(_token != "("){
//         throw errors::IllegalCallException("Bracket '(' is missing.");
//     }
//     _out<<_inputLine<<"\n";

//     getNextLine("Bracket ')' is missing.");
//     getToken();
//     compileParameterList();

//     if(_token != ")"){
//         throw errors::IllegalCallException("Bracket ')' is missing.");
//     }
//     _out<<_inputLine<<"\n";

//     getNextLine("Sub routine body must start with '{': "+_inputLine);
//     getToken();
//     if(_token != "{"){
//         throw errors::IllegalCallException("Sub routine body must start with '{': "+_inputLine);
//     }
//     _out<<"<subroutineBody>\n";
//     _out<<_inputLine<<"\n";

//     while(_token != "}"){
//         getNextLine("Sub routine body must start with '{': "+_inputLine);
//         getToken();
//         if(_token == "var"){
//             compileVarDec();
//         }else if(_token == "let" || _token == "if" || _token == "while" || _token == "do" || _token == "return"){
//             compileStatements();
//         }else break;
//     }

//     if(_token != "}"){
//         throw errors::IllegalCallException("Sub routine body must end with '}': "+_inputLine);
//     }
//     _out<<_inputLine<<"\n";
//     _out<<"</subroutineBody>\n";

//     _out<<"</subroutineDec>\n";
// }

// void compileAPI::Compile::compileParameterList(){
//     _out<<"<parameterList>\n";
    
//     while(_token != ")"){
//         getNextLine("Variable Type is not present");
//         getTokenType();
//         getToken();

//         if(!checkVariableType()){
//             throw errors::IllegalCallException("Variable Type is invalid:" + _inputLine);
//         }

//         _out<<_inputLine<<"\n";

//         getNextLine("Variable Type is not present");
//         getTokenType();
//         if(_tokenType != "identifier"){
//             throw errors::IllegalCallException("Variable Name is invalid:" + _inputLine);
//         }
//         _out<<_inputLine<<"\n";

//         getNextLine("Illegal termination of declaration: "+_inputLine);
//         getToken();
//         if(_token == ","){
//             _out<<_inputLine<<"\n";
//         }
//     }

//     _out<<_inputLine<<"\n";
//     _out<<"</parameterList>\n";
// }

// void compileAPI::Compile::compileVarDec(){
//     _out<<"<varDec>\n";
//     _out<<_inputLine<<"\n";

//     getNextLine("Variable type is not present");
//     getTokenType();
//     getToken();
//     if(!checkVariableType()){
//         throw errors::IllegalCallException("Variable name is invalid:" + _inputLine);
//     }
//     _out<<_inputLine<<"\n";
        
//     while(_token != ";"){
//         getNextLine("Variable name is not present");
//         getTokenType();
//         getToken();
//         if(_tokenType != "identifier"){
//             throw errors::IllegalCallException("Variable name is invalid:" + _inputLine);
//         }
//         _out<<_inputLine<<"\n";
//         getNextLine("Illegal termination of declaration: "+_inputLine);
//         getToken();
//         if(_token == ","){
//             _out<<_inputLine<<"\n";
//         }
//     }

//     _out<<"</varDec>\n";
// }

// void compileAPI::Compile::compileStatements(){
    
// }

// void compileAPI::Compile::compileDo(){
    
// }

// void compileAPI::Compile::compileLet(){
    
// }

// void compileAPI::Compile::compileWhile(){
    
// }

// void compileAPI::Compile::compileReturn(){
    
// }

// void compileAPI::Compile::compileIf(){
    
// }

// void compileAPI::Compile::compileExpression(){
    
// }

// void compileAPI::Compile::compileTerm(){
//     _out<<_inputLine;
// }

// void compileAPI::Compile::compileExpressionList(){
    
// }   

