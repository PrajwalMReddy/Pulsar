#ifndef CODEPULSAR_TOKENDISASSEMBLER_H
#define CODEPULSAR_TOKENDISASSEMBLER_H

#include <iostream>
#include <vector>

#include "../lang/Token.h"
#include "../lang/SetUp.h"
#include "../pulsar/Pulsar.h"


namespace Pulsar {
    class TokenDisassembler {
        public:
            static void display(std::vector<Pulsar::Token> tokens);

        private:
            static void displayTokens(std::vector<Pulsar::Token> tokens);
            static std::string tokenToString(Pulsar::TokenType type);

            static bool isLiteralTokenType(Pulsar::TokenType type);
            static std::string space(int line);
            static std::string space(Pulsar::Token token);
            static std::string giveSpaces(int length);
    };
}


#endif
