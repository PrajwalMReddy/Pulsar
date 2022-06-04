#ifndef CODEPULSAR_PARSER_H
#define CODEPULSAR_PARSER_H

#include <string>

#include "Lexer.h"
#include "../util/TokenDisassembler.h"

#include "../ast/Expression.h"
#include "../ast/expression/Literal.h"
#include "../ast/expression/Grouping.h"
#include "../ast/expression/Unary.h"
#include "../ast/expression/Call.h"
#include "../ast/expression/Binary.h"
#include "../ast/expression/Logical.h"


namespace Pulsar {
    class Parser {
        public:
            Parser(std::string sourceCode);
            Expression* parse();
            CompilerError* getErrors();

        private:
            // Input Data
            std::string sourceCode;
            std::vector<Token> tokens;

            // Processing Data
            int current;

            // Output Data
            Expression* program;
            CompilerError* errors;

            // AST Parsing Functions
            Expression* expression();
            Expression* assignment();
            Expression* logicalOr();
            Expression* logicalAnd();
            Expression* equality();
            Expression* comparison();
            Expression* term();
            Expression* factor();
            Expression* unary();
            Expression* call();
            Expression* primary();

            // Helper Functions
            bool match(TokenType type);
            bool matchAdvance(TokenType type);

            Token advance();
            Token previous();

            // Error Handling Functions
            bool look(TokenType token, std::string message);
            void newError(std::string message, int line);

            // The Peek Family
            Token peek();
            Token peekNext();

            TokenType peekType();
            std::string peekLiteral();
            int peekLine();
    };
}


#endif
