#include "Parser.h"
#include "Lexer.h"


Parser::Parser(string sourceCode) {
    this->sourceCode = sourceCode;
}

void Parser::parse() {
    Lexer* lexer = new Lexer(this->sourceCode);
    lexer->tokenize();
}
