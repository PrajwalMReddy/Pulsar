#ifndef CODEPULSAR_PRINT_H
#define CODEPULSAR_PRINT_H

#include "../Statement.h"
#include "../Expression.h"


namespace Pulsar {
    class Print: public Statement {
        public:
            Print(Expression* expression, int line);
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
