#ifndef CODEPULSAR_PROGRAM_H
#define CODEPULSAR_PROGRAM_H

#include <vector>

#include "../Statement.h"


namespace Pulsar {
    class Program: public Statement {
        public:
            Program(std::vector<Statement*>* statements);
            std::any accept(StmtVisitor& visitor);

            std::vector<Statement*>* getStatements();

        private:
            std::vector<Statement*>* statements;
    };
}


#endif
