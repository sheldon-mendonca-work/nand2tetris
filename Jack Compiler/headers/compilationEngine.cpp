#include"./compilationEngine.hpp"

/**
    Imp:
    1. writeLine() and writeCmd() are debugging commands.
       Although it can be deleted, it's retained for now.
*/

/*
    Checks if string is a part of keyboardConstant[] = {"true", "false", "null", "this"};
*/
bool compileAPI::Compile::checkKeyboardConst(const std::string &token){
    for(std::string &s:keywordConstant){
        if(s == token) return true;
    }
    return false;
}

/*
    Checks if string is a part of unaryTerm[] = {"~", "-"}
*/
bool compileAPI::Compile::checkUnaryTerm(const std::string &token){
    for(std::string &s:unaryTerm){
        if(s == token) return true;
    }
    return false;
}

/*
    Checks if string is a part of term[] = {"+", "-", "*", "/", "&amp;", "|", "&lt;", "&gt;", "="}
*/
bool compileAPI::Compile::checkTerm(const std::string &token){
    for(std::string &s:term){
        if(s == token) return true;
    }
    return false;
}

void compileAPI::Compile::addToken(const std::string &t){
    if(_tokenList.size() == _curr){
        _tokenList.push_back(t);
    }else{
        _tokenList[_curr] = t;
    }

    _curr++;
}

/*
    Gets the input line from tokenizer.
    Takes 3 arguments:
    1. Error message to be shown if no line is received.
    2. tokenType matches the input line.
    3. token matches the input token
*/
void compileAPI::Compile::getNextLine(const std::string &errMsg, const std::string &tokenType, const std::string &token){
    if(_tokenizer.hasMoreTokens()){
        _tokenizer.advance();              
    }else{
        throw errors::IllegalCallException("Cannot get new line");
    }
    
    _tokenType = _tokenizer.tokenType();
    _token = _tokenizer.token();

    if(tokenType.length() > 0 && tokenType != _tokenType){
        throw errors::IllegalCallException("Invalid token type." + tokenType + ". Token."+_token+", tokenType."+_tokenType);
    }

    if(token.length() > 0 && token != _token){
        throw errors::IllegalCallException("Invalid token ." + token + ". Token."+_token+", tokenType."+_tokenType);
    }
}

/*
    Writes a line to output file
*/
void compileAPI::Compile::writeLine(){
    _writer.writeCmd("<"+_tokenType+">"+_token+"</"+_tokenType+">\n");
}

/*
    Start of compilation. <tokens>  and </tokens> are skipped.
*/
void compileAPI::Compile::compileTokens(){
    getNextLine("", "", "");
    compileClass();
} 

/*
    Compiles a class. Grammar is of the type:
    'class' className '{' classVarDec* subroutineDec* '}'
*/
void compileAPI::Compile::compileClass(){
    _writer.writeCmd("<class>\n");
    _kind = "class"; _type="";
    writeLine(); // class

    getNextLine("Identifier should be present after class.", "identifier", ""); //className
    writeLine();
    _className = _token;
    
    getNextLine("Missing '{.", "", "{"); // '{'    
    writeLine();
    addToken(_token);
    
    // run till all declarations and routines are completed. Class is terminated by '}'
    getNextLine("Class is not completed.", "", "");
    while(1){
        
        if(_tokenType == "keyword"){
            if(_token == "static" || _token == "field"){
                compileClassVarDec();
            }else if(_token == "constructor" || _token == "function" || _token == "method"){
                compileSubroutine();
            }else{
                throw errors::IllegalCallException("Class should have functions or fields.");
            }
        }else if(_token == "}"){
            writeLine();
            break;
        }else{
            throw errors::IllegalCallException("Class definition must begin with a keyword.");
        }
    }
    _writer.writeCmd("</class>\n");
}

/*
    class variable declarations are of the form:
    ('static' | 'field') type varName (',' varName)';'
    We run a loop till we reach ';' or the end of file.
    If we observe a ',' the loop is continued;
*/
void compileAPI::Compile::compileClassVarDec(){
    
    _writer.writeCmd("<classVarDec>\n");
    writeLine(); // static | field
    _kind = _token;
    
    getNextLine("Variable type is undefined.", "", ""); // type
    writeLine();
    _type = _token;

    while(_token != ";"){
        getNextLine("Variable is not present", "identifier", ""); // varName
        writeLine();
        _sym.define(_token, _type, _kind);

        getNextLine("Illegal termination of declaration.", "", ""); // next varName | ','  | ';'
        
        if(_token == ",") writeLine();
    }

    writeLine();
    getNextLine("", "", "");
    _writer.writeCmd("</classVarDec>\n");
}

/*
    subroutine is of the type:
    ('constructor' | 'function' | 'method') ('void' | type) subroutineName '(' parameterList ')' subroutineBody
*/
// done
void compileAPI::Compile::compileSubroutine(){
    _writer.writeCmd("<subroutineDec>\n");
    writeLine(); //'constructor' | 'function' | 'method'
    addToken(_token);
    
    getNextLine("Function type is undefined.", "", ""); // 'void' | type
    writeLine();
    _type = _token;
    addToken(_type);

    getNextLine("Function name is not present", "identifier", ""); // subroutineName 
    writeLine();
    addToken(_className + "." + _token);
    
    getNextLine("Bracket '(' is missing.", "", "(");
    writeLine();
    addToken(_token);
    _sym.startSubroutine();

    if(_tokenList[_curr-4] == "method"){
        _sym.define("this", _className, "argument");
    }

    getNextLine("Bracket ')' is missing.", "", ""); // parameterList | ')'
    
    compileParameterList();

    if(_token != ")"){
        throw errors::IllegalCallException("Bracket ')' is missing.");
    }
    writeLine();
    
    // subroutine body handling
    getNextLine("Sub routine body must start with '{'.", "", "{");
    
    _writer.writeCmd("<subroutineBody>\n");
    writeLine();
    addToken(_token);

    if(_token != "}"){
        getNextLine("Sub routine body should have statement or variables.", "", "");
        
        while(_token == "var"){
            compileVarDec();
        }
        
        _writer.writeFunction(_tokenList[_curr-2], std::to_string(_sym.varCount("var")));

        if(_tokenList[_curr-4] == "constructor"){
            _writer.writePush("constant", std::to_string(_sym.varCount("field")));
            _writer.writeCall("Memory.alloc", "1");
            _writer.writePop("pointer", "0");
        }else if(_tokenList[_curr-4] == "method"){
            _writer.writePush("arg", "0");
            _writer.writePop("pointer", "0");
        }

        while(_token == "let" || _token == "if" || _token == "while" || _token == "do" || _token == "return"){
            compileStatements();
        }
    }

    if(_token != "}"){
        throw errors::IllegalCallException("Sub routine body must end with '}'.");
    }

    _curr -= 4;
    writeLine();
    getNextLine("", "", "");
    _writer.writeCmd("</subroutineBody>\n");
    _writer.writeCmd("</subroutineDec>\n");
}

/*
    Parameter list is of the type:
    ((type varName) (',' type varName)?) | null

    A loop is run till ')' is found.
*/
// done
void compileAPI::Compile::compileParameterList(){
    _writer.writeCmd("<parameterList>\n");
    _kind = "argument";
    _type = _token;

    while(_token != ")"){
        writeLine();

        getNextLine("Variable Type is not present", "identifier", "");
        _sym.define(_token, _type, _kind);
        
        writeLine();

        getNextLine("Illegal termination of declaration.", "", "");
        
        if(_token == ","){
            writeLine();
            getNextLine("Variable Type is not present", "", "");
        }
    }

    while(_tokenList[--_curr] != "("){}
    _writer.writeCmd("</parameterList>\n");
}

/*
    Variable declaration is of the type:
    'var' type varName (',' varName)? ';'

    A loop is run till ';' is found.
    If ',' is found, more variables are present.
*/
//done
void compileAPI::Compile::compileVarDec(){
    _writer.writeCmd("<varDec>\n");
    writeLine(); // var
    _kind = "var";

    getNextLine("Variable type is not present", "", ""); // type
    writeLine();
    _type = _token;
        
    while(_token != ";"){
        getNextLine("Variable name is not present", "identifier", "");
        _sym.define(_token, _type, _kind);
        writeLine();

        getNextLine("Illegal termination of declaration.", "", ""); // "," | ";"
        
        if(_token == ","){
            writeLine();
        }
    }
    writeLine();

    getNextLine("", "", "");
    _writer.writeCmd("</varDec>\n");
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
//done
void compileAPI::Compile::compileStatements(){
    _writer.writeCmd("<statements>\n");
    
    while(1){
        if(_token == "let") compileLet();
        else if(_token == "if") compileIf();
        else if(_token == "do") compileDo();
        else if(_token == "while") compileWhile();
        else if(_token == "return") compileReturn();
        else break;
    }
    _writer.writeCmd("</statements>\n");
}

/*
    Do statement is of the type:
    'do' subRoutineCall ';'
*/
void compileAPI::Compile::compileDo(){
    _writer.writeCmd("<doStatement>\n");
    writeLine(); // do
    addToken(_token);

    // start of subroutine call. We fetch the name of subroutine call here and 
    // then pass the rest to compileSubroutineCall().
    getNextLine("Do statement must have an identifier.", "identifier", "");
    writeLine();
    addToken(_token);

    getNextLine("Subroutine call is incomplete:.", "", "");

    _argCount = 0;
    compileSubroutineCall();
    
    if(_token != ";"){
        throw errors::IllegalCallException("Subroutine call must end with ';'");
    }
    writeLine();
    
    // _writer.writeCall(_tokenList[--_curr], std::to_string(_argCount));
    _writer.writePop("temp", "0");
    _curr -= 2;
    getNextLine("", "", "");
    _writer.writeCmd("</doStatement>\n");
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
        if(_tokenList[_curr-1].find('.') == std::string::npos){
            _writer.writePush("pointer", "0");
            _tokenList[_curr-1] = _className + "." + _tokenList[_curr-1];
            _argCount++;
        }
        addToken(_token);

        getNextLine("", "", "");
        
        compileExpressionList();

        while(_tokenList[--_curr] != "("){}
        
        if(_token != ")"){
            throw errors::IllegalCallException("Subroutine call should end with ')'");
        }
        
        _writer.writeCall(_tokenList[_curr-1], std::to_string(_argCount));
        writeLine();
        getNextLine("", "", "");
    }else if (_token == "."){ // case 2
        writeLine();
        // a.b() is written as Object.b(a)
        std::string kind = _sym.kindOf(_tokenList[_curr-1]), type = _sym.typeOf(_tokenList[_curr-1]);
        if(kind != "NONE"){
            _writer.writePush(kind, std::to_string(_sym.indexOf(_tokenList[_curr-1])));
            _tokenList[_curr-1] = type;
            _argCount++;
        }
        _tokenList[_curr-1] += _token;

        getNextLine("Subcall must have an identifier:.", "identifier", "");
        writeLine();
        _tokenList[_curr-1] += _token;

        getNextLine("Expressions must start with '(':.", "", "(");
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
    _writer.writeCmd("<letStatement>\n");
    writeLine();

    while(_token != ";"){
        getNextLine("Let should have a variable name.", "identifier", "");
        writeLine();
        addToken(_token);
        
        getNextLine("Let function is incomplete.", "", "");
        if(_token == "["){
            writeLine();
            addToken(_token);
            getNextLine("Bracket not closed ']'.", "", "");
                
            if(_token != "]"){
                compileExpression();
            }
            
            while(_tokenList[--_curr] != "["){};
            
            _curr--;
            _writer.writePush(_sym.kindOf(_tokenList[_curr]), std::to_string(_sym.indexOf(_tokenList[_curr])) );
            _writer.writeArithmetic("+");
            addToken("pointer");
            writeLine();
            getNextLine("Bracket not closed ']'.", "", "");
        }

        if(_token != "="){
            throw errors::IllegalCallException("Let should have an initial value:.");
        }
        writeLine();
        _argCount = 0;
        
        getNextLine("Let should have an initial value.", "", "");
        
        compileExpression();

        // example: let a[i] = Keyboard.readInt("ENTER THE NEXT NUMBER.");
        if(_token == ")"){
            getNextLine("Let should have an initial value.", "", "");
        }
        
        if(_token == ","){
            writeLine();
        }
    
        _curr -= 2;
        if(_tokenList[_curr] == "pointer"){
            _writer.writePop("temp", "0");
            _writer.writePop("pointer", "1");
            _writer.writePush("temp", "0");
            _writer.writePop("that", "0");
        }else{
            _writer.writePop(_sym.kindOf(_tokenList[_curr]), std::to_string(_sym.indexOf(_tokenList[_curr])) );
        }
    }

    writeLine();
    getNextLine("", "", "");    
    _writer.writeCmd("</letStatement>\n");
}

/*
    while statement is of the type:
    'while' '(' expression ')' '{' statements '}'

    Run until '}' is reached
*/
void compileAPI::Compile::compileWhile(){
    _writer.writeCmd("<whileStatement>\n");
    writeLine(); // while
    int lc = ++_labelCount;
    _writer.writeLabel("WHILE_START_" + std::to_string(lc));

    getNextLine("While should begin with '('.", "", "(");
    writeLine();
    addToken(_token);
    
    getNextLine("Missing expression for while statement.", "", "");
    compileExpression();
    
    if(_token != ")"){
        throw errors::IllegalCallException("While initialization should end with ')':.");
    }
    writeLine();
    _writer.writeArithmetic("~");
    _writer.writeIf("WHILE_END_" + std::to_string(lc));

    getNextLine("While body should begin with '{'.", "", "{");
    writeLine();
    
    getNextLine("While body should begin with '{'.", "", "");
    compileStatements();
    _writer.writeGoto("WHILE_START_" + std::to_string(lc));

    if(_token != "}"){
        throw errors::IllegalCallException("While should end with '}':.");
    }
    writeLine();

    _writer.writeLabel("WHILE_END_" + std::to_string(lc));

    getNextLine("", "", "");
    _curr -= 2;
    _writer.writeCmd("</whileStatement>\n");
}

/*
    return statement is of the type:
    'return'  expression? ';'
    only none or one variable can be returned. 
*/
void compileAPI::Compile::compileReturn(){
    _writer.writeCmd("<returnStatement>\n");
    writeLine(); // return
    addToken(_token);

    getNextLine("Return missing ';'.", "", "");

    if(_token != ";"){
        compileExpression();
    }

    if(_token != ";"){
        throw errors::IllegalCallException("Return missing ';':.");
    }
    writeLine();

    if(_tokenList[_curr-1] == "return"){
        _writer.writePush("constant", "0");
    }

    _writer.writeReturn();
    getNextLine("", "", "");
    _curr--;
    _writer.writeCmd("</returnStatement>\n");
}

/*
    if statement is of the type:
    'if'  '(' expression ')' '{' statements '}'
    ('else' '{' statements '}')? 
*/
void compileAPI::Compile::compileIf(){
    _writer.writeCmd("<ifStatement>\n");
    writeLine(); // if
    
    getNextLine("If statement should begin with '('.", "", "(");
    writeLine();
    
    getNextLine("If statement should have an expression.", "", "");
    compileExpression();
    
    if(_token != ")"){
        throw errors::IllegalCallException("If declaration should end with ')':.");
    }
    writeLine();

    int lc = ++_labelCount;
    _writer.writeIf("IF_TRUE_" + std::to_string(lc));
    _writer.writeGoto("ELSE_TRUE_" + std::to_string(lc));
    
    _writer.writeLabel("IF_TRUE_" + std::to_string(lc));

    getNextLine("If statement body should begin with '{'.", "", "{");
    writeLine();
    
    getNextLine("If statement should have a body.", "", "");
    compileStatements();

    if(_token != "}"){
        throw errors::IllegalCallException("If expression body should end with '}':.");
    }
    writeLine();

    getNextLine("", "", "");
    _writer.writeGoto("ELSE_END_" + std::to_string(lc));
    _writer.writeLabel("ELSE_TRUE_" + std::to_string(lc));
    
    // Else check.
    if(_token == "else"){
        writeLine();

        getNextLine("Else statement body should begin with '{'.", "", "{");
        writeLine();
        
        getNextLine("Else statement should have a body.", "", "");
        compileStatements();

        if(_token != "}"){
            throw errors::IllegalCallException("Else expression body should end with '}':.");
        }
        writeLine();

        getNextLine("", "", "");
    }
    _writer.writeLabel("ELSE_END_" + std::to_string(lc));

    _writer.writeCmd("</ifStatement>\n");
}

/*
    expressions are of the type:
    term (op term)
    at least one term is mandatory. other terms should be preceded by op. 
*/
void compileAPI::Compile::compileExpression(){
    _writer.writeCmd("<expression>\n");
    
    compileTerm();
    while(checkTerm(_token)){
        writeLine();
        addToken(_token);

        getNextLine("Term is incomplete:.", "", "");
        
        compileTerm();
        _curr -= 2;
        _writer.writeArithmetic(_tokenList[_curr]);
    }

    _writer.writeCmd("</expression>\n");
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
    _writer.writeCmd("<term>\n");

     // case 1
    if(_tokenType == "stringConstant"){
        writeLine();
        _writer.writePush("constant", std::to_string(_token.length()));
        _writer.writeCall("String.new", "1");

        for(char c:_token){
            _writer.writePush("constant", std::to_string((int)c));
            _writer.writeCall("String.appendChar", "2");
        }

        getNextLine("Term is incomplete:.", "", "");
    }else if(_tokenType == "integerConstant"){
        writeLine();
        addToken(_token);
        _writer.writePush("constant", _token);

        getNextLine("Term is incomplete:.", "", "");
    }else if(checkKeyboardConst(_token)){
        writeLine();
        addToken(_token);

        if(_token == "this"){
            _writer.writePush("pointer", "0");
        }else if(_token == "null"){
            _writer.writePush("constant", "0");
        }else{
            _writer.writePush("constant", "0");
            if(_token == "true"){
                _writer.writeArithmetic("~");
            }
        }

        getNextLine("Term is incomplete:.", "", "");
    }else if(checkUnaryTerm(_token)){ // case 2
        writeLine();
        if(_token == "-"){
            addToken("neg");
        }else{
            addToken(_token);
        }
        
        getNextLine("Term is incomplete:.", "", "");
        compileTerm();
        
        --_curr;
        _writer.writeArithmetic(_tokenList[_curr-1]);
    }else if(_token == "("){ // case 3
        writeLine();
        addToken(_token);
        
        getNextLine("Term Expression must end with ')':.", "", "");
        
        compileExpression();

        if(_token != ")"){
            throw errors::IllegalCallException("Expression should end with ')':.");
        }
        while(_tokenList[--_curr] != "("){}
        addToken(" ");
        writeLine();
        getNextLine("Term is incomplete:.", "", "");
    
    }else{
        addToken(_token);
        writeLine();
        // we reach here if an identifier is present. Could be case 4 or 5
        // could be varName or subroutine call. 
        getNextLine("Term is incomplete:.", "", "");
        
        // subroutineCall
        if(_token == "(" || _token == "."){
            compileSubroutineCall();
        }else if(_token == "["){ 
            addToken(_token);
            writeLine();
            getNextLine("Term is incomplete:.", "", "");
            
            compileExpression();
            if(_token != "]"){
                throw errors::IllegalCallException("Expression should end with ']'.");
            }
            
            while(_tokenList[--_curr] != "["){}
            --_curr;
            _writer.writePush(_sym.kindOf(_tokenList[_curr]), std::to_string(_sym.indexOf(_tokenList[_curr])) );
            
            _writer.writeArithmetic("+");
            _writer.writePop("pointer", "1");
            _writer.writePush("that", "0");
            addToken("pointer");
            
            writeLine();
            getNextLine("Term is incomplete:.", "", "");
        }else{
            _writer.writePush(_sym.kindOf(_tokenList[_curr-1]), std::to_string(_sym.indexOf(_tokenList[_curr-1])) );
        }
    }
    
    _writer.writeCmd("</term>\n");
}

/*
    ExpressionList is of the type:
    expression (',' expression)?

    looped till ')' is reached.
*/
void compileAPI::Compile::compileExpressionList(){
    _writer.writeCmd("<expressionList>\n");
    
    while(_token != ")"){
        _argCount++;
        compileExpression();
        
        if(_token == ","){
            writeLine();
            getNextLine("Expressions must end with ')'.", "", "");
        }
    }
    
    _writer.writeCmd("</expressionList>\n");
}   

