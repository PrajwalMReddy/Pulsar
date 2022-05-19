#ifndef CODEPULSAR_LEXER_H
#define CODEPULSAR_LEXER_H

#include <iostream>
#include <vector>

#include "../lang/Token.h"
#include "../lang/CompilerError.h"

using namespace std;


class Lexer {
    public:
        explicit Lexer(string sourceCode);
        vector<Token> tokenize();
        CompilerError* getErrors();

    private:
        // Input Data
        string sourceCode;

        // Processing Data
        int start;
        int current;
        int line;

        // Output Data
        vector<Token> tokens;
        CompilerError* errors = new CompilerError();

        // Functions
        Token scanToken();

        Token identifier();
        Token number();
        Token character(char now);

        Token makeToken(TokenType tokenType);
        Token errorToken(string message);

        // Utility Functions
        TokenType identifyIdentifier();
        Token charLiteral();

        void skipWhitespace();
        string currentLiteral();

        bool isAlpha(char c);
        bool isDigit(char c);

        char peek();
        char peek(int skip);
        char advance();
        bool isAtEnd();
};


#endif
