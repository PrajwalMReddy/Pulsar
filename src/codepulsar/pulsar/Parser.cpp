#include "Parser.h"
#include "Lexer.h"


Parser::Parser(string sourceCode) {
    this->sourceCode = sourceCode;

    this->current = 0;
    this->depth = 1;
}

Statement Parser::parse() {
    Lexer* lexer = new Lexer(this->sourceCode);
    this->tokens = lexer->tokenize();
    this->errors = *lexer->getErrors();

    TokenDisassembler::display(this->tokens);
    if (this->errors.hasError()) return this->program;

    return this->program;
}
