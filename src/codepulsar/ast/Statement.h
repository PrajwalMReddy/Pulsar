#ifndef CODEPULSAR_STATEMENT_H
#define CODEPULSAR_STATEMENT_H

#include "StmtVisitor.h"


namespace Pulsar {
    class Statement {
        public:
            virtual void accept(StmtVisitor& visitor) = 0;
    };
}


#endif
