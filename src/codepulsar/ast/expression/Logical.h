#ifndef CODEPULSAR_LOGICAL_H
#define CODEPULSAR_LOGICAL_H

#include <string>

#include "../Expression.h"


namespace Pulsar {
    class Logical: public Expression {
    public:
        Logical(Expression* left, std::string operatorType, Expression* right, int line);
        std::any accept(ExprVisitor& visitor);

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
