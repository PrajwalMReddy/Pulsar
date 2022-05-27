#include "Parser.h"


Pulsar::Parser::Parser(std::string sourceCode) {
    this->sourceCode = sourceCode;
}

void Pulsar::Parser::parse() {
    Pulsar::Lexer lexer = Lexer(this->sourceCode);
    this->tokens = lexer.tokenize();
    this->errors = lexer.getErrors();

    if (this->errors->hasError()) return;
    Pulsar::TokenDisassembler::display(this->tokens);
}