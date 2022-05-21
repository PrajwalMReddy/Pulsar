#include "Parser.h"
#include "Lexer.h"


Parser::Parser(string sourceCode) {
    this->sourceCode = sourceCode;

    this->current = 0;
    this->depth = 1;
}

int Parser::parse() {
    Lexer* lexer = new Lexer(this->sourceCode);
    this->tokens = lexer->tokenize();
    this->errors = *lexer->getErrors();

    if (this->errors.hasError()) return this->program;
    TokenDisassembler::display(this->tokens);

    return this->program;
}
