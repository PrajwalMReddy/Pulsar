#ifndef CODEPULSAR_BLOCK_H
#define CODEPULSAR_BLOCK_H

#include <vector>

#include "../Statement.h"


namespace Pulsar {
    class Block: public Statement {
        public:
            Block(std::vector<Statement*>* statements, int line);
            void accept(StmtVisitor& visitor);

            std::vector<Statement*>* getStatements();
            int getLine();

        private:
            std::vector<Statement*>* statements;
            int line;
    };
}


#endif
