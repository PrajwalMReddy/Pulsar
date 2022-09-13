#ifndef CODEPULSAR_IF_H
#define CODEPULSAR_IF_H

#include "../Expression.h"
#include "../other/Block.h"


namespace Pulsar {
    class If: public Statement {
        public:
            If(Expression* condition, Block* thenBranch, Statement* elseBranch, int line);
            std::any accept(StmtVisitor& visitor);

            bool hasElse();
            Expression* getCondition();
            Block* getThenBranch();
            Statement* getElseBranch();
            int getLine();

        private:
            Expression* condition;
            Block* thenBranch;
            Statement* elseBranch;
            int line;
    };
}


#endif
