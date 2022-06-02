#ifndef CODEPULSAR_EXPRVISITOR_H
#define CODEPULSAR_EXPRVISITOR_H


namespace Pulsar {
    template<typename R>
    class ExprVisitor {
        public:
            virtual R visitGroupingExpression(class Grouping* expression) = 0;
            virtual R visitLiteralExpression(class Literal* expression) = 0;
    };
}


#endif
