#ifndef CODEPULSAR_EXPRVISITOR_H
#define CODEPULSAR_EXPRVISITOR_H


namespace Pulsar {
    class ExprVisitor {
        public:
            virtual void visitGroupingExpression(class Grouping* expression) = 0;
            virtual void visitLiteralExpression(class Literal* expression) = 0;
    };
}


#endif
