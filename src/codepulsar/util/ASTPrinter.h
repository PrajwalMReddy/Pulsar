#ifndef CODEPULSAR_ASTPRINTER_H
#define CODEPULSAR_ASTPRINTER_H

#include "../pulsar/Pulsar.h"
#include "../ast/ExprVisitor.h"
#include "../ast/Expression.h"
#include "../ast/StmtVisitor.h"
#include "../ast/Statement.h"


namespace Pulsar {
    class ASTPrinter: public ExprVisitor, public StmtVisitor {
        public:
            ASTPrinter();
            void print(Statement* ast);

            // Expression AST Visitors
            std::any visitAssignmentExpression(Assignment* expression) override;
            std::any visitBinaryExpression(Binary* expression) override;
            std::any visitCallExpression(Call* expression) override;
            std::any visitGroupingExpression(Grouping* expression) override;
            std::any visitLiteralExpression(Literal* expression) override;
            std::any visitLogicalExpression(Logical* expression) override;
            std::any visitUnaryExpression(Unary* expression) override;
            std::any visitVariableExpression(VariableExpr* expression) override;

            // Statement AST Visitors
            std::any visitBlockStatement(Block* statement) override;
            std::any visitExpressionStatement(ExpressionStmt* statement) override;
            std::any visitFunctionStatement(Function* statement) override;
            std::any visitIfStatement(If* statement) override;
            std::any visitNoneStatement(NoneStmt* statement) override;
            std::any visitPrintStatement(Print* statement) override;
            std::any visitProgramStatement(Program* statement) override;
            std::any visitReturnStatement(Return* statement) override;
            std::any visitVariableStatement(VariableDecl* statement) override;
            std::any visitWhileStatement(While* statement) override;

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
