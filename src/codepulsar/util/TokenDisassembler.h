#ifndef CODEPULSAR_TOKENDISASSEMBLER_H
#define CODEPULSAR_TOKENDISASSEMBLER_H

#include <vector>

#include "../lang/Token.h"
#include "../lang/SetUp.h"


class TokenDisassembler {
    public:
        static void display(vector<Token> tokens);

    private:
        static void displayTokens(vector<Token> tokens);
        static string tokenToString(TokenType type);

        static bool isLiteralTokenType(TokenType type);
        static string space(int line);
        static string space(Token token);
        static string giveSpaces(int length);

};


#endif
