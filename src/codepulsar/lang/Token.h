#ifndef CODEPULSAR_TOKEN_H
#define CODEPULSAR_TOKEN_H

#include <iostream>

#include "TokenType.h"

using namespace std;


struct Token {
    TokenType tokenType;
    string literal;
    int line;

    Token(TokenType tokenType, string literal, int line) {
        this->tokenType = tokenType;
        this->literal = literal;
        this->line = line;
    }
};

#endif
