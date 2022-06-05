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

#include "../ast/Statement.h"
#include "../ast/statement/ExpressionStmt.h"
#include "../ast/statement/Block.h"
#include "../ast/statement/If.h"
#include "../ast/statement/Print.h"
#include "../ast/statement/While.h"


namespace Pulsar {
    class Parser {
        public:
            Parser(std::string sourceCode);
            Statement* parse();
            CompilerError* getErrors();

        private:
            // Input Data
            std::string sourceCode;
            std::vector<Token> tokens;

            // Processing Data
            int current;

            // Output Data
            Statement* program;
            CompilerError* errors;

            // ---- AST Parsing Functions ---- //

            // Statement Nodes
            Statement* statement();
            Block* block();
            Statement* ifStatement();
            Statement* whileStatement();
            Statement* printStatement();
            Statement* expressionStatement();

            // Expression Nodes
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

            // ---- End AST Parsing Functions ---- //

            // Node Parsing Helpers

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
