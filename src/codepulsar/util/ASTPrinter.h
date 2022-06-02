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
            void visitGroupingExpression(Grouping* expression) override;
            void visitLiteralExpression(Literal* expression) override;

        private:
            int indentCount;

            void constructTree(Expression* ast);
    };
}


#endif
