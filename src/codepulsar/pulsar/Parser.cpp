#include "Parser.h"


Pulsar::Parser::Parser(std::string sourceCode) {
    this->sourceCode = sourceCode;
    this->symbolTable = new SymbolTable();

    this->current = 0;
    this->scopeDepth = 0;

    this->currentFunction = "";
}

Pulsar::Statement* Pulsar::Parser::parse() {
    Pulsar::Lexer lexer = Lexer(this->sourceCode);
    this->tokens = lexer.tokenize();
    this->errors = lexer.getErrors();

    if (this->errors->hasError()) return this->program;
    Pulsar::TokenDisassembler::display(this->tokens);

    // TODO Temporary Code To Allow More Than One Top Level Declaration

    int line = peekLine();
    auto* statements = new std::vector<Statement*>;

    while (!match({ TK_EOF })) {
        statements->push_back(declarationStatement());
    }

    this->program = new Block(statements, line);
    return this->program;
}

Pulsar::Statement* Pulsar::Parser::declarationStatement() {
    Statement* decl = declaration();
    if (decl != nullptr) return decl;
    newError("Only Declarations Are Allowed At The Top Level", peekLine());
    return nullptr;
}

Pulsar::Statement* Pulsar::Parser::declaration() {
    if (matchAdvance({ TK_FUN })) {
        return functionDeclaration();
    } else if (matchAdvance({ TK_VAR })) {
        return variableDeclaration(TK_VAR);
    } else if (matchAdvance({ TK_CONST })) {
        return variableDeclaration(TK_CONST);
    }

    return nullptr;
}

Pulsar::Statement* Pulsar::Parser::functionDeclaration() {
    int line = peekLine();
    std::string functionName = advance().literal;
    this->currentFunction = functionName;

    look(TK_LPAR, "An Opening Parenthesis Was Expected Before The Parameter List");
    auto* parameters = new std::vector<Parameter*>;

    int arity = 0;
    if (peekType() != TK_RPAR) {
        do {
            Token parameter = advance();
            PrimitiveType type = PR_ERROR;

            if (!matchAdvance({ TK_COLON })) {
                newError("A Colon Was Expected After The Variable Name", peekLine());
            } else {
                if (!match({ TK_INT_TYPE, TK_DOUBLE_TYPE, TK_CHAR_TYPE, TK_BOOLEAN_TYPE })) {
                    newError("A Datatype Was Expected For The Function's Parameters", peekLine());
                }
                type = checkType(advance());
            }

            arity++;
            this->symbolTable->newLocal(parameter.literal, type, true, false, this->scopeDepth + 1);
            parameters->push_back(new Parameter(parameter.literal, type));
        } while (matchAdvance({ TK_COMMA }));
    }

    look(TK_RPAR, "A Closing Parenthesis Was Expected After The Parameter List");
    if (!matchAdvance({ TK_ARROW })) newError("A Return Datatype For The Function Was Expected", peekLine());

    PrimitiveType type = checkType(advance());
    Block* statements = block();

    if (this->symbolTable->getFunctions().contains(functionName)) {
        newError("Function '" + functionName + "' Already Exists", line);
    }

    auto* functionNode = new Function(functionName, type, parameters, statements, line);
    this->symbolTable->addFunction(functionName, *functionNode, arity, type);
    return functionNode;
}

Pulsar::Statement* Pulsar::Parser::statement() {
    while (!match({ TK_EOF })) {
        Statement* decl = declaration();
        if (decl != nullptr) return decl;

        else if (matchAdvance({ TK_IF })) {
            return ifStatement();
        } else if (matchAdvance({ TK_WHILE })) {
            return whileStatement();
        } else if (matchAdvance({ TK_VAR })) {
            return variableDeclaration(TK_VAR);
        } else if (matchAdvance({ TK_CONST })) {
            return variableDeclaration(TK_CONST);
        } else if (matchAdvance({ TK_PRINT })) {
            return printStatement();
        } else if (matchAdvance({ TK_RETURN })) {
            return returnStatement();
        } else {
            return expressionStatement();
        }
    }

    return nullptr;
}

Pulsar::Statement* Pulsar::Parser::variableDeclaration(TokenType accessType) {
    int line = peekLine();
    Token identifier = advance();

    if (identifier.tokenType != TK_IDENTIFIER) {
        newError("Variable Names Should Be Identifiers", peekLine());
    }

    look(TK_COLON, "Unexpected Token '" + peekLiteral() + "' After Variable Name");
    PrimitiveType type = checkType(advance());

    Expression* expr = nullptr;
    bool isInitialized = false;

    if (matchAdvance({ TK_EQUAL })) {
        expr = expression();
        isInitialized = true;
    }

    look(TK_SEMICOLON, "A Semicolon Was Expected After The Variable Declaration");

    if (isInGlobalScope()) {
        if (this->symbolTable->containsGlobalVariable(identifier.literal)) {
            newError("Global Variable '" + identifier.literal + "' Already Exists", identifier.line);
        } this->symbolTable->addGlobalVariable(identifier.literal, nullptr, type, isInitialized, (accessType == TK_CONST));
    } else {
        if (this->symbolTable->containsLocalVariable(identifier.literal)) {
            newError("Local Variable '" + identifier.literal + "' Already Exists", identifier.line);
        } this->symbolTable->newLocal(identifier.literal, type, isInitialized, (accessType == TK_CONST), this->scopeDepth);
    }

    return new VariableDecl(identifier, expr, type, accessType, isInGlobalScope(), line);
}

void Pulsar::Parser::startScope() {
    this->scopeDepth++;
}

Pulsar::Block* Pulsar::Parser::block() {
    auto* statements = new std::vector<Statement*>;
    startScope();
    look(TK_LBRACE, "An Opening Brace Was Expected Before The Block");

    while (!match({ TK_RBRACE }) && !match({ TK_EOF })) {
        statements->push_back(statement());
    }

    look(TK_RBRACE, "A Closing Brace Was Expected After The Block");
    endScope();
    return new Block(statements, peekLine());
}

void Pulsar::Parser::endScope() {
    this->scopeDepth--;
}

Pulsar::Statement* Pulsar::Parser::ifStatement() {
    int line = peekLine();
    Expression* expr = expression();
    Block* thenBranch = block();
    Statement* elseBranch = nullptr;

    if (matchAdvance({ TK_ELSE })) {
        if (matchAdvance({ TK_IF })) {
            elseBranch = ifStatement();
        } else {
            elseBranch = block();
        }
    }

    return new If(expr, thenBranch, elseBranch, line);
}

Pulsar::Statement* Pulsar::Parser::whileStatement() {
    int line = peekLine();
    Expression* expr = expression();
    Block* statements = block();

    return new While(expr, statements, line);
}

Pulsar::Statement* Pulsar::Parser::printStatement() {
    Print* statement = new Print(expression(), peekLine());
    look(TK_SEMICOLON, "A Semicolon Was Expected After The Print Statement");
    return statement;
}

Pulsar::Statement* Pulsar::Parser::returnStatement() {
    Return* statement;
    if (match({ TK_SEMICOLON })) {
        statement = new Return(nullptr, this->currentFunction, peekLine());
    } else {
        statement = new Return(expression(), this->currentFunction, peekLine());
    }

    look(TK_SEMICOLON, "A Semicolon Was Expected After The Return Statement");
    return statement;
}

Pulsar::Statement* Pulsar::Parser::expressionStatement() {
    ExpressionStmt* expr = new ExpressionStmt(expression(), peekLine());
    look(TK_SEMICOLON, "A Semicolon Was Expected After The Expression");
    return expr;
}

Pulsar::Expression* Pulsar::Parser::expression() {
    return assignment();
}

Pulsar::Expression* Pulsar::Parser::assignment() {
    if (peekType() != TK_IDENTIFIER) return logicalOr();

    Token variable = peek();
    if (peekNext().tokenType == TK_EQUAL) {
        advance(); advance();
        return new Assignment(variable.literal, expression(), resolveLocal(variable), resolveLocal(variable) == -1, peekLine());
    } else if (peekNext().tokenType == TK_PLUS_EQUAL || peekNext().tokenType == TK_MINUS_EQUAL || peekNext().tokenType == TK_MUL_EQUAL || peekNext().tokenType == TK_DIV_EQUAL || peekNext().tokenType == TK_MOD_EQUAL) {
        std::string identifier = variable.literal;
        int line = variable.line;
        advance();

        std::string operatorType = peek().literal;
        advance();
        Expression *expr = expression();

        // Expanding The Syntactic Sugar Into A Normal Assignment
        return new Assignment(identifier, new Binary(new VariableExpr(identifier, resolveLocal(variable), resolveLocal(variable) == -1, line), operatorType.substr(0, 1), expr, line), resolveLocal(variable), resolveLocal(variable) == -1, line);
    } else {
        return logicalOr();
    }
}

Pulsar::Expression* Pulsar::Parser::logicalOr() {
    Expression* expression = logicalAnd();

    while (matchAdvance({ TK_LOGICAL_OR })) {
        Token operatorType = previous();
        Expression* right = logicalAnd();
        expression = new Logical(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::logicalAnd() {
    Expression* expression = equality();

    while (matchAdvance({ TK_LOGICAL_AND })) {
        Token operatorType = previous();
        Expression* right = equality();
        expression = new Logical(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::equality() {
    Expression* expression = comparison();

    while (matchAdvance({ TK_EQUAL_EQUAL, TK_NOT_EQUAL })) {
        Token operatorType = previous();
        Expression* right = comparison();
        expression = new Binary(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::comparison() {
    Expression* expression = term();

    while (matchAdvance({ TK_GT, TK_GT_EQUAL, TK_LT, TK_LT_EQUAL })) {
        Token operatorType = previous();
        Expression* right = term();
        expression = new Binary(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::term() {
    Expression* expression = factor();

    while (matchAdvance({ TK_PLUS, TK_MINUS })) {
        Token operatorType = previous();
        Expression* right = factor();
        expression = new Binary(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::factor() {
    Expression* expression = unary();

    while (matchAdvance({ TK_MULTIPLICATION, TK_DIVISION, TK_MODULUS })) {
        Token operatorType = previous();
        Expression* right = unary();
        expression = new Binary(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::unary() {
    if (matchAdvance({ TK_NOT, TK_MINUS })) {
        Token operatorType = previous();
        Expression* right = unary();
        return new Unary(operatorType.literal, right, operatorType.line);
    } else if (matchAdvance({ TK_PLUS })) {
        return unary();
    }

    return call();
}

// TODO Disallow 'Nested' Calls For Now
Pulsar::Expression* Pulsar::Parser::call() {
    Token name = peek();
    Expression* expr = primary();

    if (matchAdvance({ TK_LPAR })) {
        auto* arguments = new std::vector<Expression*>;

        if (!match({ TK_RPAR })) {
            do {
                arguments->push_back(expression());
            } while (matchAdvance({ TK_COMMA }));
        }

        look(TK_RPAR, "A Closing Parenthesis Is Required After A Call Expression");
        return new Call(name, arguments);
    }

    return expr;
}

Pulsar::Expression* Pulsar::Parser::primary() {
    if (matchAdvance({ TK_TRUE })) {
        return new Literal("true", PR_BOOLEAN, peekLine());
    } else if (matchAdvance({ TK_FALSE })) {
        return new Literal("false", PR_BOOLEAN, peekLine());
    }

    if (matchAdvance({ TK_INTEGER })) {
        return new Literal(previous().literal, PR_INTEGER, peekLine());
    } else if (matchAdvance({ TK_DOUBLE })) {
        return new Literal(previous().literal, PR_DOUBLE, peekLine());
    } else if (matchAdvance({ TK_CHARACTER })) {
        return new Literal(previous().literal, PR_CHARACTER, peekLine());
    }

    if (match({ TK_IDENTIFIER })) {
        Token name = advance();
        return new VariableExpr(name.literal, resolveLocal(name), resolveLocal(name) == -1, peekLine());
    }

    if (matchAdvance({ TK_LPAR })) {
        Expression* expr = expression();
        look(TK_RPAR, "A Closing Parenthesis Was Expected");
        return new Grouping(expr, peekLine());
    }

    newError("An Expression Was Expected But Nothing Was Given", peekLine());
    return new Literal("", PR_ERROR, peekLine());
}

bool Pulsar::Parser::match(std::vector<TokenType> types) {
    for (TokenType type: types) {
        if (peekType() == type) {
            return true;
        }
    }

    return false;
}

bool Pulsar::Parser::matchAdvance(std::vector<TokenType> types) {
    for (TokenType type: types) {
        if (peekType() == type) {
            advance();
            return true;
        }
    }

    return false;
}

Pulsar::Token Pulsar::Parser::advance() {
    this->current++;
    return this->tokens[this->current - 1];
}

bool Pulsar::Parser::look(TokenType token, std::string message) {
    if (peekType() != token) {
        newError(message, peekLine());
        synchronize();
        return true;
    } else {
        advance();
        return false;
    }
}

void Pulsar::Parser::synchronize() {
    while (peekType() != TK_EOF) {
        if (peekType() == TK_SEMICOLON) return;

        switch (peekType()) {
            case TK_IF:
            case TK_WHILE:
            case TK_VAR:
            case TK_CONST:
            case TK_PRINT:
            case TK_RETURN:
                return;
        }

        advance();
    }
}

Pulsar::Token Pulsar::Parser::previous() {
    return this->tokens[this->current - 1];
}

bool Pulsar::Parser::isInGlobalScope() {
    return this->scopeDepth == 0;
}

int Pulsar::Parser::resolveLocal(Token name) {
    for (int i = this->symbolTable->getLocalCount() - 1; i >= 0; i--) {
        LocalVariable local = this->symbolTable->localAt(i);

        if (local.getName() == name.literal) {
            return i;
        }
    }

    return -1;
}

Pulsar::PrimitiveType Pulsar::Parser::checkType(Token type) {
    std::string typeLiteral = type.literal;

    if (typeLiteral == "boolean") return PR_BOOLEAN;
    else if (typeLiteral == "char") return PR_CHARACTER;
    else if (typeLiteral == "double") return PR_DOUBLE;
    else if (typeLiteral == "int") return PR_INTEGER;
    else if (typeLiteral == "void") return PR_VOID;
    else return PR_ERROR;
}

Pulsar::Token Pulsar::Parser::peek() {
    return this->tokens[this->current];
}

Pulsar::Token Pulsar::Parser::peekNext() {
    return this->tokens[this->current + 1];
}

Pulsar::TokenType Pulsar::Parser::peekType() {
    return this->tokens[this->current].tokenType;
}

std::string Pulsar::Parser::peekLiteral() {
    return this->tokens[this->current].literal;
}

int Pulsar::Parser::peekLine() {
    return this->tokens[this->current].line;
}

void Pulsar::Parser::newError(std::string message, int line) {
    this->errors->addError("Parsing Error", message, line);
}

Pulsar::SymbolTable* Pulsar::Parser::getSymbolTable() {
    return this->symbolTable;
}

Pulsar::CompilerError* Pulsar::Parser::getErrors() {
    return this->errors;
}
