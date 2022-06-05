#include "Parser.h"


Pulsar::Parser::Parser(std::string sourceCode) {
    this->sourceCode = sourceCode;

    this->current = 0;
}

Pulsar::Statement* Pulsar::Parser::parse() {
    Pulsar::Lexer lexer = Lexer(this->sourceCode);
    this->tokens = lexer.tokenize();
    this->errors = lexer.getErrors();

    if (this->errors->hasError()) return this->program;
    Pulsar::TokenDisassembler::display(this->tokens);

    this->program = statement();
    return this->program;
}

Pulsar::Statement* Pulsar::Parser::statement() {
    while (!match(TK_EOF)) {
        if (matchAdvance(TK_IF)) {
            return ifStatement();
        } else {
            return expressionStatement();
        }
    }

    return nullptr;
}

// TODO startScope() and endScope()
Pulsar::Block* Pulsar::Parser::block() {
    auto* statements = new std::vector<Statement*>;
    look(TK_LBRACE, "An Opening Brace Was Expected Before The Block");

    while (!match(TK_RBRACE) && !match(TK_EOF)) {
        statements->push_back(statement());
    }

    look(TK_RBRACE, "A Closing Brace Was Expected After The Block");
    return new Block(statements, peekLine());
}

Pulsar::Statement* Pulsar::Parser::ifStatement() {
    int line = peekLine();
    Expression* expr = expression();
    Block* thenBranch = block();
    Statement* elseBranch = nullptr;

    if (matchAdvance(TK_ELSE)) {
        if (matchAdvance(TK_IF)) {
            elseBranch = ifStatement();
        } else {
            elseBranch = block();
        }
    }

    return new If(expr, thenBranch, elseBranch, line);
}

Pulsar::Statement* Pulsar::Parser::expressionStatement() {
    ExpressionStmt* expr = new ExpressionStmt(expression(), peekLine());
    look(TK_SEMICOLON, "A Semicolon Was Expected After The Expression");
    return expr;
}

Pulsar::Expression* Pulsar::Parser::expression() {
    return assignment();
}

// TODO Finish assignment()
Pulsar::Expression* Pulsar::Parser::assignment() {
    logicalOr();
}

Pulsar::Expression* Pulsar::Parser::logicalOr() {
    Expression* expression = logicalAnd();

    while (matchAdvance(TK_LOGICAL_OR)) {
        Token operatorType = previous();
        Expression* right = logicalAnd();
        expression = new Logical(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::logicalAnd() {
    Expression* expression = equality();

    while (matchAdvance(TK_LOGICAL_AND)) {
        Token operatorType = previous();
        Expression* right = equality();
        expression = new Logical(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::equality() {
    Expression* expression = comparison();

    while (matchAdvance(TK_EQUAL_EQUAL) || matchAdvance(TK_NOT_EQUAL)) {
        Token operatorType = previous();
        Expression* right = comparison();
        expression = new Binary(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::comparison() {
    Expression* expression = term();

    while (matchAdvance(TK_GT) || matchAdvance(TK_GT_EQUAL) || matchAdvance(TK_LT) || matchAdvance(TK_LT_EQUAL)) {
        Token operatorType = previous();
        Expression* right = term();
        expression = new Binary(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::term() {
    Expression* expression = factor();

    while (matchAdvance(TK_PLUS) || matchAdvance(TK_MINUS)) {
        Token operatorType = previous();
        Expression* right = factor();
        expression = new Binary(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::factor() {
    Expression* expression = unary();

    while (matchAdvance(TK_MULTIPLICATION) || matchAdvance(TK_DIVISION) || matchAdvance(TK_MODULUS)) {
        Token operatorType = previous();
        Expression* right = unary();
        expression = new Binary(expression, operatorType.literal, right, operatorType.line);
    }

    return expression;
}

Pulsar::Expression* Pulsar::Parser::unary() {
    if (matchAdvance(TK_NOT) || matchAdvance(TK_MINUS)) {
        Token operatorType = previous();
        Expression* right = unary();
        return new Unary(operatorType.literal, right, operatorType.line);
    } else if (matchAdvance(TK_PLUS)) {
        return unary();
    }

    return call();
}

// TODO Disallow 'Nested' Calls For Now
Pulsar::Expression* Pulsar::Parser::call() {
    Token name = peek();
    Expression* expr = primary();

    if (matchAdvance(TK_LPAR)) {
        auto* arguments = new std::vector<Expression*>;

        if (!match(TK_RPAR)) {
            do {
                arguments->push_back(expression());
            } while (matchAdvance(TK_COMMA));
        }

        look(TK_RPAR, "A Closing Parenthesis Is Required After A Call Expression");
        return new Call(name, arguments);
    }

    return expr;
}

// TODO Variable Accessors
Pulsar::Expression* Pulsar::Parser::primary() {
    if (matchAdvance(TK_TRUE)) {
        return new Literal("true", PR_BOOLEAN, peekLine());
    } else if (matchAdvance(TK_FALSE)) {
        return new Literal("false", PR_BOOLEAN, peekLine());
    }

    if (matchAdvance(TK_INTEGER)) {
        return new Literal(previous().literal, PR_INTEGER, peekLine());
    } else if (matchAdvance(TK_DOUBLE)) {
        return new Literal(previous().literal, PR_DOUBLE, peekLine());
    } else if (matchAdvance(TK_CHARACTER)) {
        return new Literal(previous().literal, PR_CHARACTER, peekLine());
    }

    if (matchAdvance(TK_LPAR)) {
        Expression* expr = expression();
        look(TK_RPAR, "A Closing Parenthesis Was Expected");
        return new Grouping(expr, peekLine());
    }

    newError("An Expression Was Expected But Nothing Was Given", peekLine());
    return new Literal("", PR_ERROR, peekLine());
}

bool Pulsar::Parser::match(TokenType type) {
    if (peekType() == type) return true;
    return false;
}

bool Pulsar::Parser::matchAdvance(TokenType type) {
    if (peekType() == type) {
        advance();
        return true;
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
        // TODO synchronize();
        return true;
    } else {
        advance();
        return false;
    }
}

Pulsar::Token Pulsar::Parser::previous() {
    return this->tokens[this->current - 1];
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

Pulsar::CompilerError* Pulsar::Parser::getErrors() {
    return this->errors;
}
