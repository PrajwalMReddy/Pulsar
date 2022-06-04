#ifndef CODEPULSAR_EXPRVISITOR_H
#define CODEPULSAR_EXPRVISITOR_H


namespace Pulsar {
    class ExprVisitor {
        public:
            virtual void visitBinaryExpression(class Binary* expression) = 0;
            virtual void visitCallExpression(class Call* expression) = 0;
            virtual void visitGroupingExpression(class Grouping* expression) = 0;
            virtual void visitLiteralExpression(class Literal* expression) = 0;
            virtual void visitLogicalExpression(class Logical* expression) = 0;
            virtual void visitUnaryExpression(class Unary* expression) = 0;
    };
}


#endif
