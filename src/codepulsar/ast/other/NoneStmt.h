#ifndef CODEPULSAR_NONESTMT_H
#define CODEPULSAR_NONESTMT_H

#include "../Statement.h"


namespace Pulsar {
    class NoneStmt: public Statement {
        public:
            NoneStmt();
            std::any accept(StmtVisitor& visitor);
    };
}


#endif
