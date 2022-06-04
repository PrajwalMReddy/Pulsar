#ifndef CODEPULSAR_ASTPRINTER_H
#define CODEPULSAR_ASTPRINTER_H

#include "../pulsar/Pulsar.h"
#include "../ast/ExprVisitor.h"
#include "../ast/Expression.h"


namespace Pulsar {
    class ASTPrinter: public ExprVisitor {
        public:
            ASTPrinter();
            void print(Expression* ast);

            // Expression AST Visitors
            void visitBinaryExpression(Binary* expression) override;
            void visitCallExpression(Call* expression) override;
            void visitGroupingExpression(Grouping* expression) override;
            void visitLiteralExpression(Literal* expression) override;
            void visitLogicalExpression(Logical* expression) override;
            void visitUnaryExpression(Unary* expression) override;

        private:
            int indentCount;

            void constructTree(Expression* ast);
    };
}


#endif
