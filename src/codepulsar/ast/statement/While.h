#ifndef CODEPULSAR_WHILE_H
#define CODEPULSAR_WHILE_H

#include "../Statement.h"
#include "../Expression.h"


namespace Pulsar {
    class While: public Statement {
        public:
            While(Expression* condition, Block* statements, int line);
            template<typename R>
            R accept(StmtVisitor<R>& visitor);

            Expression* getCondition();
            Block* getStatements();
            int getLine();

        private:
            Expression* condition;
            Block* statements;
            int line;
    };
}


#endif
