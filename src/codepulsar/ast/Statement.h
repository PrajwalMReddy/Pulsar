#ifndef CODEPULSAR_STATEMENT_H
#define CODEPULSAR_STATEMENT_H

#include <any>

#include "StmtVisitor.h"


namespace Pulsar {
    class Statement {
        public:
            virtual std::any accept(StmtVisitor& visitor) = 0;
    };
}


#endif
