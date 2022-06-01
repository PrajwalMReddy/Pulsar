#include "Parser.h"


Pulsar::Parser::Parser(std::string sourceCode) {
    this->sourceCode = sourceCode;

    this->current = 0;
}

Pulsar::Expression* Pulsar::Parser::parse() {
    Pulsar::Lexer lexer = Lexer(this->sourceCode);
    this->tokens = lexer.tokenize();
    this->errors = lexer.getErrors();

    if (this->errors->hasError()) return this->program;
    Pulsar::TokenDisassembler::display(this->tokens);

    this->program = primary();
    return this->program;
}

// TODO Grouping and Variable Accessors
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