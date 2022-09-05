#ifndef CODEPULSAR_VALIDATOR_H
#define CODEPULSAR_VALIDATOR_H

#include "../ast/ExprVisitor.h"
#include "../ast/StmtVisitor.h"
#include "../ast/Statement.h"
#include "../lang/CompilerError.h"
#include "../primitive/PrimitiveType.h"
#include "../pulsar/Pulsar.h"
#include "../primitive/PrimitiveType.h"
#include "../variable/SymbolTable.h"


namespace Pulsar {
    class Validator: public ExprVisitor, public StmtVisitor {
        public:
            Validator(Statement* program, SymbolTable* symbolTable, CompilerError* errors);
            void validate();

            // Expression Nodes
            std::any visitAssignmentExpression(Assignment* expression) override;
            std::any visitBinaryExpression(Binary* expression) override;
            std::any visitCallExpression(Call* expression) override;
            std::any visitGroupingExpression(Grouping* expression) override;
            std::any visitLiteralExpression(Literal* expression) override;
            std::any visitLogicalExpression(Logical* expression) override;
            std::any visitUnaryExpression(Unary* expression) override;
            std::any visitVariableExpression(VariableExpr* expression) override;

            // Statement Nodes
            std::any visitBlockStatement(Block* statement) override;
            std::any visitExpressionStatement(ExpressionStmt* statement) override;
            std::any visitFunctionStatement(Function* statement) override;
            std::any visitIfStatement(If* statement) override;
            std::any visitPrintStatement(Print* statement) override;
            std::any visitReturnStatement(Return* statement) override;
            std::any visitVariableStatement(VariableDecl* statement) override;
            std::any visitWhileStatement(While* statement) override;

        private:
            Statement* program;
            SymbolTable* symbolTable;
            CompilerError* errors;

            void generalValidation();

            void newError(std::string message, int line);
            CompilerError* getErrors();
    };
}


#endif
