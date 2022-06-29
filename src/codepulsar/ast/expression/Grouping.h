#ifndef CODEPULSAR_GROUPING_H
#define CODEPULSAR_GROUPING_H

#include "../Expression.h"


namespace Pulsar {
    class Grouping: public Expression {
        public:
            Grouping(Expression* expression, int line);
            std::any accept(ExprVisitor& visitor);

            Expression* getExpression();
            int getLine();

        private:
            Expression* expression;
            int line;
    };
}


#endif
