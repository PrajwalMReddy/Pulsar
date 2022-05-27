#ifndef CODEPULSAR_TOKEN_H
#define CODEPULSAR_TOKEN_H

#include <string>

#include "TokenType.h"


namespace Pulsar {
    struct Token {
        Pulsar::TokenType tokenType;
        std::string literal;
        int line;

        Token(Pulsar::TokenType tokenType, std::string literal, int line) {
            this->tokenType = tokenType;
            this->literal = literal;
            this->line = line;
        }
    };
}


#endif
