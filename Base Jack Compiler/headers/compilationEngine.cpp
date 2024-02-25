#include"./compilationEngine.hpp"

/*
    Checks if string is a part of keyboardConstant[] = {"true", "false", "null", "this"};
*/
bool compileAPI::Compile::checkKeyboardConst(){
    for(std::string &s:keywordConstant){
        if(s == _token) return true;
    }
    return false;
}

/*
    Checks if string is a part of unaryTerm[] = {"~", "-"}
*/
bool compileAPI::Compile::checkUnaryTerm(){
    for(std::string &s:unaryTerm){
        if(s == _token) return true;
    }
    return false;
}

/*
    Checks if string is a part of term[] = {"+", "-", "*", "/", "&amp;", "|", "&lt;", "&gt;", "="}
*/
bool compileAPI::Compile::checkTerm(){
    for(std::string &s:term){
        if(s == _token) return true;
    }
    return false;
}

/*
    Gets the input line from tokenizer.
    Takes 3 arguments:
    1. Error message to be shown if no line is received.
    2. tokenType matches the input line.
    3. token matches the input token
*/
void compileAPI::Compile::getNextLine(const std::string &errMsg, const std::string &tokenType, const std::string &token){
    if(!_in.eof()){
        getline(_in, _inputLine);
        _pos = 1;
        _tokenType = "";
        _token = "";
        while(_inputLine[_pos] != '>') _tokenType += _inputLine[_pos++];
        _pos += 2;
        while(!(_inputLine[_pos] == ' ' && _inputLine[_pos+1] == '<')) _token += _inputLine[_pos++];

        if(tokenType.length() > 0 && tokenType != _tokenType){
            throw errors::IllegalCallException("Invalid token type: " + tokenType + ". Line: " + _inputLine);
        }

        if(token.length() > 0 && token != _token){
            throw errors::IllegalCallException("Invalid token : " + token + ". Line: " + _inputLine);
        }
    
    }else{
        throw errors::IllegalCallException(errMsg);
    }
}

/*
    Writes a line to output file
*/
void compileAPI::Compile::writeLine(){
    _out<<_inputLine<<"\n";
}

/*
    Start of compilation. <tokens>  and </tokens> are skipped.
*/
void compileAPI::Compile::compileTokens(){
    getline(_in, _inputLine); // <tokens>
    getNextLine("", "", ""); // <class>
    compileClass();
    getline(_in, _inputLine); // </tokens>
} 

/*
    Compiles a class. Grammar is of the type:
    'class' className '{' classVarDec* subroutineDec* '}'
*/
void compileAPI::Compile::compileClass(){
    _out<<"<class>\n";
    writeLine(); // class

    getNextLine("Identifier should be present after class.", "identifier", ""); //className
    writeLine();
    
    getNextLine("Missing '{'" + _inputLine, "", "{"); // '{'    
    writeLine();

    
    // run till all declarations and routines are completed. Class is terminated by '}'
    getNextLine("Class is not completed: "+_inputLine, "", "");
    while(1){
                
        if(_tokenType == "keyword"){
            if(_token == "static" || _token == "field"){
                compileClassVarDec();
            }else if(_token == "constructor" || _token == "function" || _token == "method"){
                compileSubroutine();
            }else{
                throw errors::IllegalCallException("Class should have functions or fields:" + _inputLine);
            }
        }else if(_token == "}"){
            writeLine();
            break;
        }else{
            std::cout<<_token<<std::endl;
            throw errors::IllegalCallException("Class definition must begin with a keyword:" + _inputLine);
        }
    }
    _out<<"</class>\n";
}

/*
    class variable declarations are of the form:
    ('static' | 'field') type varName (',' varName)';'
    We run a loop till we reach ';' or the end of file.
    If we observe a ',' the loop is continued;
*/
void compileAPI::Compile::compileClassVarDec(){
    
    _out<<"<classVarDec>\n";
    writeLine(); // static | field
    
    getNextLine("Variable type is undefined:" + _inputLine, "", ""); // type
    writeLine();

    while(_token != ";"){
        getNextLine("Variable is not present", "identifier", ""); // varName
        writeLine();

        getNextLine("Illegal termination of declaration: "+_inputLine, "", ""); // next varName | ','  | ';'
        
        if(_token == ",") writeLine();
    }

    writeLine();
    _out<<"</classVarDec>\n";
}

/*
    subroutine is of the type:
    ('constructor' | 'function' | 'method') ('void' | type) subroutineName '(' parameterList ')' subroutineBody
*/
void compileAPI::Compile::compileSubroutine(){
    _out<<"<subroutineDec>\n";
    writeLine(); //'constructor' | 'function' | 'method'
    
    getNextLine("Function type is undefined:" + _inputLine, "", ""); // 'void' | type
    writeLine();

    getNextLine("Function name is not present", "identifier", ""); // subroutineName 
    writeLine();

    getNextLine("Bracket '(' is missing.", "", "(");
    writeLine();

    getNextLine("Bracket ')' is missing.", "", ""); // parameterList | ')'
    
    compileParameterList();

    if(_token != ")"){
        throw errors::IllegalCallException("Bracket ')' is missing.");
    }
    writeLine();

    // subroutine body handling
    getNextLine("Sub routine body must start with '{': "+_inputLine, "", "{");
    
    _out<<"<subroutineBody>\n";
    writeLine();

    if(_token != "}"){
        getNextLine("Sub routine body must start with '{': "+_inputLine, "", "");
        
        while(_token == "var"){
            compileVarDec();
        }
        
        while(_token == "let" || _token == "if" || _token == "while" || _token == "do" || _token == "return"){
            compileStatements();
        }
    }

    if(_token != "}"){
        throw errors::IllegalCallException("Sub routine body must end with '}': "+_inputLine);
    }
   
    writeLine();
    getNextLine("", "", "");
    _out<<"</subroutineBody>\n";
    _out<<"</subroutineDec>\n";
}

/*
    Parameter list is of the type:
    ((type varName) (',' type varName)?) | null

    A loop is run till ')' is found.
*/
void compileAPI::Compile::compileParameterList(){
    _out<<"<parameterList>\n";

    while(_token != ")"){
        writeLine();

        getNextLine("Variable Type is not present", "identifier", "");
        writeLine();

        getNextLine("Illegal termination of declaration: "+_inputLine, "", "");
        
        if(_token == ","){
            writeLine();
            getNextLine("Variable Type is not present", "", "");
        }
    }

    _out<<"</parameterList>\n";
}

/*
    Variable declaration is of the type:
    'var' type varName (',' varName)? ';'

    A loop is run till ';' is found.
    If ',' is found, more variables are present.
*/
void compileAPI::Compile::compileVarDec(){
    _out<<"<varDec>\n";
    writeLine(); // var

    getNextLine("Variable type is not present", "", ""); // type
    writeLine();
        
    while(_token != ";"){
        getNextLine("Variable name is not present", "identifier", "");
        writeLine();

        getNextLine("Illegal termination of declaration: "+_inputLine, "", "");
        
        if(_token == ","){
            writeLine();
        }
    }
    writeLine();
    getNextLine("", "", "");
    _out<<"</varDec>\n";
}

/*
    Statements can be:
    1. *blank*
    2. Let
    3. If
    4. Do
    5. While
    6. Return

    Rest are errors.
*/
void compileAPI::Compile::compileStatements(){
    _out<<"<statements>\n";
    while(1){
        if(_token == "let") compileLet();
        else if(_token == "if") compileIf();
        else if(_token == "do") compileDo();
        else if(_token == "while") compileWhile();
        else if(_token == "return") compileReturn();
        else break;
    }
    _out<<"</statements>\n";
}

/*
    Do statement is of the type:
    'do' subRoutineCall ';'
*/
void compileAPI::Compile::compileDo(){
    _out<<"<doStatement>\n";
    writeLine(); // do

    // start of subroutine call. We fetch the name of subroutine call here and 
    // then pass the rest to compileSubroutineCall().
    getNextLine("Do statement must have an identifier: "+_inputLine, "identifier", "");
    writeLine();

    getNextLine("Subroutine call is incomplete: " + _inputLine, "", "");

    compileSubroutineCall();
    
    if(_token != ";"){
        throw errors::IllegalCallException("Subroutine call must end with ';'");
    }
    writeLine();
    
    getNextLine(""+_inputLine, "", "");
    _out<<"</doStatement>\n";
}

/*
    This is used to complete a sub routine call. These can be:
    
    1. subroutineName '(' expressionList ')'
    2. (className | varName ).subroutineName'('expressionList')'

    Imp: the first identifier should be taken care of before hand. The processing begins from '.' or '('
    
*/
void compileAPI::Compile::compileSubroutineCall(){
    if(_token == "("){ // case 1 
        writeLine();
        getNextLine("", "", "");
        
        compileExpressionList();
        writeLine();
        getNextLine("", "", "");
    }else if (_token == "."){ // case 2
        writeLine();
        getNextLine("Subcall must have an identifier: " + _inputLine, "identifier", "");
        writeLine();
        getNextLine("Expressions must start with '(': " + _inputLine, "", "(");
        compileSubroutineCall();
    }
}

/*
    let statement is of the type:
    'let' varName ('[' expression ']')? '=' expression ';'

    Definition of the variable is mandatory.
    Run until ';' is reached
*/
void compileAPI::Compile::compileLet(){
    _out<<"<letStatement>\n";
    writeLine();

    while(_token != ";"){
        getNextLine("Let should have a variable name: "+_inputLine, "identifier", "");
        writeLine();
        
        getNextLine("Let function is incomplete: "+_inputLine, "", "");
        if(_token == "["){
            writeLine();
            getNextLine("Bracket not closed ']': "+_inputLine, "", "");
                
            if(_token != "]"){
                compileExpression();
            }

            writeLine();
            getNextLine("Bracket not closed ']': "+_inputLine, "", "");
        }

        if(_token != "="){
            throw errors::IllegalCallException("Let should have an initial value: " + _inputLine);
        }
        writeLine();
        
        getNextLine("Let should have an initial value: "+_inputLine, "", "");
        
        compileExpression();

        // example: let a[i] = Keyboard.readInt("ENTER THE NEXT NUMBER: ");
        if(_token == ")"){
            getNextLine("Let should have an initial value: ", "", "");
        }
        
        if(_token == ","){
            writeLine();
        }
    }

    writeLine();
    getNextLine("", "", "");    
    _out<<"</letStatement>\n";
}

/*
    while statement is of the type:
    'while' '(' expression ')' '{' statements '}'

    Run until '}' is reached
*/
void compileAPI::Compile::compileWhile(){
    _out<<"<whileStatement>\n";
    writeLine(); // while

    getNextLine("While should begin with '(': "+_inputLine, "", "(");
    writeLine();
    
    getNextLine("Missing expression for while statement: "+_inputLine, "", "");
    compileExpression();
    
    if(_token != ")"){
        throw errors::IllegalCallException("While initialization should end with ')': " + _inputLine);
    }
    writeLine();

    getNextLine("While body should begin with '{': "+_inputLine, "", "{");
    writeLine();
    
    getNextLine("While body should begin with '{': "+_inputLine, "", "");
    compileStatements();

    if(_token != "}"){
        throw errors::IllegalCallException("While should end with '}': " + _inputLine);
    }
    writeLine();

    getNextLine(""+_inputLine, "", "");
    _out<<"</whileStatement>\n";
}

/*
    return statement is of the type:
    'return'  expression? ';'
    only none or one variable can be returned. 
*/
void compileAPI::Compile::compileReturn(){
    _out<<"<returnStatement>\n";
    writeLine(); // return

    getNextLine("Return missing ';': "+_inputLine, "", "");

    if(_token != ";"){
        compileExpression();
    }

    if(_token != ";"){
        throw errors::IllegalCallException("Return missing ';': " + _inputLine);
    }
    writeLine();
    
    getNextLine(""+_inputLine, "", "");
    _out<<"</returnStatement>\n";
}

/*
    if statement is of the type:
    'if'  '(' expression ')' '{' statements '}'
    ('else' '{' statements '}')? 
*/
void compileAPI::Compile::compileIf(){
    _out<<"<ifStatement>\n";
    writeLine(); // if
    
    getNextLine("If statement should begin with '(': "+_inputLine, "", "(");
    writeLine();
    
    getNextLine("If statement should have an expression: "+_inputLine, "", "");
    compileExpression();
    
    if(_token != ")"){
        throw errors::IllegalCallException("If declaration should end with ')': " + _inputLine);
    }
    writeLine();

    getNextLine("If statement body should begin with '{': "+_inputLine, "", "{");
    writeLine();
    
    getNextLine("If statement should have a body: "+_inputLine, "", "");
    compileStatements();

    if(_token != "}"){
        throw errors::IllegalCallException("If expression body should end with '}': " + _inputLine);
    }
    writeLine();

    getNextLine(""+_inputLine, "", "");
    
    // Else check.
    if(_token == "else"){
        writeLine();

        getNextLine("Else statement body should begin with '{': "+_inputLine, "", "{");
        writeLine();
        
        getNextLine("Else statement should have a body: "+_inputLine, "", "");
        compileStatements();

        if(_token != "}"){
            throw errors::IllegalCallException("Else expression body should end with '}': " + _inputLine);
        }
        writeLine();

        getNextLine(""+_inputLine, "", "");
    }

    _out<<"</ifStatement>\n";
}

/*
    expressions are of the type:
    term (op term)
    at least one term is mandatory. other terms should be preceded by op. 
*/
void compileAPI::Compile::compileExpression(){
    _out<<"<expression>\n";
    compileTerm();
    while(checkTerm()){
        writeLine();
        getNextLine("Term is incomplete: " + _inputLine, "", "");
        
        compileTerm();
    }
    _out<<"</expression>\n";
}

/*
    Term is of the type:
    1. Integer Constant/ String Constant/ Keyboard Constant
    2. unaryOperator term
    3. '(' expression ')'
    4. varName ('[' expression ']')
    5. subroutineCall
*/
void compileAPI::Compile::compileTerm(){
    _out<<"<term>\n";
    
    // case 1
    if(_tokenType == "stringConstant"){    
        writeLine();
        getNextLine("Term is incomplete: " + _inputLine, "", "");
    }else if(_tokenType == "integerConstant"){    
        writeLine();
        getNextLine("Term is incomplete: " + _inputLine, "", "");
    }else if(checkKeyboardConst()){ 
        writeLine();
        getNextLine("Term is incomplete: " + _inputLine, "", "");
    }else if(checkUnaryTerm()){ // case 2
        writeLine();
        getNextLine("Term is incomplete: " + _inputLine, "", "");
        compileTerm();
    }else if(_token == "("){ // case 3
        writeLine();
        getNextLine("Term Expression must end with ')': " + _inputLine, "", "");
        
        compileExpression();
        if(_token != ")"){
            throw errors::IllegalCallException("Expression should end with ')': " + _inputLine);
        }

        writeLine();
        getNextLine("Term is incomplete: " + _inputLine, "", "");
    
    }else{
        // we reach here if an identifier is present. Could be case 4 or 5
        // could be varName or subroutine call. 
        writeLine();
        getNextLine("Term is incomplete: " + _inputLine, "", "");
        
        // subroutineCall
        if(_token == "(" || _token == "."){
            compileSubroutineCall();
        }else if(_token == "["){ // varName
            writeLine();
            getNextLine("Term is incomplete: " + _inputLine, "", "");
            
            compileExpression();
            if(_token != "]"){
                throw errors::IllegalCallException("Expression should end with ']': " + _inputLine);
            }
            
            writeLine();
            getNextLine("Term is incomplete: " + _inputLine, "", "");
        }
    }
    
    _out<<"</term>\n";
}

/*
    ExpressionList is of the type:
    expression (',' expression)?

    looped till ')' is reached.
*/
void compileAPI::Compile::compileExpressionList(){
    _out<<"<expressionList>\n";
    while(_token != ")"){
        compileExpression();
        
        if(_token == ","){
            writeLine();
            getNextLine("Expressions must end with ')': ", "", "");
        }
    }
    _out<<"</expressionList>\n";
}   

