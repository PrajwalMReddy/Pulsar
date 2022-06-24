#ifndef CODEPULSAR_EXPRESSIONSTMT_H
#define CODEPULSAR_EXPRESSIONSTMT_H

#include "../Statement.h"
#include "../Expression.h"


namespace Pulsar {
    class ExpressionStmt: public Statement {
        public:
            ExpressionStmt(Expression* expression, int line);
            template<typename R>
            R accept(StmtVisitor<R>& visitor);

            Expression* getExpression();
            int getLine();

        private:
            Expression* expression;
            int line;
    };
}


#endif
