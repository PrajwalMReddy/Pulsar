#ifndef CODEPULSAR_ASTPRINTER_H
#define CODEPULSAR_ASTPRINTER_H

#include "../pulsar/Pulsar.h"
#include "../ast/ExprVisitor.h"
#include "../ast/Expression.h"
#include "../ast/StmtVisitor.h"
#include "../ast/Statement.h"


namespace Pulsar {
class ASTPrinter: public ExprVisitor<std::string>, public StmtVisitor<std::string> {
        public:
            ASTPrinter();
            void print(Statement* ast);

            // Expression AST Visitors
            std::string visitAssignmentExpression(Assignment* expression) override;
            std::string visitBinaryExpression(Binary* expression) override;
            std::string visitCallExpression(Call* expression) override;
            std::string visitGroupingExpression(Grouping* expression) override;
            std::string visitLiteralExpression(Literal* expression) override;
            std::string visitLogicalExpression(Logical* expression) override;
            std::string visitUnaryExpression(Unary* expression) override;
            std::string visitVariableExpression(VariableExpr* expression) override;

            // Statement AST Visitors
            std::string visitBlockStatement(Block* statement) override;
            std::string visitExpressionStatement(ExpressionStmt* statement) override;
            std::string visitFunctionStatement(Function* statement) override;
            std::string visitIfStatement(If* statement) override;
            std::string visitPrintStatement(Print* statement) override;
            std::string visitReturnStatement(Return* statement) override;
            std::string visitVariableStatement(VariableDecl* statement) override;
            std::string visitWhileStatement(While* statement) override;

        private:
            int indentCount;

            void constructTree(Statement* ast);
            std::string blockStatement(Block* statement);

            std::string giveTabs() const;
            void incrementIndentCount();
            void decrementIndentCount();
    };
}


#endif
