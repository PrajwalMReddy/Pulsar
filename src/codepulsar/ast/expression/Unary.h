#ifndef CODEPULSAR_UNARY_H
#define CODEPULSAR_UNARY_H

#include <string>

#include "../Expression.h"


namespace Pulsar {
    class Unary: public Expression {
        public:
            Unary(std::string operatorType, Expression* right, int line);
            std::any accept(ExprVisitor& visitor);

            std::string getOperator();
            Expression* getExpression();
            int getLine();

        private:
            std::string operatorType;
            Expression* right;
            int line;
    };
}


#endif
