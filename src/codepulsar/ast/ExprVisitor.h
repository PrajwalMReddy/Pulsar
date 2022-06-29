#ifndef CODEPULSAR_EXPRVISITOR_H
#define CODEPULSAR_EXPRVISITOR_H

#include <any>


namespace Pulsar {
    class ExprVisitor {
        public:
            virtual std::any visitAssignmentExpression(class Assignment* expression) = 0;
            virtual std::any visitBinaryExpression(class Binary* expression) = 0;
            virtual std::any visitCallExpression(class Call* expression) = 0;
            virtual std::any visitGroupingExpression(class Grouping* expression) = 0;
            virtual std::any visitLiteralExpression(class Literal* expression) = 0;
            virtual std::any visitLogicalExpression(class Logical* expression) = 0;
            virtual std::any visitUnaryExpression(class Unary* expression) = 0;
            virtual std::any visitVariableExpression(class VariableExpr* expression) = 0;
    };
}


#endif
