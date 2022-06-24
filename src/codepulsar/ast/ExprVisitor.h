#ifndef CODEPULSAR_EXPRVISITOR_H
#define CODEPULSAR_EXPRVISITOR_H


namespace Pulsar {
    template<typename R>
    class ExprVisitor {
        public:
            virtual R visitAssignmentExpression(class Assignment* expression) = 0;
            virtual R visitBinaryExpression(class Binary* expression) = 0;
            virtual R visitCallExpression(class Call* expression) = 0;
            virtual R visitGroupingExpression(class Grouping* expression) = 0;
            virtual R visitLiteralExpression(class Literal* expression) = 0;
            virtual R visitLogicalExpression(class Logical* expression) = 0;
            virtual R visitUnaryExpression(class Unary* expression) = 0;
            virtual R visitVariableExpression(class VariableExpr* expression) = 0;
    };
}


#endif
