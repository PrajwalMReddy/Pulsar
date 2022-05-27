#ifndef CODEPULSAR_LEXER_H
#define CODEPULSAR_LEXER_H

#include <string>
#include <vector>

#include "../lang/Token.h"
#include "../lang/CompilerError.h"


namespace Pulsar {
    class Lexer {
        public:
            Lexer(std::string sourceCode);
            std::vector<Pulsar::Token> tokenize();
            Pulsar::CompilerError* getErrors();

        private:
            // Input Data
            std::string sourceCode;

            // Processing Data
            int start;
            int current;
            int line;

            // Output Data
            std::vector<Token> tokens;
            Pulsar::CompilerError* errors;

            // Core Functions
            Pulsar::Token scanToken();

            Pulsar::Token scanIdentifier();
            Pulsar::Token scanNumber();
            Pulsar::Token scanCharacter(char character);

            Pulsar::Token makeToken(Pulsar::TokenType tokenType);
            Pulsar::Token errorToken(std::string message);

            // Utility Functions
            Pulsar::TokenType identifyIdentifier();
            Pulsar::Token charLiteral();

            void skipWhitespace();
            std::string currentLiteral();

            bool isAlpha(char c);
            bool isDigit(char c);

            char peek();
            char peek(int skip);
            char advance();
            bool isAtEnd();
    };
}


#endif
