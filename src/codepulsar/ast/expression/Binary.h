#ifndef CODEPULSAR_BINARY_H
#define CODEPULSAR_BINARY_H

#include <string>

#include "../Expression.h"


namespace Pulsar {
    class Binary: public Expression {
        public:
            Binary(Expression* left, std::string operatorType, Expression* right, int line);
            template<typename R> R accept(ExprVisitor<R>& visitor);

            Expression* getLeft();
            std::string getOperator();
            Expression* getRight();
            int getLine();

        private:
            Expression* left;
            std::string operatorType;
            Expression* right;
            int line;
    };
}


#endif
