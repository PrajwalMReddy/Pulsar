#ifndef CODEPULSAR_PARSER_H
#define CODEPULSAR_PARSER_H

#include <string>
#include <vector>

#include "Lexer.h"
#include "../util/TokenDisassembler.h"
#include "../variable/SymbolTable.h"

#include "../ast/Expression.h"
#include "../ast/expression/Literal.h"
#include "../ast/expression/Grouping.h"
#include "../ast/expression/Unary.h"
#include "../ast/expression/Call.h"
#include "../ast/expression/Binary.h"
#include "../ast/expression/Logical.h"
#include "../ast/expression/VariableExpr.h"
#include "../ast/expression/Assignment.h"

#include "../ast/Statement.h"
#include "../ast/statement/ExpressionStmt.h"
#include "../ast/statement/Block.h"
#include "../ast/statement/If.h"
#include "../ast/statement/Print.h"
#include "../ast/statement/While.h"
#include "../ast/declaration/VariableDecl.h"
#include "../ast/statement/Return.h"
#include "../ast/declaration/Function.h"


namespace Pulsar {
    class Parser {
        public:
            Parser(std::string sourceCode);
            Statement* parse();

            SymbolTable* getSymbolTable();
            CompilerError* getErrors();

        private:
            // Input Data
            std::string sourceCode;
            std::vector<Token> tokens;

            // Processing Data
            int current;
            int scopeDepth;
            std::string currentFunction;

            // Output Data
            Statement* program;
            SymbolTable* symbolTable;
            CompilerError* errors;

            // ---- AST Parsing Functions ---- //

            // Statement Nodes
            Statement* declarationStatement();
            Statement* declaration();
            Statement* functionDeclaration();
            Statement* statement();
            Block* block();
            Statement* variableDeclaration(TokenType accessType);
            Statement* ifStatement();
            Statement* whileStatement();
            Statement* printStatement();
            Statement* returnStatement();
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
            bool match(std::vector<TokenType> types);
            bool matchAdvance(std::vector<TokenType> types);

            Token advance();
            Token previous();

            void startScope();
            bool isInGlobalScope();
            void endScope();

            int resolveLocal(Token name);
            PrimitiveType checkType(Token type);

            // Error Handling Functions
            bool look(TokenType token, std::string message);
            void synchronize();
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
